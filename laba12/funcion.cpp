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
#include <algorithm>

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

// Подготовить входные данные для STL1Iter15 тремя способами
static bool prepareSTL1Iter15Input(std::string& inputFileName) {
    using namespace std;

    int mode = readintrange("Заполнение: 1-клавиатура, 2-файл, 3-случайно: ", 1, 3);

    if (mode == 1) {
        inputFileName = "temp_stl1iter15.txt";
        ofstream temp(inputFileName);
        if (!temp.is_open()) return false;

        int n = readintmin("Введите количество чисел: ", 1);
        for (int i = 0; i < n; ++i) {
            int x = readint("Введите число: ");
            temp << x << ' ';
        }
        return true;
    }

    if (mode == 2) {
        cout << "Имя входного файла: ";
        cin >> inputFileName;

        ifstream fin(inputFileName);
        return fin.is_open();
    }

    inputFileName = "temp_stl1iter15.txt";
    ofstream temp(inputFileName);
    if (!temp.is_open()) return false;

    int n = readintmin("Введите количество чисел: ", 1);
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
        temp << x << ' ';
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
    
    vector<int> sourcev;
    vector<int> sourcel;
    
    cout << "Заполнение vector V\n";
    if (!fillSource3Ways(sourcev, 5)) {
        cout << "Ошибка заполнения V\n";
        return;
    }

    cout << "Заполнение list L\n";
    if (!fillSource3Ways(sourcel, 5)) {
        cout << "Ошибка заполнения L\n";
        return;
    }

    vector<int> V(sourcev.begin(), sourcev.end());
    list<int> L(sourcel.begin(), sourcel.end());

     cout << "V: ";
    for (vector<int>::iterator it = V.begin(); it != V.end(); ++it) {
        cout << *it << ' ';
    }
    cout << '\n';

    cout << "L до вставки: ";
    for (list<int>::iterator it = L.begin(); it != L.end(); ++it) {
        cout << *it << ' ';
    }
    cout << '\n';

     // Ищем позицию после 5-го элемента списка
    list<int>::iterator pos = L.begin();
    advance(pos, 5);

    // Берем первые 5 элементов V, но в обратном порядке
    vector<int>::iterator first = V.begin();
    vector<int>::iterator last = V.begin();
    advance(last, 5);

    // Один вызов insert
    L.insert(
        pos,
        //обход с конца
        reverse_iterator<vector<int>::iterator>(last),
        reverse_iterator<vector<int>::iterator>(first)
    );

    cout << "L после вставки: ";
    for (list<int>::iterator it = L.begin(); it != L.end(); ++it) {
        cout << *it << ' ';
    }
    cout << '\n';
}


void STL2Seq27() {
    using namespace std;

    vector<int> source;

    if (!fillSource3Ways(source, 1)) {
        cout << "Ошибка заполнения\n";
        return;
    }

    // Создаем vector через конструктор и итераторы
    vector<int> V(source.begin(), source.end());

    cout << "V до удаления: ";
    for (vector<int>::iterator it = V.begin(); it != V.end(); ++it) {
        cout << *it << ' ';
    }
    cout << '\n';

    // Удаляем элементы с нечетными номерами: 1, 3, 5, ...
    for (vector<int>::iterator it = V.begin(); it != V.end(); ) {
        it = V.erase(it);

        if (it == V.end()) break;

        ++it;
    }

    cout << "V после удаления: ";
    for (vector<int>::iterator it = V.begin(); it != V.end(); ++it) {
        cout << *it << ' ';
    }
    cout << '\n';
}

void STL1Iter15() {
    using namespace std;

    string inputFileName;
    if (!prepareSTL1Iter15Input(inputFileName)) {
        cout << "Ошибка подготовки входных данных\n";
        return;
    }

    string outFileName;
    cout << "Имя выходного файла: ";
    cin >> outFileName;

    if (inputFileName == outFileName) {
        cout << "Входной и выходной файл не должны совпадать\n";
        return;
    }

    ifstream finShow(inputFileName);
    if (!finShow.is_open()) {
        cout << "Ошибка открытия входного файла\n";
        return;
    }

    cout << "Исходные числа: ";
    copy(
        istream_iterator<int>(finShow),
        istream_iterator<int>(),
        ostream_iterator<int>(cout, " ")
    );
    cout << '\n';
    finShow.close();

    ifstream fin(inputFileName);
    ofstream fout(outFileName);

    if (!fin.is_open() || !fout.is_open()) {
        cout << "Ошибка открытия файла\n";
        return;
    }

    replace_copy(
        istream_iterator<int>(fin),
        istream_iterator<int>(),
        ostream_iterator<int>(fout, "  "),
        0,
        10
    );

    cout << "Готово. Результат записан в файл: " << outFileName << '\n';
}