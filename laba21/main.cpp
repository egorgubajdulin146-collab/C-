#include "funcion.h"

#include <iostream>

int main(){
    using namespace std;

    int choice;

    do{
        cout << "\n\tЛаба 21, вариант 4\n";
        cout << "1 - Graf2\n";
        cout << "2 - Graf7\n";
        cout << "3 - Graf8\n";
        cout << "0 - Выход\n";

        choice = Check::readIntRange("Выбор: ", 0, 3);

        switch(choice){
            case 1:
                Graf2();
                break;
            case 2:
                Graf7();
                break;
            case 3:
                Graf8();
                break;
            case 0:
                cout << "Выход\n";
                printCat();
                break;
        }
    } while(choice != 0);

    return 0;
}
