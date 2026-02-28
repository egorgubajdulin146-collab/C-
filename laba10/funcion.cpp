#include "funcion.h"

#include <cstdlib>
#include <fstream>
#include <iostream>

using namespace std;

// создать пустой стек
Stack::Stack() : top_(nullptr) {}

// создать копию стека
Stack::Stack(const Stack& other) : top_(nullptr) {
    copyFrom(other);
}

// присвоить один стек другому
Stack& Stack::operator=(const Stack& other) {
    if (this != &other) {
        clear();
        copyFrom(other);
    }
    return *this;
}

// удалить стек и освободить память
Stack::~Stack() {
    clear();
}

// скопировать данные из другого стека
void Stack::copyFrom(const Stack& other) {
    Node* rev = nullptr;
    for (Node* p = other.top_; p != nullptr; p = p->next) {
        rev = new Node(p->data, rev);
    }

    while (rev) {
        push(rev->data);
        Node* t = rev;
        rev = rev->next;
        delete t;
    }
}

// добавить элемент в вершину стека
void Stack::push(int value) {
    top_ = new Node(value, top_);
}

// извлечь верхний элемент стека
bool Stack::pop(int& value) {
    if (!top_) return false;

    Node* p = top_;
    value = p->data;
    top_ = top_->next;
    delete p;
    return true;
}

// найти значение в стеке
bool Stack::find(int value) const {
    for (Node* p = top_; p != nullptr; p = p->next) {
        if (p->data == value) return true;
    }
    return false;
}

// проверить, пуст ли стек
bool Stack::isEmpty() const {
    return top_ == nullptr;
}

// очистить стек
void Stack::clear() {
    while (top_) {
        Node* p = top_;
        top_ = top_->next;
        delete p;
    }
}

// вывести стек
void Stack::print() const {
    cout << "stack: ";
    for (Node* p = top_; p != nullptr; p = p->next) {
        cout << p->data << ' ';
    }
    cout << '\n';
}

// получить адрес вершины стека
const void* Stack::topAddress() const {
    return static_cast<const void*>(top_);
}

// заполнить стек с клавиатуры
bool Stack::fillKeyboard(int minN) {
    clear();

    int n = 0;
    cout << "Введите количество элементов: ";
    cin >> n;
    if (n < minN) return false;

    cout << "Введите " << n << " чисел: ";
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        push(x);
    }

    return true;
}

// заполнить стек из файла
bool Stack::fillFile(const string& fileName, int minN) {
    clear();

    ifstream fin(fileName);
    if (!fin.is_open()) return false;

    int n = 0;
    fin >> n;
    if (n < minN) return false;

    for (int i = 0; i < n; ++i) {
        int x;
        fin >> x;
        push(x);
    }

    return true;
}

// заполнить стек случайными числами
bool Stack::fillRandom(int n, int l, int r, int minN) {
    clear();

    if (n < minN) return false;
    if (l > r) {
        int t = l;
        l = r;
        r = t;
    }

    cout << "Сгенерировано: ";
    for (int i = 0; i < n; ++i) {
        int x = l + rand() % (r - l + 1);
        cout << x << ' ';
        push(x);
    }
    cout << '\n';

    return true;
}

// dynamic6: извлечь 9 верхних элементов стека
void Stack::solveDynamic6() {
    cout << "Извлекаем 9 элементов: ";
    for (int i = 0; i < 9; ++i) {
        int x;
        if (!pop(x)) break;
        cout << x << ' ';
    }
    cout << '\n';

    if (top_) cout << "P2 = " << topAddress() << '\n';
    else cout << "P2 = nullptr\n";
}

// создать пустую очередь
QueueDS::QueueDS() : head_(nullptr), tail_(nullptr) {}

// создать копию очереди
QueueDS::QueueDS(const QueueDS& other) : head_(nullptr), tail_(nullptr) {
    copyFrom(other);
}

// присвоить одну очередь другой
QueueDS& QueueDS::operator=(const QueueDS& other) {
    if (this != &other) {
        clear();
        copyFrom(other);
    }
    return *this;
}

// удалить очередь и освободить память
QueueDS::~QueueDS() {
    clear();
}

// скопировать данные из другой очереди
void QueueDS::copyFrom(const QueueDS& other) {
    for (Node* p = other.head_; p != nullptr; p = p->next) {
        enqueue(p->data);
    }
}

