#include "funcion.h"

#include <iostream>
#include <limits>

using namespace std;

// Считать пункт меню
static int readMenuChoice() {
    while (true) {
        cout << "Выбор: ";
        int x;
        if (cin >> x && x >= 0 && x <= 4) return x;

        cout << "Ошибка ввода. Введите число от 0 до 4.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

int main() {
    int choice = -1;

    do {
        cout << "\n\tЛаба 13, вариант 4\n";
        cout << "1 - STL3Alg3\n";
        cout << "2 - STL3Alg19\n";
        cout << "3 - STL3Alg47\n";
        cout << "4 - STL3Alg61\n";
        cout << "0 - Выход\n";

        choice = readMenuChoice();

        switch (choice) {
            case 1:
                STL3Alg3();
                break;
            case 2:
                STL3Alg19();
                break;
            case 3:
                STL3Alg47();
                break;
            case 4:
                STL3Alg61();
                break;
            case 0:
                cout << "Выход\n";
                break;
        }
    } while (choice != 0);

    return 0;
}
