#include "funcion.h"

#include <ctime>
#include <cstdlib>
#include <iostream>
#include <string>



int main() {
    using namespace std;
    srand(static_cast<unsigned int>(time(nullptr)));

    int cmd;

    do {
        cout << "\n\tЛаба 10, вариант 4\n";
        cout << "1 - Dynamic 6\n";
        cout << "2 - Dynamic 21\n";
        cout << "3 - ListWork4\n";
        cout << "4 - ListWork25\n";
        cout << "5 - ListWork62\n";
        cout << "0 - Выход\n";
        cout << "Выбор: ";
        cin >> cmd;

        switch (cmd) {
            case 1: {
                PNode top = nullptr;
                fillStack(top, 10);

                printstack(top);
                dynamic6(top);
                printstack(top);

                clearstack(top);
                break;
            }

            case 2: {
                Queue q1, q2;

                cout << "Первая очередь:\n";
                fillQueue(q1);
                cout << "Вторая очередь:\n";
                fillQueue(q2);

                cout << "Первая ";
                printqueue(q1);
                cout << "Вторая ";
                printqueue(q2);

                dynamic21(q1, q2);

                cout << "После переноса:\n";
                cout << "Первая ";
                printqueue(q1);
                cout << "Вторая ";
                printqueue(q2);

                if (q2.head) cout << "P3 = " << q2.head << ", P4 = " << q2.tail << '\n';
                else cout << "P3 = nullptr, P4 = nullptr\n";

                clearqueue(q1);
                clearqueue(q2);
                break;
            }

            case 3: {
                PNode head = nullptr, tail = nullptr;
                fillList(head, tail, 5);

                printlist(head);

                PNode p5 = listWork4(head);
                if (p5) cout << "P5 = " << p5 << ", value = " << p5->data << '\n';
                else cout << "P5 = nullptr\n";

                clearlist(head);
                break;
            }

            case 4: {
                PNode head = nullptr, tail = nullptr;
                int m;

                fillList(head, tail, 1);
                cout << "Введите M: ";
                cin >> m;

                cout << "До: ";
                printlist(head);

                PNode p2 = listWork25(head, m);

                cout << "После: ";
                printlist(head);

                if (p2) cout << "P2 = " << p2 << ", value = " << p2->data << '\n';
                else cout << "P2 = nullptr\n";

                clearlist(head);
                break;
            }

            case 5: {
                PNode head = nullptr;
                PNode tail = nullptr;

                int method;
                cout << "Способ заполнения для ListWork62: 1-клавиатура, 2-файл, 3-случайно: ";
                cin >> method;

                if (method == 1) {
                    int n;
                    cout << "Введите количество элементов: ";
                    cin >> n;
                    cout << "Введите " << n << " чисел: ";
                    for (int i = 0; i < n; ++i) {
                        int x;
                        cin >> x;
                        sortik(head, x);
                    }
                } else if (method == 2) {
                    string fileName;
                    cout << "Введите имя файла: ";
                    cin >> fileName;
                    if (!listWork62(fileName, head)) {
                        cout << "Не удалось открыть файл\n";
                    }
                } else if (method == 3) {
                    int n, l, r;
                    cout << "Введите количество элементов: ";
                    cin >> n;
                    cout << "Введите диапазон [L R]: ";
                    cin >> l >> r;
                    if (l > r) {
                        int t = l;
                        l = r;
                        r = t;
                    }

                    cout << "Сгенерировано: ";
                    for (int i = 0; i < n; ++i) {
                        int x = l + rand() % (r - l + 1);
                        cout << x << ' ';
                        sortik(head, x);
                    }
                    cout << '\n';
                } else {
                    cout << "Неверный способ\n";
                }

                if (head) {
                    PNode p = head;
                    while (p->next) p = p->next;
                    tail = p;
                }

                cout << "Список по убыванию: ";
                printlist(head);
                if (head) cout << "P1 = " << head << ", P2 = " << tail << '\n';
                else cout << "P1 = nullptr, P2 = nullptr\n";

                clearlist(head);
                break;
            }

            case 0:
                cout << "Выход\n";
                break;

            default:
                cout << "Неверный выбор\n";
                break;
        }
    } while (cmd != 0);

    return 0;
}
