#include "funcion.h"

#include <fstream>
#include <iostream>
#include <limits>
#include <string>
#include <cstdlib>
#include <cctype>

using namespace std;

// проверить и считать целое число
static int readInt(const string& prompt) {
    while (true) {
        cout << prompt;
        string s;
        if (!(cin >> s)) continue;

        try {
            size_t pos = 0;
            int x = stoi(s, &pos);
            if (pos == s.size()) return x; // вся строка число
        } catch (...) {}

        cout << "Ошибка ввода. Введите целое число.\n";
    }
}


// проверить и считать целое число не меньше minVal
static int readIntMin(const string& prompt, int minVal) {
    while (true) {
        int x = readInt(prompt);
        if (x >= minVal) return x;
        cout << "Число должно быть >= " << minVal << ".\n";
    }
}

// проверить и считать целое число в диапазоне [l; r]
static int readIntRange(const string& prompt, int l, int r) {
    while (true) {
        int x = readInt(prompt);
        if (x >= l && x <= r) return x;
        cout << "Число должно быть в диапазоне [" << l << "; " << r << "].\n";
    }
}

// создать Node
Node::Node(int value) : data(value), next(nullptr) {}

// создать PNode
PNode::PNode(int value) : data(value), prev(nullptr), next(nullptr) {}

// создать пустой CircularList
CircularList::CircularList() : head(nullptr), sizeList(0) {}

// создать копию CircularList
CircularList::CircularList(const CircularList& other) : head(nullptr), sizeList(0) {
    copyFrom(other);
}

// присвоение CircularList
CircularList& CircularList::operator=(const CircularList& other) {
    if (this != &other) {
        clear();
        copyFrom(other);
    }
    return *this;
}

// удалить CircularList
CircularList::~CircularList() {
    clear();
}

// проверить пустой ли CircularList
bool CircularList::empty() const {
    return head == nullptr;
}

// получить размер CircularList
int CircularList::size() const {
    return sizeList;
}

// получить хвост CircularList
Node* CircularList::getTail() const {
    if (!head) return nullptr;

    Node* tail = head;
    while (tail->next != head) {
        tail = tail->next;
    }
    return tail;
}

// скопировать CircularList
void CircularList::copyFrom(const CircularList& other) {
    if (!other.head) return;

    Node* cur = other.head;
    for (int i = 0; i < other.sizeList; ++i) {
        pushBack(cur->data);
        cur = cur->next;
    }
}

// добавить в конец CircularList
void CircularList::pushBack(int value) {
    Node* node = new Node(value);

    if (!head) {
        head = node;
        node->next = node;
        sizeList = 1;
        return;
    }

    Node* tail = getTail();
    tail->next = node;
    node->next = head;
    ++sizeList;
}

// удалить первое вхождение из CircularList
bool CircularList::removeFirst(int value) {
    if (!head) return false;

    Node* cur = head;
    Node* prev = getTail();

    for (int i = 0; i < sizeList; ++i) {
        if (cur->data == value) {
            if (sizeList == 1) {
                delete cur;
                head = nullptr;
                sizeList = 0;
                return true;
            }

            prev->next = cur->next;
            if (cur == head) head = cur->next;

            delete cur;
            --sizeList;
            return true;
        }

        prev = cur;
        cur = cur->next;
    }

    return false;
}

// поиск значения в CircularList
bool CircularList::contains(int value) const {
    if (!head) return false;

    Node* cur = head;
    for (int i = 0; i < sizeList; ++i) {
        if (cur->data == value) return true;
        cur = cur->next;
    }
    return false;
}

// очистить CircularList
void CircularList::clear() {
    while (!empty()) {
        removeFirst(head->data);
    }
}

// вывести CircularList
void CircularList::print() const {
    cout << "list: ";
    if (!head) {
        cout << "nullptr\n";
        return;
    }

    Node* cur = head;
    for (int i = 0; i < sizeList; ++i) {
        cout << cur->data << ' ';
        cur = cur->next;
    }
    cout << '\n';
}

