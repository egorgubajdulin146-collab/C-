#include "funcion.h"

#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <iterator>
#include <limits>
#include <list>
#include <string>
#include <vector>

// Считать целое число с проверкой
static int readint(const std::string& prompt) {
    using namespace std;
    int x;
    while (true) {
        cout << prompt;
        if (cin >> x) return x;

        cout << "Ошибка ввода. Введите целое число.\n";
        cin.clear();
        cin.ignore(10000, '\n');
    }
}
// Считать число не меньше minVal
static int readintmin(const std::string& prompt, int minVal) {
    while (true) {
        int x = readint(prompt);
        if (x >= minVal) return x;
        std::cout << "Число должно быть >= " << minVal << ".\n";
    }
}

// Считать число в диапазоне [l; r]
static int readintrange(const std::string& prompt, int l, int r) {
    while (true) {
        int x = readint(prompt);
        if (x >= l && x <= r) return x;
        std::cout << "Число должно быть в диапазоне [" << l << "; " << r << "].\n";
    }
}

static bool fillSource3Ways(std::vector<int>& src, int minCount) {
    using namespace std;
    src.clear();

    int mode = readintrange("Заполнение: 1-клавиатура, 2-файл, 3-случайно: ", 1, 3);

    // 1) Клавиатура
    if (mode == 1) {
        int n = readintmin("Введите количество элементов: ", minCount);
        for (int i = 0; i < n; ++i) {
            int x = readint("Введите число: ");
            src.push_back(x);
        }
        return true;
    }

    // 2) Файл
    if (mode == 2) {
        string fileName;
        cout << "Имя файла: ";
        cin >> fileName;

        ifstream fin(fileName);
        if (!fin.is_open()) return false;

        // Читаем все числа из файла через итераторы
        vector<int> temp((istream_iterator<int>(fin)), istream_iterator<int>());
        if ((int)temp.size() < minCount) return false;

        src = temp;
        return true;
    }

    // 3) Случайно
    int n = readintmin("Введите n: ", minCount);
    int l = readint("Введите left: ");
    int r = readint("Введите right: ");
    if (l > r) swap(l, r);

    static bool seeded = false;
    if (!seeded) {
        srand((unsigned)time(nullptr));
        seeded = true;
    }

    cout << "Сгенерировано: ";
    for (int i = 0; i < n; ++i) {
        int x = l + rand() % (r - l + 1);
        cout << x << ' ';
        src.push_back(x);
    }
    cout << '\n';

    return true;
}



void STL2Seq2() {
    using namespace std;
    vector<int> source;

    if (!fillSource3Ways(source, 1)) {
        cout << "Ошибка заполнения\n";
        return;
    }

    // Заполнение контейнера list через итераторы и конструктор
    list<int> L(source.begin(), source.end());

    cout << "L (прямой порядок): ";
    for (list<int>::iterator it = L.begin(); it != L.end(); ++it) {
        cout << *it << ' ';
    }
    cout << '\n';

    cout << "L (обратный порядок): ";
    for (list<int>::reverse_iterator it = L.rbegin(); it != L.rend(); ++it) {
        cout << *it << ' ';
    }
    cout << '\n';
}

void STL2Seq11() {
    using namespace std;
    cout << "Задание 2 пока не реализовано.\n";
}

void STL2Seq27() {
    using namespace std;
    cout << "Задание 3 пока не реализовано.\n";
}

void STL1Iter15() {
    using namespace std;
    cout << "Задание 4 пока не реализовано.\n";
}