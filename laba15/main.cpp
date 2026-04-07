#include "funcion.h"

#include <iostream>
#include <limits>

using namespace std;

// Считать пункт меню
static int readMenuChoice() {
    while (true) {
        cout << "Выбор: ";
        int x;

        if (cin >> x && x >= 0 && x <= 5) {
            return x;
        }

        cout << "Ошибка ввода. Введите число от 0 до 5.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

int main() {
    int choice;

    do {
        cout << "\nЛаба 15, вариант 4\n";
        cout << "1 - Задание 1\n";
        cout << "2 - Задание 2\n";
        cout << "3 - Задание 3\n";
        cout << "4 - Задание 4\n";
        cout << "5 - Задание 5\n";
        cout << "0 - Выход\n";

        choice = readMenuChoice();

        switch (choice) {
            case 1:
                runTask1();
                break;
            case 2:
                runTask2();
                break;
            case 3:
                runTask3();
                break;
            case 4:
                runTask4();
                break;
            case 5:
                runTask5();
                break;
            case 0:
                cout << "Выход\n";
                break;
        }
    } while (choice != 0);

    return 0;
}
