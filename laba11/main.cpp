#include "funcion.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    int choice = -1;

    do {
        cout << "\n\t Лаба 11, Вариант 4\n";
        cout << "1 - ListWork69\n";
        cout << "2 - ListWork41\n";
        cout << "3 - ListWork63\n";
        cout << "4 - ListWork46\n";
        cout << "5 - Текстовая задача 4\n";
        cout << "0 - Выход\n";
        cout << "Выбор: ";
        cin >> choice;

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
            default:
                cout << "Неверный пункт\n";
                break;
        }
    } while (choice != 0);

    return 0;
}
