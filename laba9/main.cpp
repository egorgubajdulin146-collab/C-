#include <iostream>
#include "functions.h"

int main(){
    using namespace std;
    int cmd;
    do{
        cout << endl;
        cout << endl;
        cout << "\t ~~~Лаба 9~~~" << endl;
        cout << "1. File9" << endl;
        cout << "2. File32" << endl;
        cout << "3. File51" << endl;
        cout << "4. Recur15" << endl;
        cout << "5. Создать тесты" << endl;
        cout << "0. Выход" << endl;
        cout << "Ваш выбор: ";
        cin >> cmd;

        switch (cmd) {
            case 1: file9(); break;
            case 2: file32(); break;
            case 3: file51(); break;
            case 4: recur15(); break;
            case 5: create_tests(); break;
            case 0: 
                cout << "Программа завершена.\n"; 
                break;
            default: 
                cout << "Неверный ввод!\n";
                break;
        }
    } while(cmd != 0);

    return 0;
}