// заполнить CircularList с клавиатуры
bool CircularList::fillKeyboard(int minCount) {
    clear();

    int n = readIntMin("Введите количество элементов: ", minCount);
    for (int i = 0; i < n; ++i) {
        int x = readInt("Введите число: ");
        pushBack(x);
    }
    return true;
}

// заполнить CircularList из файла
bool CircularList::fillFile(const string& fileName, int minCount) {
    clear();

    ifstream fin(fileName);
    if (!fin.is_open()) return false;

    int n = 0;
    if (!(fin >> n) || n < minCount) return false;

    for (int i = 0; i < n; ++i) {
        int x = 0;
        if (!(fin >> x)) return false;
        pushBack(x);
    }
    return true;
}

// заполнить CircularList случайными числами
bool CircularList::fillRandom(int n, int left, int right, int minCount) {
    clear();

    if (n < minCount) return false;
    if (left > right) {
        int t = left;
        left = right;
        right = t;
    }

    cout << "Сгенерировано: ";
    for (int i = 0; i < n; ++i) {
        int x = left + rand() % (right - left + 1);
        cout << x << ' ';
        pushBack(x);
    }
    cout << '\n';
    return true;
}

// ListWork69: вывести в файл с шагом k и удалить элементы
bool CircularList::writeByStepAndErase(int k, const string& outFileName) {
    if (k <= 0) return false;

    ofstream fout(outFileName);
    if (!fout.is_open()) return false;
    if (empty()) return true;

    bool firstWrite = true;
    Node* prev = getTail();
    Node* cur = head;

    while (!empty()) {
        // сначала выводим текущий
        if (!firstWrite) fout << ' ';
        fout << cur->data;
        firstWrite = false;

        // удаляем текущий
        if (sizeList == 1) {
            delete cur;
            head = nullptr;
            sizeList = 0;
            break;
        }

        prev->next = cur->next;
        if (cur == head) head = cur->next;

        Node* del = cur;
        cur = cur->next;
        delete del;
        --sizeList;

        // потом делаем шаг k-1
        for (int i = 1; i < k; ++i) {
            prev = cur;
            cur = cur->next;
        }
    }

    return true;
}

// создать пустой DoublyList
DoublyList::DoublyList() : head(nullptr), tail(nullptr), sizeList(0) {}

// создать копию DoublyList
DoublyList::DoublyList(const DoublyList& other) : head(nullptr), tail(nullptr), sizeList(0) {
    copyFrom(other);
}

// присвоение DoublyList
DoublyList& DoublyList::operator=(const DoublyList& other) {
    if (this != &other) {
        clear();
        copyFrom(other);
    }
    return *this;
}

// удалить DoublyList
DoublyList::~DoublyList() {
    clear();
}

// скопировать DoublyList
void DoublyList::copyFrom(const DoublyList& other) {
    for (PNode* p = other.head; p != nullptr; p = p->next) {
        pushBack(p->data);
    }
}

// проверить пустой ли DoublyList
bool DoublyList::empty() const {
    return head == nullptr;
}

// получить размер DoublyList
int DoublyList::size() const {
    return sizeList;
}

// добавить в конец DoublyList
void DoublyList::pushBack(int value) {
    PNode* node = new PNode(value);

    if (!head) {
        head = tail = node;
        sizeList = 1;
        return;
    }

    tail->next = node;
    node->prev = tail;
    tail = node;
    ++sizeList;
}

// удалить первое вхождение из DoublyList
bool DoublyList::removeFirstValue(int value) {
    PNode* p = head;

    while (p) {
        if (p->data == value) {
            PNode* left = p->prev;
            PNode* right = p->next;

            if (left) left->next = right;
            else head = right;

            if (right) right->prev = left;
            else tail = left;

            delete p;
            --sizeList;
            return true;
        }
        p = p->next;
    }

    return false;
}

// поиск значения в DoublyList
bool DoublyList::contains(int value) const {
    for (PNode* p = head; p != nullptr; p = p->next) {
        if (p->data == value) return true;
    }
    return false;
}

