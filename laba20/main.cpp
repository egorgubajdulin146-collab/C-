#include "funcion.h"

#include <iostream>

int main(){
    using namespace std;

    RightTriangle t1;
    RightTriangle t2;
    int choice;

    do{
        cout << "\n\tЛаба 20, вариант 4\n";
        cout << "1 - Ввести первый треугольник\n";
        cout << "2 - Ввести второй треугольник\n";
        cout << "3 - Вывести треугольники\n";
        cout << "4 - Площадь первого треугольника\n";
        cout << "5 - Проверить существование первого треугольника\n";
        cout << "6 - Увеличение первого треугольника\n";
        cout << "7 - Уменьшение первого треугольника\n";
        cout << "8 - Сравнить площади\n";
        cout << "9 - Тест конструкторов\n";
        cout << "0 - Выход\n";

        choice = Check::readIntRange("Выбор: ", 0, 9);

        switch(choice){
            case 1:
                cout << "Первый треугольник\n";
                t1.input();
                break;
            case 2:
                cout << "Второй треугольник\n";
                t2.input();
                break;
            case 3:
                cout << "T1: " << t1 << '\n';
                cout << "T2: " << t2 << '\n';
                break;
            case 4:
                cout << "Площадь T1: " << t1.area() << '\n';
                cout << "Через double: " << (double)t1 << '\n';
                break;
            case 5:
                if(t1){
                    cout << "T1 существует\n";
                }
                else{
                    cout << "T1 не существует\n";
                }
                break;
            case 6:
                ++t1;
                cout << "После Увеличения T1: " << t1 << '\n';
                break;
            case 7:
                --t1;
                cout << "После Уменьшения T1: " << t1 << '\n';
                break;
            case 8:
                if(t1 <= t2){
                    cout << "Площадь T1 <= площади T2\n";
                }
                else{
                    cout << "Площадь T1 > площади T2\n";
                }

                if(t1 >= t2){
                    cout << "Площадь T1 >= площади T2\n";
                }
                else{
                    cout << "Площадь T1 < площади T2\n";
                }
                break;
            case 9:{
                RightTriangle a;
                RightTriangle b(3, 4);
                RightTriangle c(b);

                cout << "Конструктор по умолчанию: " << a << '\n';
                cout << "Конструктор с параметрами: " << b << '\n';
                cout << "Конструктор копирования: " << c << '\n';
                break;
            }
            case 0:
                cout << "Выход\n";
                break;
        }
    } while(choice != 0);

    return 0;
}