// добавить элемент в конец очереди
void QueueDS::enqueue(int value) {
    Node* p = new Node(value);

    if (!head_) {
        head_ = tail_ = p;
    } else {
        tail_->next = p;
        tail_ = p;
    }
}

// удалить элемент из начала очереди
bool QueueDS::dequeue(int& value) {
    if (!head_) return false;

    Node* p = head_;
    value = p->data;
    head_ = head_->next;
    if (!head_) tail_ = nullptr;

    delete p;
    return true;
}

// найти значение в очереди
bool QueueDS::find(int value) const {
    for (Node* p = head_; p != nullptr; p = p->next) {
        if (p->data == value) return true;
    }
    return false;
}

// проверить, пуста ли очередь
bool QueueDS::isEmpty() const {
    return head_ == nullptr;
}

// очистить очередь
void QueueDS::clear() {
    while (head_) {
        Node* p = head_;
        head_ = head_->next;
        delete p;
    }
    tail_ = nullptr;
}

// вывести очередь
void QueueDS::print() const {
    cout << "queue: ";
    for (Node* p = head_; p != nullptr; p = p->next) {
        cout << p->data << ' ';
    }
    cout << '\n';
}

// получить адрес головы очереди
const void* QueueDS::headAddress() const {
    Node* p = head_;
    int f= head_->data;
    return static_cast<const void*>(f);
}

// получить адрес хвоста очереди
const void* QueueDS::tailAddress() const {
    return static_cast<const void*>(tail_);
}

// заполнить очередь с клавиатуры
bool QueueDS::fillKeyboard() {
    clear();

    int n = 0;
    cout << "Введите количество элементов: ";
    cin >> n;
    if (n < 0) return false;

    cout << "Введите " << n << " чисел: ";
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        enqueue(x);
    }

    return true;
}

// заполнить очередь из файла
bool QueueDS::fillFile(const string& fileName) {
    clear();

    ifstream fin(fileName);
    if (!fin.is_open()) return false;

    int n = 0;
    fin >> n;
    if (n < 0) return false;

    for (int i = 0; i < n; ++i) {
        int x;
        fin >> x;
        enqueue(x);
    }

    return true;
}

// заполнить очередь случайными числами
bool QueueDS::fillRandom(int n, int l, int r) {
    clear();

    if (n < 0) return false;
    if (l > r) {
        int t = l;
        l = r;
        r = t;
    }

    cout << "Сгенерировано: ";
    for (int i = 0; i < n; ++i) {
        int x = l + rand() % (r - l + 1);
        cout << x << ' ';
        enqueue(x);
    }
    cout << '\n';

    return true;
}

// dynamic21: перенести все элементы первой очереди во вторую
void QueueDS::moveAllTo(QueueDS& second) {
    if (!head_) return;

    if (!second.head_) {
        second.head_ = head_;
        second.tail_ = tail_;
    } else {
        second.tail_->next = head_;
        second.tail_ = tail_;
    }

    head_ = nullptr;
    tail_ = nullptr;
}

// создать пустой список
SinglyList::SinglyList() : head_(nullptr), tail_(nullptr) {}

// создать копию списка
SinglyList::SinglyList(const SinglyList& other) : head_(nullptr), tail_(nullptr) {
    copyFrom(other);
}

// присвоить один список другому
SinglyList& SinglyList::operator=(const SinglyList& other) {
    if (this != &other) {
        clear();
        copyFrom(other);
    }
    return *this;
}

// удалить список и освободить память
SinglyList::~SinglyList() {
    clear();
}

// скопировать данные из другого списка
void SinglyList::copyFrom(const SinglyList& other) {
    for (Node* p = other.head_; p != nullptr; p = p->next) {
        pushBack(p->data);
    }
}

// добавить элемент в конец списка
void SinglyList::pushBack(int value) {
    Node* p = new Node(value);

    if (!head_) {
        head_ = tail_ = p;
    } else {
        tail_->next = p;
        tail_ = p;
    }
}

// найти значение в списке
bool SinglyList::find(int value) const {
    for (Node* p = head_; p != nullptr; p = p->next) {
        if (p->data == value) return true;
    }
    return false;
}

