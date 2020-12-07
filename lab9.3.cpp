#include <iostream> 
#include <fstream> 
#include <iomanip> 
#include <string> 
#include <Windows.h>   // забезпечення відображення кирилиці

using namespace std; 

struct Route {
    string begin;
    string end;
    int number;
};

void Input(Route * &p, int &N);
void Sort(Route* p, const int N);
void Print(Route* p, const int N);
void Find(Route* p, const int N);
void SaveToFile(Route* p, const int N, const char* filename);
void LoadFromFile(Route*& p, int& N, const char* filename);

int main() {
    SetConsoleCP(1251); // встановлення сторінки win-cp1251 в потік вводу
    SetConsoleOutputCP(1251); // встановлення сторінки win-cp1251 в потік виводу

    int N = 0;
    int action;
    Route* p = nullptr;
    char filename[100];

    while (true) {
        cout << "Введіть дію (1 - ввести список маршрутів, 2 - завантажити з файлу, 3 - зберегти у файл, 4 - знайти маршрут, 5 - сортувати масив, 0 - вихід з програми): ";
        cin >> action;
        if (action == 0) break;
        if (action == 1) {
            Input(p, N);
            Print(p, N);
        } 
        if (action == 2) {
            //delete [] p;
            cin.get();
            cin.sync();
            cout << "Введіть ім'я файлу: ";
            cin.getline(filename, 99);
            LoadFromFile(p, N, filename);
            Print(p, N);
            continue;
        }
        if (action == 3) {
            if (N == 0) {
                cout << "Список маршрутів ще не заданий " << endl;
                continue;
            }
            cin.get();  
            cin.sync(); 
            cout << "Введіть ім'я файлу: ";
            cin.getline(filename, 99);
            SaveToFile(p, N, filename);
            continue;
        };
        if (action == 4) Find(p, N);
        if (action == 5) {
            Sort(p, N);
            Print(p, N);
        }
    }
}

void Input(Route * &p, int &N) {
    cout << "Введіть кількість маршрутів: ";
    cin >> N;
    if (N <= 0) {
        cout << "Кількість маршрутів повинна бути додатною " << endl;
    }
    p = new Route[N];
    for (int n = 0; n < N; n++) {
        cout << "маршрут №: " << n+1 << endl;
        cout << "  початок: ";
        cin.get();  // очищуємо буфер клавіатури, бо залишаються символи
        cin.sync(); // "кінець рядка", які не дають ввести наступний літерний рядок
        getline(cin, p[n].begin);
        cout << "  кінець: ";
        getline(cin, p[n].end);
        cout << "  номер маршрута: ";
        cin >> p[n].number;
    }
}

// сортування масиву методом бульбашки
void Sort(Route* p, const int N) {
    if (N == 0) {
        cout << "Список маршрутів ще не заданий " << endl;
        return;
    }
    Route tmp_route;
    for (int upper = N - 2; upper >= 0; upper--) {
        for (int k = 0; k <= upper; k++) {
            if (p[k].number > p[k + 1].number) {
                tmp_route = p[k];
                p[k] = p[k + 1];
                p[k + 1] = tmp_route;
            }
        }
    }
}

void Print(Route* p, const int N) {
    if (N == 0) {
        cout << "Список маршрутів ще не заданий " << endl;
        return;
    }
    cout << "==============================" << endl;
    cout << "|  №  |  Початок  |  Кінець  |" << endl;
    cout << "------------------------------" << endl;
    for (int i = 0; i < N; i++) {
        cout << "| " << right << setw(3) << p[i].number << " ";
        cout << "| " << left << setw(9) << p[i].begin << " ";
        cout << "| " << left << setw(8) << p[i].end << " ";
        cout << "|" << endl;
    }    
    cout << "==============================" << endl;
}

void Find(Route* p, const int N) {
    if (N == 0) {
        cout << "Список маршрутів ще не заданий " << endl;
        return;
    }
    int k = 0;
    cout << "Введіть номер маршрута для пошуку: ";
    cin >> k;
    for (int i = 0; i < N; i++) {
        if (p[i].number == k) {
            cout << "Маршрут знайдено: " << endl;
            cout << "  Початок: " << p[i].begin << endl;
            cout << "  Кінець: " << p[i].end << endl;
            return;
        }
    }
    cout << "Маршрут не знайдено." << endl;
}

void SaveToFile(Route* p, const int N, const char* filename) {
    ofstream fout(filename, ios::binary); 
    fout.write((char*)&N, sizeof(N)); 
    for (int i = 0; i < N; i++) fout.write((char*)&p[i], sizeof(Route)); 
    fout.close(); 
} 

void LoadFromFile(Route*& p, int& N, const char* filename) {
    ifstream fin(filename, ios::binary);
    fin.read((char*)&N, sizeof(N));
    p = new Route[N];
    for (int i = 0; i < N; i++) fin.read((char*)&p[i], sizeof(Route));
    fin.close();
}
