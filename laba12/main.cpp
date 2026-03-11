#include "funcion.h" 
#include <iostream>
#include <limits>


static int readMenuChoice() {
    using namespace std;
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
    using namespace std;
    int choice = -1;

    do {
        cout << "\n\tЛаба 12, вариант 4\n";
        cout << "1 - STL2Seq2\n";
        cout << "2 - STL2Seq11\n";
        cout << "3 - STL2Seq27\n";
        cout << "4 - STL1Iter15\n";
        cout << "0 - Выход\n";

        choice = readMenuChoice();

        switch (choice) {
            case 1:
                STL2Seq2();
                break;
            case 2:
                STL2Seq11();
                break;
            case 3:
                STL2Seq27();
                break;
            case 4:
                STL1Iter15();
                break;
            case 0:
                cout << "Выход\n";
                break;
        }
    } while (choice != 0);

    return 0;
}
