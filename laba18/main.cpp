#include "funcion.h"

#include <iostream>

int main(){
    using namespace std;

    int choice;

    do{
        cout << "\n\tЛаба 18, вариант 4\n";
        cout << "1 - TreeFun2\n";
        cout << "2 - TreeFun6\n";
        cout << "3 - TreeFun9\n";
        cout << "0 - Выход\n";

        choice = Check::readIntRange("Выбор: ", 0, 3);

        switch(choice){
            case 1:
                TreeFun2();
                break;
            case 2:
                TreeFun6();
                break;
            case 3:
                TreeFun9();
                break;
            case 0:
                cout << "Выход\n";
                break;
        }
    } while(choice != 0);

    return 0;
}