// очистить DoublyList
void DoublyList::clear() {
    PNode* p = head;
    while (p) {
        PNode* nxt = p->next;
        delete p;
        p = nxt;
    }
    head = nullptr;
    tail = nullptr;
    sizeList = 0;
}

// вывести DoublyList слева направо
void DoublyList::printForward() const {
    cout << "list forward: ";
    for (PNode* p = head; p != nullptr; p = p->next) {
        cout << p->data << ' ';
    }
    cout << '\n';
}

// вывести DoublyList справа налево
void DoublyList::printBackward() const {
    cout << "list backward: ";
    for (PNode* p = tail; p != nullptr; p = p->prev) {
        cout << p->data << ' ';
    }
    cout << '\n';
}

// заполнить DoublyList с клавиатуры
bool DoublyList::fillKeyboard(int minCount) {
    clear();

    int n = readIntMin("Введите количество элементов: ", minCount);
    for (int i = 0; i < n; ++i) {
        int x = readInt("Введите число: ");
        pushBack(x);
    }
    return true;
}

// заполнить DoublyList из файла
bool DoublyList::fillFile(const string& fileName, int minCount) {
    clear();

    ifstream fin(fileName);
    if (!fin.is_open()) return false;

    int n = 0;
    if (!(fin >> n) || n < minCount) return false;

    for (int i = 0; i < n; ++i) {
        int x = 0;
        if (!(fin >> x)) return false;
        pushBack(x);
    }
    return true;
}

// заполнить DoublyList случайными числами
bool DoublyList::fillRandom(int n, int left, int right, int minCount) {
    clear();

    if (n < minCount) return false;
    if (left > right) {
        int t = left;
        left = right;
        right = t;
    }

    cout << "Сгенерировано: ";
    for (int i = 0; i < n; ++i) {
        int x = left + rand() % (right - left + 1);
        cout << x << ' ';
        pushBack(x);
    }
    cout << '\n';
    return true;
}

// ListWork41: вывести min, max и элементы между ними
void DoublyList::printBetweenMinMax() const {
    if (!head || !head->next) {
        cout << "Список слишком короткий\n";
        return;
    }

    PNode* minNode = head;
    PNode* maxNode = head;

    for (PNode* p = head->next; p != nullptr; p = p->next) {
        if (p->data < minNode->data) minNode = p;
        if (p->data > maxNode->data) maxNode = p;
    }

    cout << "min = " << minNode->data << ", max = " << maxNode->data << '\n';

    if (minNode == maxNode) {
        cout << "Элементов между min и max нет\n";
        return;
    }

    PNode* left = minNode;
    PNode* right = maxNode;

    for (PNode* p = head; p != nullptr; p = p->next) {
        if (p == minNode) break;
        if (p == maxNode) {
            left = maxNode;
            right = minNode;
            break;
        }
    }

    cout << "Элементы между min и max: ";
    bool has = false;
    for (PNode* p = left->next; p != nullptr && p != right; p = p->next) {
        cout << p->data << ' ';
        has = true;
    }

    if (!has) cout << "(нет)";
    cout << '\n';
}

// ListWork63: вывести в файл в обратном порядке и удалить все
bool DoublyList::writeReverseAndErase(const string& outFileName) {
    ofstream fout(outFileName);
    if (!fout.is_open()) return false;

    bool first = true;
    while (tail) {
        if (!first) fout << ' ';
        fout << tail->data;
        first = false;

        PNode* del = tail;
        if (head == tail) {
            head = nullptr;
            tail = nullptr;
        } else {
            tail = tail->prev;
            tail->next = nullptr;
        }

        delete del;
        --sizeList;
    }

    sizeList = 0;
    return true;
}

// ListWork46: преобразовать линейный двусвязный список в циклический с барьером
PNode* DoublyList::makeBarrierCycle(){
    PNode* barrier = new PNode(0);

    if(!head){
        barrier->next = barrier;
        barrier->prev = barrier;
        return barrier;
    }

    barrier->next = head;
    barrier->prev = tail;
    head->prev = barrier;
    tail->next = barrier;
    head = nullptr;
    tail = nullptr;
    sizeList = 0;

    return barrier;
}

