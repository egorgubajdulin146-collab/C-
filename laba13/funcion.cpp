#include "funcion.h"

#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <iterator>
#include <limits>
#include <list>
#include <string>
#include <vector>
#include <deque>
#include <numeric>

// Функтор для STL3Alg19: выдает N, N-1, ..., 1
struct DecGenerator {
    int* cur;

    explicit DecGenerator(int& value) : cur(&value) {}

    int operator()() {
        --(*cur);
        return *cur;
    }
};

// Функтор для STL3Alg61: из пары соседних слов делает "первая буква левого + последняя буква правого"
struct PairWordBuilder {
    std::string operator()(const std::string& right, const std::string& left) const {
        std::string s;
        s += left.front();
        s += right.back();
        return s;
    }
};



// Считать целое число с проверкой
static int readInt(const std::string& prompt) {
    using namespace std;
    int x;
    while (true) {
        cout << prompt;
        if (cin >> x) return x;

        cout << "Ошибка ввода. Введите целое число.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// Считать число не меньше minVal
static int readIntMin(const std::string& prompt, int minVal) {
    using namespace std;
    while (true) {
        int x = readInt(prompt);
        if (x >= minVal) return x;
        cout << "Число должно быть >= " << minVal << ".\n";
    }
}

// Считать число в диапазоне [l; r]
static int readIntRange(const std::string& prompt, int l, int r) {
    using namespace std;
    while (true) {
        int x = readInt(prompt);
        if (x >= l && x <= r) return x;
        cout << "Число должно быть в диапазоне [" << l << "; " << r << "].\n";
    }
}

// Заполнить исходный набор 3 способами
static bool fillSource3Ways(std::vector<int>& src, int minCount) {
    using namespace std;
    src.clear();

    int mode = readIntRange("Заполнение: 1-клавиатура, 2-файл, 3-случайно: ", 1, 3);

    // 1) Клавиатура
    if (mode == 1) {
        int n = readIntMin("Введите количество элементов: ", minCount);
        for (int i = 0; i < n; ++i) {
            int x = readInt("Введите число: ");
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

        vector<int> temp((istream_iterator<int>(fin)), istream_iterator<int>());
        if ((int)temp.size() < minCount) return false;

        src = temp;
        return true;
    }

    // 3) Случайно
    int n = readIntMin("Введите количество элементов: ", minCount);
    int l = readInt("Введите left: ");
    int r = readInt("Введите right: ");

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

static bool fillVectorForSTL3Alg47(std::vector<int>& src) {
    using namespace std;
    src.clear();

    int mode = readIntRange("Заполнение: 1-клавиатура, 2-файл, 3-случайно: ", 1, 3);

    // 1) Клавиатура
    if (mode == 1) {
        int n;
        do {
            n = readIntMin("Введите количество элементов (четное): ", 2);
            if (n % 2 != 0) {
                cout << "Количество элементов должно быть четным.\n";
            }
        } while (n % 2 != 0);

        cout << "Первая половина должна быть уже отсортирована по возрастанию.\n";
        for (int i = 0; i < n; ++i) {
            int x = readInt("Введите число: ");
            src.push_back(x);
        }

        bool ok = true;
        for (int i = 1; i < n / 2; ++i) {
            if (src[i - 1] > src[i]) {
                ok = false;
                break;
            }
        }

        if (!ok) {
            cout << "Ошибка: первая половина не отсортирована.\n";
            return false;
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

        vector<int> temp((istream_iterator<int>(fin)), istream_iterator<int>());

        if (temp.size() < 2 || temp.size() % 2 != 0) return false;

        bool ok = true;
        for (size_t i = 1; i < temp.size() / 2; ++i) {
            if (temp[i - 1] > temp[i]) {
                ok = false;
                break;
            }
        }

        if (!ok) return false;

        src = temp;
        return true;
    }

    // 3) Случайно
    int n;
    do {
        n = readIntMin("Введите количество элементов (четное): ", 2);
        if (n % 2 != 0) {
            cout << "Количество элементов должно быть четным.\n";
        }
    } while (n % 2 != 0);

    int l = readInt("Введите left: ");
    int r = readInt("Введите right: ");
    if (l > r) swap(l, r);

    static bool seeded = false;
    if (!seeded) {
        srand((unsigned)time(nullptr));
        seeded = true;
    }

    for (int i = 0; i < n; ++i) {
        int x = l + rand() % (r - l + 1);
        src.push_back(x);
    }

    sort(src.begin(), src.begin() + n / 2);

    cout << "Сгенерировано: ";
    for (vector<int>::iterator it = src.begin(); it != src.end(); ++it) {
        cout << *it << ' ';
    }
    cout << '\n';

    return true;
}

// Заполнить список слов 3 способами
static bool fillWords3Ways(std::vector<std::string>& src, int minCount) {
    using namespace std;
    src.clear();

    int mode = readIntRange("Заполнение: 1-клавиатура, 2-файл, 3-случайно: ", 1, 3);

    // 1) Клавиатура
    if (mode == 1) {
        int n = readIntMin("Введите количество слов: ", minCount);
        for (int i = 0; i < n; ++i) {
            string s;
            cout << "Введите слово: ";
            cin >> s;
            src.push_back(s);
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

        vector<string> temp((istream_iterator<string>(fin)), istream_iterator<string>());
        if ((int)temp.size() < minCount) return false;

        src = temp;
        return true;
    }

    // 3) Случайно
    static const string words[] = {
        "ABC", "DEF", "KLM", "XYZ", "DOG", "CAT", "SUN", "MOON", "CODE", "TREE"
    };

    static bool seeded = false;
    if (!seeded) {
        srand((unsigned)time(nullptr));
        seeded = true;
    }

    int n = readIntMin("Введите количество слов: ", minCount);

    cout << "Сгенерировано: ";
    for (int i = 0; i < n; ++i) {
        string s = words[rand() % 10];
        cout << s << ' ';
        src.push_back(s);
    }
    cout << '\n';

    return true;
}


// 1 Задание

void STL3Alg3(){
    using namespace std;
    vector<int>source;

    if (!fillSource3Ways(source, 1)) {
        cout << "Ошибка заполнения\n";
        return;
    }

    list<int> L(source.begin(), source.end());

    cout << "Список до обработки: ";
    for (list<int>::iterator it = L.begin(); it != L.end(); ++it) {
        cout << *it << ' ';
    }
    cout << '\n';

    //первый ноль 
    list<int>::iterator firstZero = find(L.begin(), L.end(), 0);
    //последний ноль
    list<int>::reverse_iterator lastZeroR = find(L.rbegin(), L.rend(), 0);
    
    if (firstZero == L.end()) {
        cout << "Нулевых элементов нет\n";
        cout << "Список после обработки: ";
        for (list<int>::iterator it = L.begin(); it != L.end(); ++it) {
            cout << *it << ' ';
        }
        cout << '\n';
        return;
    }

    list<int>::iterator lastZero = lastZeroR.base();
    lastZero--;

        // Если ноль один, удаляем только его
    if (firstZero == lastZero) {
        L.erase(firstZero);
    } else {
        // Сначала удаляем последний, потом первый
        L.erase(lastZero);
        L.erase(firstZero);
    }

     cout << "Список после обработки: ";
    for (list<int>::iterator it = L.begin(); it != L.end(); ++it) {
        cout << *it << ' ';
    }
    cout << '\n';

}

// Задание 2: STL3Alg19
void STL3Alg19() {
    using namespace std;
    deque<int> D;
    vector<int> source;

    if (!fillSource3Ways(source, 0)) {
        cout << "Ошибка заполнения\n";
        return;
    }

    D = deque<int>(source.begin(), source.end());

    int N = readIntMin("Введите N (> 0): ", 1);

    cout << "Дек до обработки: ";
    for (deque<int>::iterator it = D.begin(); it != D.end(); ++it) {
        cout << *it << ' ';
    }
    cout << '\n';

    int cur = N + 1;

    DecGenerator gen(cur);

    generate_n(front_inserter(D), N, gen);
    cur = N + 1;
    generate_n(back_inserter(D), N, gen);

    cout << "Дек после обработки: ";
    for (deque<int>::iterator it = D.begin(); it != D.end(); ++it) {
        cout << *it << ' ';
    }
    cout << '\n';
}

// Задание 3: STL3Alg47
void STL3Alg47() {
    using namespace std;
    vector<int> source;
    
    if (!fillVectorForSTL3Alg47(source)) {
        cout << "Ошибка заполнения\n";
        return;
    }

    vector<int> V(source.begin(), source.end());

    cout << "Вектор до обработки: ";
    for (vector<int>::iterator it = V.begin(); it != V.end(); ++it) {
        cout << *it << ' ';
    }
    cout << '\n';

    vector<int>::iterator mid = V.begin() + V.size() / 2;

    sort(mid, V.end());

    cout << "После sort второй половины: ";
    for (vector<int>::iterator it = V.begin(); it != V.end(); ++it) {
        cout << *it << ' ';
    }
    cout << '\n';

    inplace_merge(V.begin(), mid, V.end());

    cout << "После inplace_merge: ";
    for (vector<int>::iterator it = V.begin(); it != V.end(); ++it) {
        cout << *it << ' ';
    }
    cout << '\n';
}

// Задание 4: STL3Alg61
void STL3Alg61() {
    using namespace std;
    vector<string> source;

    if (!fillWords3Ways(source, 2)) {
        cout << "Ошибка заполнения\n";
        return;
    }

    list<string> L(source.begin(), source.end());
    deque<string> D;

    cout << "Список слов L: ";
    for (list<string>::iterator it = L.begin(); it != L.end(); ++it) {
        cout << *it << ' ';
    }
    cout << '\n';

    adjacent_difference(
    L.begin(),
    L.end(),
    back_inserter(D),
    PairWordBuilder()
    );

    // adjacent_difference первым элементом копирует первый элемент списка,
    // поэтому его надо удалить
    if (!D.empty()) {
        D.erase(D.begin());
    }

    cout << "Дек D: ";
    for (deque<string>::iterator it = D.begin(); it != D.end(); ++it) {
        cout << *it << ' ';
    }
    cout << '\n';
}
