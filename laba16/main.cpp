#include "funcion.h"

#include <iostream>


int main() {
    using namespace std;
    int choice;

    do {
        cout << "\n\tЛаба 16, вариант 4\n";
        cout << "1 - TreeWork4\n";
        cout << "2 - TreeWork13\n";
        cout << "3 - TreeWork20\n";
        cout << "0 - Выход\n";

        choice = Check::readIntRange("Выбор: ", 0, 3);

        switch (choice) {
            case 1:
                TreeWork4();
                break;
            case 2:
                TreeWork13();
                break;
            case 3:
                TreeWork20();
                break;
            case 0:
                cout << "Выход\n";
                break;
        }
    } while (choice != 0);

    return 0;
}
