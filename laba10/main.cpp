#include "funcion.h"

#include <iostream>
#include <string>

int main() {
    using namespace std;
    int choice;

    do {
        cout << "\n===== Лаба 10, вариант 4 =====\n";
        cout << "1 - Dynamic 6\n";
        cout << "2 - Dynamic 21\n";
        cout << "3 - ListWork4\n";
        cout << "4 - ListWork25\n";
        cout << "5 - ListWork62\n";
        cout << "0 - Выход\n";
        cout << "Выбор: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                PNode top = nullptr;
                int n;
                cout << "Количество элементов стека (>=10): ";
                cin >> n;
                if(n < 10){
                    cout << "Неверный выбор" << endl;
                    return 1;
                }
                cout << "Введите " << n << " чисел: ";
                for (int i = 0; i < n; ++i) {
                    int x;
                    cin >> x;
                    push(top, x);
                }

                printstack(top);
                dynamic6(top);
                printstack(top);

                clearstack(top);
                break;
            }
             case 2: {
                Queue q1, q2;
                int n1, n2;

                cout << "Размер первой очереди: ";
                cin >> n1;
                cout << "Введите " << n1 << " чисел: ";
                for (int i = 0; i < n1; ++i) {
                    int x;
                    cin >> x;
                    enqueue(q1, x);
                }

                cout << "Размер второй очереди: ";
                cin >> n2;
                cout << "Введите " << n2 << " чисел: ";
                for (int i = 0; i < n2; ++i) {
                    int x;
                    cin >> x;
                    enqueue(q2, x);
                }

                cout << "Первая "; printqueue(q1);
                cout << "Вторая "; printqueue(q2);

                dynamic21(q1, q2);

                cout << "После переноса:\n";
                cout << "Первая "; printqueue(q1);
                cout << "Вторая "; printqueue(q2);

                if (q2.head) cout << "P3 = " << q2.head << ", P4 = " << q2.tail << '\n';
                else cout << "P3 = nullptr, P4 = nullptr\n";

                clearqueue(q1);
                clearqueue(q2);
                break;
            }
            case 3: {
                PNode head = nullptr, tail = nullptr;
                int n;

                cout << "Размер списка (>=5): ";
                cin >> n;
                cout << "Введите " << n << " чисел: ";
                for (int i = 0; i < n; ++i) {
                    int x;
                    cin >> x;
                    pushback(head, tail, x);
                }

                printlist(head);

                PNode p5 = listWork4(head);
                if (p5) cout << "P5 = " << p5 << ", value = " << p5->data << '\n';
                else cout << "P5 = nullptr\n";

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
    } while (choice != 0);

    return 0;
}

