#include "funcion.h"

#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <iterator>
#include <set>
#include <string>
#include <vector>
#include <map>


// Считать целое число с проверкой
static int readInt(const std::string& prompt) {
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

// Вывести вектор
static void printVector(const std::vector<int>& V, const std::string& name) {
    using namespace std;
    cout << name << ": ";
    for (vector<int>::const_iterator it = V.begin(); it != V.end(); ++it) {
        cout << *it << ' ';
    }
    cout << '\n';
}

// Подготовить данные для STL5Assoc3 тремя способами
static bool fillDataForSTL5Assoc3(std::vector<int>& V0, std::vector<std::vector<int> >& allV) {
    using namespace std;
    V0.clear();
    allV.clear();

    int mode = readIntRange("Заполнение: 1-клавиатура, 2-файл, 3-случайно: ", 1, 3);

    // 1) Клавиатура
    if (mode == 1) {
        int N = readIntMin("Введите N (> 0): ", 1);
        int size0 = readIntMin("Введите размер V0: ", 0);

        for (int i = 0; i < size0; ++i) {
            V0.push_back(readInt("Введите элемент V0: "));
        }

        for (int i = 0; i < N; ++i) {
            int sizeI;
            do {
                sizeI = readIntMin("Введите размер очередного Vi: ", 0);
                if (sizeI < size0) {
                    cout << "Размер Vi должен быть не меньше размера V0.\n";
                }
            } while (sizeI < size0);

            vector<int> temp;
            for (int j = 0; j < sizeI; ++j) {
                temp.push_back(readInt("Введите элемент Vi: "));
            }
            allV.push_back(temp);
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

        int N;
        int size0;

        if (!(fin >> N) || N <= 0) return false;
        if (!(fin >> size0) || size0 < 0) return false;

        for (int i = 0; i < size0; ++i) {
            int x;
            if (!(fin >> x)) return false;
            V0.push_back(x);
        }

        for (int i = 0; i < N; ++i) {
            int sizeI;
            if (!(fin >> sizeI) || sizeI < size0) return false;

            vector<int> temp;
            for (int j = 0; j < sizeI; ++j) {
                int x;
                if (!(fin >> x)) return false;
                temp.push_back(x);
            }
            allV.push_back(temp);
        }

        return true;
    }

    // 3) Случайно
    int N = readIntMin("Введите N (> 0): ", 1);
    int size0 = readIntMin("Введите размер V0: ", 0);
    int l = readInt("Введите left: ");
    int r = readInt("Введите right: ");

    if (l > r) swap(l, r);

    static bool seeded = false;
    if (!seeded) {
        srand((unsigned)time(nullptr));
        seeded = true;
    }

    for (int i = 0; i < size0; ++i) {
        V0.push_back(l + rand() % (r - l + 1));
    }

    for (int i = 0; i < N; ++i) {
        int sizeI = size0 + rand() % 4;
        vector<int> temp;
        for (int j = 0; j < sizeI; ++j) {
            temp.push_back(l + rand() % (r - l + 1));
        }
        allV.push_back(temp);
    }

    return true;
}

// Заполнить один вектор 3 способами
static bool fillVector3Ways(std::vector<int>& V, int minCount) {
    using namespace std;
    V.clear();

    int mode = readIntRange("Заполнение: 1-клавиатура, 2-файл, 3-случайно: ", 1, 3);

    // 1) Клавиатура
    if (mode == 1) {
        int n = readIntMin("Введите количество элементов: ", minCount);
        for (int i = 0; i < n; ++i) {
            V.push_back(readInt("Введите число: "));
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

        V = temp;
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
        V.push_back(x);
    }
    cout << '\n';

    return true;
}

// Заполнить вектор слов 3 способами
static bool fillWords3Ways(std::vector<std::string>& V, int minCount) {
    using namespace std;
    V.clear();

    int mode = readIntRange("Заполнение: 1-клавиатура, 2-файл, 3-случайно: ", 1, 3);

    // 1) Клавиатура
    if (mode == 1) {
        int n = readIntMin("Введите количество слов: ", minCount);
        for (int i = 0; i < n; ++i) {
            string s;
            cout << "Введите слово: ";
            cin >> s;
            V.push_back(s);
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

        V = temp;
        return true;
    }

    // 3) Случайно
    static const string words[] = {
        "ABC", "DOG", "TREE", "CODE", "SUN", "MOON", "CAT", "BOOK", "KLM", "XYZ"
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
        V.push_back(s);
    }
    cout << '\n';

    return true;
}



// Задание 1: STL5Assoc3
void STL5Assoc3() {
    using namespace std;
    vector<int> V0;
    vector<vector<int> > allV;

    if (!fillDataForSTL5Assoc3(V0, allV)) {
        cout << "Ошибка заполнения\n";
        return;
    }

    printVector(V0, "V0");
    for (size_t i = 0; i < allV.size(); ++i) {
        printVector(allV[i], "V" + to_string(i + 1));
    }

    multiset<int> M0(V0.begin(), V0.end());

    int count = 0;

    for (vector<vector<int> >::iterator it = allV.begin(); it != allV.end(); ++it) {
        multiset<int> M(it->begin(), it->end());

        if (includes(M.begin(), M.end(), M0.begin(), M0.end())) {
            ++count;
        }
    }

    cout << "Количество подходящих векторов: " << count << '\n';
}

// Задание 2: STL5Assoc15
void STL5Assoc15() {
    using namespace std;
    vector<int> V;

    if (!fillVector3Ways(V, 1)) {
        cout << "Ошибка заполнения\n";
        return;
    }

    cout << "V: ";
    for (vector<int>::iterator it = V.begin(); it != V.end(); ++it) {
        cout << *it << ' ';
    }
    cout << endl;

    map<int, int> M;

    // Считаем количество повторений
    for (vector<int>::iterator it = V.begin(); it != V.end(); ++it) {
        M[*it]++;
    }

    cout << "Элемент и количество повторений:\n";
    for (map<int, int>::iterator it = M.begin(); it != M.end(); ++it) {
        cout << it->first << ' ' << it->second << endl;
    }
}


// Задание 3: STL5Assoc22
void STL5Assoc22() {
    using namespace std;
    vector<string> V;

    if (!fillWords3Ways(V, 1)) {
        cout << "Ошибка заполнения\n";
        return;
    }

    cout << "V: ";
    for (vector<string>::iterator it = V.begin(); it != V.end(); ++it) {
        cout << *it << ' ';
    }
    cout << '\n';

    multimap<char, string> M;

    //поиск ключа и пары
    for (vector<string>::reverse_iterator it = V.rbegin(); it != V.rend(); ++it) {
        char key = (*it)[it->size() - 1];
        M.insert(make_pair(key, *it));
    }

    cout << "Ключ и слово:\n";
    for (multimap<char, string>::iterator it = M.begin(); it != M.end(); ++it) {
        cout << it->first << ' ' << it->second << '\n';
    }

}
