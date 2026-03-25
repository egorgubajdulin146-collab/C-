#include "funcion.h"

#include <iostream>
#include <limits>


static int readMenuChoice() {
    using namespace std;
    while (true) {
        cout << "Выбор: ";
        int x;
        if (cin >> x && x >= 0 && x <= 3) return x;

        cout << "Ошибка ввода. Введите число от 0 до 3.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

int main() {
    using namespace std;
    int choice = -1;

    do {
        cout << "\n\tЛаба 14, вариант 4\n";
        cout << "1 - STL5Assoc3\n";
        cout << "2 - STL5Assoc15\n";
        cout << "3 - STL5Assoc22\n";
        cout << "0 - Выход\n";

        choice = readMenuChoice();

        switch (choice) {
            case 1:
                STL5Assoc3();
                break;
            case 2:
                STL5Assoc15();
                break;
            case 3:
                STL5Assoc22();
                break;
            case 0:
                cout << "Выход\n";
                break;
        }
    } while (choice != 0);

    return 0;
}
