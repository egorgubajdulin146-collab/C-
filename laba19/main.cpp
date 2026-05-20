 #include "funcion.h"

#include <iostream>

int main(){
    using namespace std;

    int choice;

    do{
        cout << "\n\tЛаба 19, вариант 4\n";
        cout << "1 - Код Хемминга\n";
        cout << "2 - Код Хаффмана\n";
        cout << "3 - Столбчатый шифр транспонирования\n";
        cout << "0 - Выход\n";

        choice = Check::readIntRange("Выбор: ", 0, 3);

        switch(choice){
            case 1:
                HammingTask();
                break;
            case 2:
                HuffmanTask();
                break;
            case 3:
                TranspositionCipherTask();
                break;
            case 0:
                cout << "Выход\n";
                break;
        }
    } while(choice != 0);

    return 0;
}