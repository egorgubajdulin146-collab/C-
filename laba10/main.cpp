#include "funcion.h"

#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

bool fillStackByMode(Stack& st, int minN) {
    int mode = 0;
    cout << "Заполнение стека: 1-клавиатура, 2-файл, 3-случайно: ";
    cin >> mode;

    if (mode == 1) return st.fillKeyboard(minN);

    if (mode == 2) {
        string f;
        cout << "Имя файла: ";
        cin >> f;
        return st.fillFile(f, minN);
    }

    if (mode == 3) {
        int n, l, r;
        cout << "n l r: ";
        cin >> n >> l >> r;
        return st.fillRandom(n, l, r, minN);
    }

    return false;
}

bool fillQueueByMode(QueueDS& q) {
    int mode = 0;
    cout << "Заполнение очереди: 1-клавиатура, 2-файл, 3-случайно: ";
    cin >> mode;

    if (mode == 1) return q.fillKeyboard();

    if (mode == 2) {
        string f;
        cout << "Имя файла: ";
        cin >> f;
        return q.fillFile(f);
    }

    if (mode == 3) {
        int n, l, r;
        cout << "n l r: ";
        cin >> n >> l >> r;
        return q.fillRandom(n, l, r);
    }

    return false;
}

bool fillListByMode(SinglyList& lst, int minN) {
    int mode = 0;
    cout << "Заполнение списка: 1-клавиатура, 2-файл, 3-случайно: ";
    cin >> mode;

    if (mode == 1) return lst.fillKeyboard(minN);

    if (mode == 2) {
        string f;
        cout << "Имя файла: ";
        cin >> f;
        return lst.fillFile(f, minN);
    }

    if (mode == 3) {
        int n, l, r;
        cout << "n l r: ";
        cin >> n >> l >> r;
        return lst.fillRandom(n, l, r, minN);
    }

    return false;
}

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    int choice = -1;

    do {
        cout << "\n\tЛаба 10, вариант 4\n";
        cout << "1 - Dynamic6\n";
        cout << "2 - Dynamic21\n";
        cout << "3 - ListWork4\n";
        cout << "4 - ListWork25\n";
        cout << "5 - ListWork62\n";
        cout << "0 - Выход\n";
        cout << "Выбор: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                Stack st;
                if (!fillStackByMode(st, 10)) {
                    cout << "Ошибка заполнения\n";
                    break;
                }

                st.print();

                cout << "Поиск в стеке, число: ";
                int key = 0;
                cin >> key;
                cout << (st.find(key) ? "Найдено\n" : "Не найдено\n");

                st.solveDynamic6();
                st.print();

                Stack copySt(st);
                cout << "Копия стека: ";
                copySt.print();
                break;
            }

            case 2: {
                QueueDS q1, q2;

                cout << "Первая очередь\n";
                if (!fillQueueByMode(q1)) {
                    cout << "Ошибка\n";
                    break;
                }

                cout << "Вторая очередь\n";
                if (!fillQueueByMode(q2)) {
                    cout << "Ошибка\n";
                    break;
                }

                q1.print();
                q2.print();

                q1.moveAllTo(q2);

                cout << "После переноса:\n";
                q1.print();
                q2.print();
                cout << "P3 = " << q2.headAddress() << ", P4 = " << q2.tailAddress() << '\n';

                cout << "Поиск во 2-й очереди, число: ";
                int key = 0;
                cin >> key;
                cout << (q2.find(key) ? "Найдено\n" : "Не найдено\n");
                break;
            }

            case 3: {
                SinglyList lst;
                if (!fillListByMode(lst, 5)) {
                    cout << "Ошибка заполнения\n";
                    break;
                }

                lst.print();

                const void* p5 = lst.fifthAddress();
                int v5 = 0;
                if (p5 && lst.fifthValue(v5)) {
                    cout << "P5 = " << p5 << ", value = " << v5 << '\n';
                } else {
                    cout << "P5 = nullptr\n";
                }

                cout << "Поиск в списке, число: ";
                int key = 0;
                cin >> key;
                cout << (lst.find(key) ? "Найдено\n" : "Не найдено\n");

                cout << "Удалить число: ";
                cin >> key;
                cout << (lst.removeFirst(key) ? "Удалено\n" : "Не найдено\n");
                lst.print();
                break;
            }

            case 4: {
                SinglyList lst;
                if (!fillListByMode(lst, 1)) {
                    cout << "Ошибка заполнения\n";
                    break;
                }

                cout << "До: ";
                lst.print();

                int m = 0;
                cout << "Введите M: ";
                cin >> m;
                lst.insertBeforeEachSecond(m);

                cout << "После: ";
                lst.print();
                cout << "P2 = " << lst.tailAddress() << '\n';
                break;
            }

            case 5: {
                SinglyList lst;
                int mode = 0;
                cout << "ListWork62: 1-файл, 2-клавиатура, 3-случайно: ";
                cin >> mode;

                if (mode == 1) {
                    string f;
                    cout << "Имя файла: ";
                    cin >> f;

                    ifstream fin(f);
                    if (!fin.is_open()) {
                        cout << "Ошибка файла\n";
                        break;
                    }

                    int n = 0;
                    fin >> n;
                    cout << "До (из файла): ";
                    for (int i = 0; i < n; ++i) {
                        int x = 0;
                        fin >> x;
                        cout << x << ' ';
                    }
                    cout << '\n';
                    fin.close();

                    if (!lst.buildSortedDescFromFile(f)) {
                        cout << "Ошибка файла\n";
                        break;
                    }
                } else if (mode == 2) {
                    int n = 0;
                    cout << "Количество: ";
                    cin >> n;
                    cout << "Введите " << n << " чисел: ";
                    for (int i = 0; i < n; ++i) {
                        int x = 0;
                        cin >> x;
                        lst.insertSortedDesc(x);
                    }
                } else if (mode == 3) {
                    int n = 0, l = 0, r = 0;
                    cout << "n l r: ";
                    cin >> n >> l >> r;
                    if (l > r) {
                        int t = l;
                        l = r;
                        r = t;
                    }

                    cout << "Сгенерировано: ";
                    for (int i = 0; i < n; ++i) {
                        int x = l + rand() % (r - l + 1);
                        cout << x << ' ';
                        lst.insertSortedDesc(x);
                    }
                    cout << '\n';
                } else {
                    cout << "Неверный режим\n";
                    break;
                }

                cout << "Список по убыванию: ";
                lst.print();
                cout << "P1 = " << lst.headAddress() << ", P2 = " << lst.tailAddress() << '\n';
                break;
            }

            case 0:
                cout << "Выход\n";
                break;

            default:
                cout << "Неверный пункт\n";
                break;
        }
    } while (choice != 0);

    return 0;
}
