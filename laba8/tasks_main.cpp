#include <iostream>
#include <cstdlib>
#include <fstream>

#include "tasks.h"



int main(int argc, char** argv) {
    using namespace std;
    int task = 0;
    
    if (argc >= 2) {
        task = atoi(argv[1]);
    } else {
        cout << "Выберите задачу:\n";
        cout << "1) Артефакты (минимальный налог при весе >= Z)\n";
        cout << "2) Хромой король (минимальная сумма и путь)\n";
        cout << "3) K-ичные числа (есть 4+ нулей подряд)\n";
        cout << "Ваш выбор: ";
        cin >> task;
    }

    switch (task) {
        case 1: {
            // Для задачи 1: если есть input.txt/output.txt — работаем через файлы.
            ifstream fin("input.txt");
            istream* in = &cin;
            ostream* out = &cout;
            ofstream fout;
            if (fin) {
                fout.open("output.txt");
                in = &fin;
                if (fout) out = &fout;
            }

            solveArtifactsMinTax(*in, *out);
            break;
        }
        case 2: {
            // Для задачи 2: если есть input.txt/output.txt — работаем через файлы.
            ifstream fin("input.txt");
            istream* in = &cin;
            ostream* out = &cout;
            ofstream fout;
            if (fin) {
                fout.open("output.txt");
                in = &fin;
                if (fout) out = &fout;
            }

            solveLameKing(*in, *out);
            break;
        }
        case 3:
            // Для задачи 3: только cin/cout (без файлов).
            cout << "Введите длину числа и систему счисления" << endl;
            solveKNumbers(cin, cout);
            break;
        default:
            cout << "Неверный номер задачи.\n";
            cout << "Нужно 1, 2 или 3.\n";
            break;
    }

    return 0;
}