// вывести циклический список с барьером
void DoublyList::printBarrierCycle(PNode* barrier){
    using namespace std;
    if (!barrier) {
        cout << "barrier = nullptr\n";
        return;
    }

    cout << "barrier = " << barrier << " (data = " << barrier->data << ")\n";
    cout << "cycle: |B| ";

    PNode* cur = barrier->next;
    if (cur == barrier) {
        cout << "-> |B|\n";
        return;
    }

    while (cur != barrier) {
        cout << "-> " << cur->data << ' ';
        cur = cur->next;
    }

    cout << "-> |B|\n";
}

// очистить циклический список с барьером
void DoublyList::clearBarrierCycle(PNode*& barrier) {
    if (!barrier) return;

    PNode* cur = barrier->next;
    while (cur != barrier) {
        PNode* nxt = cur->next;
        delete cur;
        cur = nxt;
    }

    delete barrier;
    barrier = nullptr;
}

// выбрать способ заполнения CircularList
static bool fillCircularByMode(CircularList& list, int minCount) {
    int mode = readIntRange("Заполнение: 1-клавиатура, 2-файл, 3-случайно: ", 1, 3);

    if (mode == 1) return list.fillKeyboard(minCount);

    if (mode == 2) {
        string fileName;
        cout << "Имя входного файла: ";
        cin >> fileName;
        return list.fillFile(fileName, minCount);
    }

    int n = readIntMin("Введите n: ", minCount);
    int l = readInt("Введите left: ");
    int r = readInt("Введите right: ");
    return list.fillRandom(n, l, r, minCount);
}

// выбрать способ заполнения DoublyList
static bool fillDoublyByMode(DoublyList& list, int minCount) {
    int mode = readIntRange("Заполнение: 1-клавиатура, 2-файл, 3-случайно: ", 1, 3);

    if (mode == 1) return list.fillKeyboard(minCount);

    if (mode == 2) {
        string fileName;
        cout << "Имя входного файла: ";
        cin >> fileName;
        return list.fillFile(fileName, minCount);
    }

    int n = readIntMin("Введите n: ", minCount);
    int l = readInt("Введите left: ");
    int r = readInt("Введите right: ");
    return list.fillRandom(n, l, r, minCount);
}

bool onlyLetters(const string& s) {
    if (s.empty()) return false;
    for (char ch : s) {
        if (!isalpha(static_cast<unsigned char>(ch))) return false;
    }
    return true;
}

// считать строку из файла (первая непустая строка)
static bool readLineFromFile(const string& fileName, string& s) {
    ifstream fin(fileName);
    if (!fin.is_open()) return false;

    while (getline(fin, s)) {
        if (!s.empty() && s.back() == '\r') s.pop_back();
        if (!s.empty()) return true;
    }

    return false;
}

// запуск задания 1 (ListWork69)
void ListWork69() {
    CircularList list;

    if (!fillCircularByMode(list, 1)) {
        cout << "Ошибка заполнения\n";
        return;
    }

    cout << "Исходный список:\n";
    list.print();

    int addValue = readInt("Добавить элемент: ");
    list.pushBack(addValue);
    cout << "После добавления:\n";
    list.print();

    int findValue = readInt("Поиск значения: ");
    cout << (list.contains(findValue) ? "Найдено\n" : "Не найдено\n");

    int delValue = readInt("Удалить значение: ");
    cout << (list.removeFirst(delValue) ? "Удалено\n" : "Не найдено\n");
    cout << "После удаления:\n";
    list.print();

    CircularList copied(list);
    cout << "Копия списка:\n";
    copied.print();

    int k = readIntMin("Введите шаг k: ", 1);
    string outFile;
    cout << "Имя выходного файла: ";
    cin >> outFile;

    if (!list.writeByStepAndErase(k, outFile)) {
        cout << "Ошибка выполнения задания 1\n";
        return;
    }

    cout << "Готово. Результат в файле: " << outFile << '\n';
    cout << "Список после удаления:\n";
    list.print();
}