// удалить первое вхождение значения из списка
bool SinglyList::removeFirst(int value) {
    Node* prev = nullptr;
    Node* cur = head_;

    while (cur) {
        if (cur->data == value) {
            if (!prev) head_ = cur->next;
            else prev->next = cur->next;

            if (cur == tail_) tail_ = prev;
            delete cur;
            return true;
        }
        prev = cur;
        cur = cur->next;
    }

    return false;
}

// проверить, пуст ли список
bool SinglyList::isEmpty() const {
    return head_ == nullptr;
}

// очистить список
void SinglyList::clear() {
    while (head_) {
        Node* p = head_;
        head_ = head_->next;
        delete p;
    }
    tail_ = nullptr;
}

// вывести список
void SinglyList::print() const {
    cout << "list: ";
    for (Node* p = head_; p != nullptr; p = p->next) {
        cout << p->data << ' ';
    }
    cout << '\n';
}

// получить адрес головы списка
const void* SinglyList::headAddress() const {
    return static_cast<const void*>(head_);
}

// получить адрес хвоста списка
const void* SinglyList::tailAddress() const {
    return static_cast<const void*>(tail_);
}

// заполнить список с клавиатуры
bool SinglyList::fillKeyboard(int minN) {
    clear();

    int n = 0;
    cout << "Введите количество элементов: ";
    cin >> n;
    if (n < minN) return false;

    cout << "Введите " << n << " чисел: ";
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        pushBack(x);
    }

    return true;
}

// заполнить список из файла
bool SinglyList::fillFile(const string& fileName, int minN) {
    clear();

    ifstream fin(fileName);
    if (!fin.is_open()) return false;

    int n = 0;
    fin >> n;
    if (n < minN) return false;

    for (int i = 0; i < n; ++i) {
        int x;
        fin >> x;
        pushBack(x);
    }

    return true;
}

// заполнить список случайными числами
bool SinglyList::fillRandom(int n, int l, int r, int minN) {
    clear();

    if (n < minN) return false;
    if (l > r) {
        int t = l;
        l = r;
        r = t;
    }

    cout << "Сгенерировано: ";
    for (int i = 0; i < n; ++i) {
        int x = l + rand() % (r - l + 1);
        cout << x << ' ';
        pushBack(x);
    }
    cout << '\n';

    return true;
}

// listwork4: получить адрес 5-го элемента
const void* SinglyList::fifthAddress() const {
    Node* p = head_;
    for (int i = 1; i < 5 && p; ++i) {
        p = p->next;
    }
    return static_cast<const void*>(p);
}

// listwork4: получить значение 5-го элемента
bool SinglyList::fifthValue(int& value) const {
    Node* p = head_;
    for (int i = 1; i < 5 && p; ++i) {
        p = p->next;
    }
    if (!p) return false;
    value = p->data;
    return true;
}

// listwork25: вставить M перед каждым вторым элементом
void SinglyList::insertBeforeEachSecond(int m) {
    if (!head_ || !head_->next) return;

    Node* prev = head_;
    Node* curr = head_->next;
    int pos = 2;

    while (curr) {
        if (pos % 2 == 0) {
            Node* ins = new Node(m);
            prev->next = ins;
            ins->next = curr;

            prev = curr;
            curr = curr->next;
            ++pos;
        } else {
            prev = curr;
            curr = curr->next;
            ++pos;
        }
    }

    tail_ = head_;
    while (tail_ && tail_->next) tail_ = tail_->next;
}

// вставить элемент в список по убыванию
void SinglyList::insertSortedDesc(int value) {
    Node* p = new Node(value);

    if (!head_) {
        head_ = tail_ = p;
        return;
    }

    if (value > head_->data) {
        p->next = head_;
        head_ = p;
        return;
    }

    Node* cur = head_;
    while (cur->next && cur->next->data >= value) {
        cur = cur->next;
    }

    p->next = cur->next;
    cur->next = p;

    if (!p->next) tail_ = p;
}

// listwork62: построить список по убыванию из файла
bool SinglyList::buildSortedDescFromFile(const string& fileName) {
    clear();

    ifstream fin(fileName);
    if (!fin.is_open()) return false;

    int n = 0;
    fin >> n;
    if (n < 0) return false;

    for (int i = 0; i < n; ++i) {
        int x;
        fin >> x;
        insertSortedDesc(x);
    }

    return true;
}
