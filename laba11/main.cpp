#include "funcion.h"

#include <iostream>
#include <limits>

using namespace std;

static int readMenuChoice() {
    int x;
    while (true) {
        cout << "Выбор: ";
        if (cin >> x && x >= 0 && x <= 5) return x;

        cout << "Ошибка ввода. Введите число от 0 до 5.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

int main() {
    int choice = -1;

    do {
        cout << "\n\t Лаба 11, Вариант 4\n";
        cout << "1 - ListWork69\n";
        cout << "2 - ListWork41\n";
        cout << "3 - ListWork63\n";
        cout << "4 - ListWork46\n";
        cout << "5 - Текстовая задача 4\n";
        cout << "0 - Выход\n";

        choice = readMenuChoice();

        switch (choice) {
            case 1:
                ListWork69();
                break;
            case 2:
                ListWork41();
                break;
            case 3:
                ListWork63();
                break;
            case 4:
                ListWork46();
                break;
            case 5:
                Text4();
                break;
            case 0:
                cout << "Выход\n";
                break;
        }
    } while (choice != 0);

    return 0;
}