// запуск задания 2 (ListWork41)
void ListWork41() {
    DoublyList list;

    if (!fillDoublyByMode(list, 2)) {
        cout << "Ошибка заполнения\n";
        return;
    }

    cout << "Исходный список:\n";
    list.printForward();

    DoublyList copied(list);
    cout << "Копия списка:\n";
    copied.printForward();

    int addValue = readInt("Добавить элемент в копию: ");
    copied.pushBack(addValue);
    cout << "Копия после добавления:\n";
    copied.printForward();

    int findValue = readInt("Поиск в копии: ");
    cout << (copied.contains(findValue) ? "Найдено\n" : "Не найдено\n");

    int delValue = readInt("Удалить из копии: ");
    cout << (copied.removeFirstValue(delValue) ? "Удалено\n" : "Не найдено\n");
    cout << "Копия после удаления:\n";
    copied.printForward();

    list.printBetweenMinMax();
}

// запуск задания 3 (ListWork63)
void ListWork63() {
    DoublyList list;

    if (!fillDoublyByMode(list, 1)) {
        cout << "Ошибка заполнения\n";
        return;
    }

    cout << "Исходный список:\n";
    list.printForward();

    int findValue = readInt("Поиск значения: ");
    cout << (list.contains(findValue) ? "Найдено\n" : "Не найдено\n");

    string outFile;
    cout << "Имя выходного файла: ";
    cin >> outFile;

    if (!list.writeReverseAndErase(outFile)) {
        cout << "Ошибка записи в файл\n";
        return;
    }

    cout << "Готово. Вывод в обратном порядке записан в: " << outFile << '\n';
    cout << "Список после удаления всех элементов:\n";
    list.printForward();
}

// запуск задания 4 (ListWork46)
void ListWork46() {
    using namespace std;

    DoublyList list;

    // можно пустой список, по условию это допустимо
    if (!fillDoublyByMode(list, 0)) {
        cout << "Ошибка заполнения\n";
        return;
    }

    cout << "Исходный линейный список:\n";
    list.printForward();

    PNode* barrier = list.makeBarrierCycle();

    cout << "После преобразования в циклический с барьером:\n";
    DoublyList::printBarrierCycle(barrier);

    // освобождаем память
    DoublyList::clearBarrierCycle(barrier);
}

// запуск задания 5 (Текстовая задача 4)
void Text4() {
    using namespace std;

    string s;
    int mode = readIntRange("Ввод строки: 1-клавиатура, 2-файл: ", 1, 2);

    if (mode == 1) {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Введите строку: ";
        getline(cin, s);
    } else {
        string fileName;
        cout << "Имя файла: ";
        cin >> fileName;

        if (!readLineFromFile(fileName, s)) {
            cout << "Ошибка: не удалось прочитать строку из файла\n";
            return;
        }

        cout << "Строка из файла: " << s << '\n';
    }

    if (!onlyLetters(s)) {
        cout << "Ошибка: разрешены только буквы\n";
        return;
    }

    // Барьерный элемент
    PNode* barrier = new PNode(0);
    barrier->next = barrier;
    barrier->prev = barrier;

    // Строим циклический двусвязный список символов
    for (char ch : s) {
        PNode* node = new PNode(static_cast<unsigned char>(ch));

        node->prev = barrier->prev;
        node->next = barrier;
        barrier->prev->next = node;
        barrier->prev = node;
    }

    // Проверка симметрии
    bool symmetric = true;
    PNode* left = barrier->next;
    PNode* right = barrier->prev;

    for (size_t i = 0; i < s.size() / 2; ++i) {
        if (left->data != right->data) {
            symmetric = false;
            break;
        }
        left = left->next;
        right = right->prev;
    }

    cout << (symmetric ? "Строка симметрична\n" : "Строка не симметрична\n");

    // Очистка памяти
    PNode* cur = barrier->next;
    while (cur != barrier) {
        PNode* nxt = cur->next;
        delete cur;
        cur = nxt;
    }
    delete barrier;
}
