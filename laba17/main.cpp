#include "funcion.h"
#include <iostream>

int main(){
    using namespace std;

    int choice;

    do{
        cout << "\n\tЛаба 17, вариант 4\n";
        cout << "1 - CalcTree4\n";
        cout << "2 - CalcTree26\n";
        cout << "0 - Выход\n";

        choice = Check::readIntRange("Выбор: ", 0, 2);

        switch(choice){
            case 1:
                CalcTree4();
                break;
            case 2:
                CalcTree26();
                break;
            case 0:
                cout << "Выход\n";
                break;
        }
    } while(choice != 0);

    return 0;
}
