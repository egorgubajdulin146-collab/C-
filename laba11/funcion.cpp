#include "funcion.h"
#include <cstdlib>
#include <fstream>
#include <iostream>

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
int CircularList::size() const{
    return sizeList;
}

// получить хвост CircularList
Node* CircularList::getTail() const {
    if(!head) return nullptr;

    Node* tail = head;
    while(tail->next != head){
        tail = tail->next;
    }
    return tail;
}

// скопировать CircularList
void CircularList::copyFrom(const CircularList& other){
    if(!other.head) return;

    Node* cur = other.head;
    for(int i = 0; i < other.sizeList; i++){
        pushBack(cur->data);
        cur = cur->next;
    }
}

// добавить в конец CircularList
void CircularList::pushBack(int value){
    Node* node = new Node(value);

    if (!head){
        head = node;
        node->next = node;
        sizeList = 1;
        return;
    }

    Node* tail = getTail();
    tail->next = node;
    node->next = head;
    sizeList++;
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
bool CircularList::contains(int value) const{
    if(!head) return false;

    Node* cur = head;
    for(int i = 0; i < sizeList; ++i){
        if(cur->data == value) return true;
        cur = cur->next;
    }
    return false;
}

// очистить CircularList
void CircularList::clear(){
    while(!empty()){
        removeFirst(head->data);
    }
}
void CircularList::print() const {
    using namespace std;
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
    using namespace std;
    clear();

    int n = 0;
    cout << "Введите количество элементов: ";
    cin >> n;
    if (n < minCount) return false;

    cout << "Введите " << n << " чисел: ";
    for (int i = 0; i < n; ++i) {
        int x = 0;
        cin >> x;
        pushBack(x);
    }
    return true;
}

// заполнить CircularList из файла
bool CircularList::fillFile(const std::string& fileName, int minCount) {
    using namespace std;
    clear();

    ifstream fin(fileName);
    if (!fin.is_open()) return false;

    int n = 0;
    fin >> n;
    if (n < minCount) return false;

    for (int i = 0; i < n; ++i) {
        int x = 0;
        fin >> x;
        pushBack(x);
    }
    return true;
}

// заполнить CircularList случайными числами
bool CircularList::fillRandom(int n, int left, int right, int minCount) {
    using namespace std;
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
bool CircularList::writeByStepAndErase(int k, const std::string& outFileName) {
    using namespace std;
    if (k <= 0) return false;

    ofstream fout(outFileName);
    if (!fout.is_open()) return false;
    if (empty()) return true;

    bool firstWrite = true;
    Node* prev = getTail();
    Node* cur = head;

    while (!empty()) {
        if (!firstWrite) fout << ' ';
        fout << cur->data;
        firstWrite = false;

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
    using namespace std;
    cout << "list forward: ";
    for (PNode* p = head; p != nullptr; p = p->next) cout << p->data << ' ';
    cout << '\n';
}

// вывести DoublyList справа налево
void DoublyList::printBackward() const {
    using namespace std;
    cout << "list backward: ";
    for (PNode* p = tail; p != nullptr; p = p->prev) cout << p->data << ' ';
    cout << '\n';
}

// заполнить DoublyList с клавиатуры
bool DoublyList::fillKeyboard(int minCount) {
    using namespace std;
    clear();

    int n = 0;
    cout << "Введите количество элементов: ";
    cin >> n;
    if (n < minCount) return false;

    cout << "Введите " << n << " чисел: ";
    for (int i = 0; i < n; ++i) {
        int x = 0;
        cin >> x;
        pushBack(x);
    }
    return true;
}

// заполнить DoublyList из файла
bool DoublyList::fillFile(const std::string& fileName, int minCount) {
    using namespace std;
    clear();

    ifstream fin(fileName);
    if (!fin.is_open()) return false;

    int n = 0;
    fin >> n;
    if (n < minCount) return false;

    for (int i = 0; i < n; ++i) {
        int x = 0;
        fin >> x;
        pushBack(x);
    }
    return true;
}

// заполнить DoublyList случайными числами
bool DoublyList::fillRandom(int n, int left, int right, int minCount) {
    using namespace std;
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

// ListWork41: вывести элементы между минимальным и максимальным
void DoublyList::printBetweenMinMax() const {
    using namespace std;

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

    // чтобы идти только слева направо
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


// ListWork63: вывести в файл в обратном порядке и удалять элементы
bool DoublyList::writeReverseAndErase(const std::string& outFileName) {
    using namespace std;
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

// выбрать способ заполнения CircularList
static bool fillCircularByMode(CircularList& list, int minCount) {
    using namespace std;
    int mode = 0;
    cout << "Заполнение: 1-клавиатура, 2-файл, 3-случайно: ";
    cin >> mode;

    if (mode == 1) return list.fillKeyboard(minCount);

    if (mode == 2) {
        string fileName;
        cout << "Имя входного файла: ";
        cin >> fileName;
        return list.fillFile(fileName, minCount);
    }

    if (mode == 3) {
        int n = 0, l = 0, r = 0;
        cout << "Введите n l r: ";
        cin >> n >> l >> r;
        return list.fillRandom(n, l, r, minCount);
    }

    return false;
}

// выбрать способ заполнения DoublyList
static bool fillDoublyByMode(DoublyList& list, int minCount) {
    using namespace std;
    int mode = 0;
    cout << "Заполнение: 1-клавиатура, 2-файл, 3-случайно: ";
    cin >> mode;

    if (mode == 1) return list.fillKeyboard(minCount);

    if (mode == 2) {
        string fileName;
        cout << "Имя входного файла: ";
        cin >> fileName;
        return list.fillFile(fileName, minCount);
    }

    if (mode == 3) {
        int n = 0, l = 0, r = 0;
        cout << "Введите n l r: ";
        cin >> n >> l >> r;
        return list.fillRandom(n, l, r, minCount);
    }

    return false;
}

// запуск задания 1 (ListWork69)
void ListWork69() {
    using namespace std;
    CircularList list;

    if (!fillCircularByMode(list, 1)) {
        cout << "Ошибка заполнения\n";
        return;
    }

    cout << "Исходный список:\n";
    list.print();

    int addValue = 0;
    cout << "Добавить элемент: ";
    cin >> addValue;
    list.pushBack(addValue);

    int findValue = 0;
    cout << "Поиск значения: ";
    cin >> findValue;
    cout << (list.contains(findValue) ? "Найдено\n" : "Не найдено\n");

    int delValue = 0;
    cout << "Удалить значение: ";
    cin >> delValue;
    cout << (list.removeFirst(delValue) ? "Удалено\n" : "Не найдено\n");
    list.print();

    CircularList copied(list);
    cout << "Копия списка:\n";
    copied.print();

    int k = 0;
    string outFile;
    cout << "Введите шаг k: ";
    cin >> k;
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
    using namespace std;

    DoublyList list;
    if(!fillDoublyByMode(list, 2)){
        cout << "Ошибка заполнения\n";
        return;
    }
    cout << "Исходный список:\n";
    list.printForward();

    DoublyList copied(list);
    cout << "Копия списка:\n";
    copied.printForward();

    int addValue = 0;
    cout << "Добавить элемент в копию: ";
    cin >> addValue;
    copied.pushBack(addValue);

    int findValue = 0;
    cout << "Поиск в копии: ";
    cin >> findValue;
    cout << (copied.contains(findValue) ? "Найдено\n" : "Не найдено\n");

    int delValue = 0;
    cout << "Удалить из копии: ";
    cin >> delValue;
    cout << (copied.removeFirstValue(delValue) ? "Удалено\n" : "Не найдено\n");
    copied.printForward();

    list.printBetweenMinMax();
}

// запуск задания 3 (ListWork63)
void ListWork63() {
    using namespace std;
    DoublyList list;

    if (!fillDoublyByMode(list, 1)) {
        cout << "Ошибка заполнения\n";
        return;
    }

    cout << "Исходный список:\n";
    list.printForward();

    int findValue = 0;
    cout << "Поиск значения: ";
    cin >> findValue;
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
    cout << "Задание 4 (ListWork46) пока не реализовано\n";
}

// запуск задания 5 (Текстовая задача 4)
void Text4() {
    using namespace std;
    cout << "Задание 5 (Текстовая задача 4) пока не реализовано\n";
}
