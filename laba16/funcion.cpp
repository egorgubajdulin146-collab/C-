#include "funcion.h"

#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <limits>
#include <queue>
#include <iomanip>
#include <vector>


// Считать целое число
int Check::readInt(const char* text){
    using namespace std;
    int x;
    while(true){
        cout << text;

        if(cin >> x){
            return x;
        }

        cout << "Ошибка ввода. Введите целое число.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// Считать целое число не меньше minValue
int Check::readIntMin(const char* text, int minValue) {
    using namespace std;
    while (true) {
        int x = readInt(text);

        if (x >= minValue) {
            return x;
        }

        cout << "Число должно быть >= " << minValue << ".\n";
    }
}

// Считать целое число в диапазоне
int Check::readIntRange(const char* text, int left, int right) {
    using namespace std;
    while (true) {
        int x = readInt(text);

        if (x >= left && x <= right) {
            return x;
        }

        cout << "Число должно быть в диапазоне [" << left << "; " << right << "].\n";
    }
}

// Создать узел
BinaryTree::Node::Node(int value) : data(value), left(nullptr), right(nullptr) {
}

// Получить значение узла
int BinaryTree::Node::getData() const {
    return data;
}

// Получить левый потомок
BinaryTree::Node* BinaryTree::Node::getLeft() const {
    return left;
}

// Получить правый потомок
BinaryTree::Node* BinaryTree::Node::getRight() const {
    return right;
}

// Изменить значение узла
void BinaryTree::Node::setData(int value) {
    data = value;
}

// Изменить левый потомок
void BinaryTree::Node::setLeft(BinaryTree::Node* p) {
    left = p;
}

// Изменить правый потомок
void BinaryTree::Node::setRight(BinaryTree::Node* p) {
    right = p;
}

// Создать дерево
BinaryTree::BinaryTree() : root(nullptr) {
}

// Удалить дерево
BinaryTree::~BinaryTree() {
    clear();
}

// Очистить поддерево
void BinaryTree::clear(BinaryTree::Node* p){
    if(!p) return;

    clear(p->getLeft());
    clear(p->getRight());
    delete p;
}

// Очистить дерево
void BinaryTree::clear(){
    clear(root);
    root = nullptr;
}

// Вставить значение в поддерево
void BinaryTree::insert(BinaryTree::Node*& p, int value){
    if(!p){
        p = new BinaryTree::Node(value);
        return;
    }

    if(value < p->getData()){
        BinaryTree::Node* left = p->getLeft();
        insert(left, value);
        p->setLeft(left);
    }
    else{
        BinaryTree::Node* right = p->getRight();
        insert(right, value);
        p->setRight(right);
    }
}

// Вставить значение в дерево
void BinaryTree::insert(int value) {
    insert(root, value);
}

// Построить обычное бинарное дерево по уровням слева направо
void BinaryTree::buildByLevels(const std::vector<int>& values) {
    clear();

    if (values.empty() || values[0] == -1) {
        return;
    }

    std::vector<BinaryTree::Node*> nodes(values.size(), nullptr);

    nodes[0] = new BinaryTree::Node(values[0]);

    for (size_t i = 1; i < values.size(); ++i) {
        size_t parentIndex = (i - 1) / 2;

        if (values[i] != -1 && nodes[parentIndex]) {
            nodes[i] = new BinaryTree::Node(values[i]);
        }
    }

    for (size_t i = 0; i < values.size(); ++i) {
        if (!nodes[i]) continue;

        size_t leftIndex = 2 * i + 1;
        size_t rightIndex = 2 * i + 2;

        if (leftIndex < values.size()) {
            nodes[i]->setLeft(nodes[leftIndex]);
        }

        if (rightIndex < values.size()) {
            nodes[i]->setRight(nodes[rightIndex]);
        }
    }

    root = nodes[0];
}

// Заполнить обычное бинарное дерево с клавиатуры
bool BinaryTree::fillKeyboardBinary() {
    using namespace std;
    clear();

    cout << "Ввод обычного бинарного\n";
    cout << "-1 означает пустую позицию.\n";

    int n = Check::readIntMin("Количество позиций: ", 1);
    vector<int> values;
    values.reserve(n);

    for (int i = 0; i < n; ++i) {
        int x = Check::readInt("Введите значение: ");
        values.push_back(x);
    }

    buildByLevels(values);

    if (!root) {
        cout << "Дерево не должно быть пустым.\n";
        return false;
    }

    return true;
}

// Заполнить обычное бинарное дерево из файла
bool BinaryTree::fillFileBinary() {
    using namespace std;
    clear();

    string fileName;
    cout << "Имя файла: ";
    cin >> fileName;

    ifstream fin(fileName);
    if (!fin.is_open()) {
        return false;
    }

    int n;
    if (!(fin >> n) || n < 1) {
        return false;
    }

    vector<int> values;
    values.reserve(n);

    for (int i = 0; i < n; ++i) {
        int x;
        if (!(fin >> x)) {
            return false;
        }
        values.push_back(x);
    }

    buildByLevels(values);

    if (!root) {
        return false;
    }

    return true;
}

// Заполнить обычное бинарное дерево случайно
bool BinaryTree::fillRandomBinary() {
    using namespace std;
    clear();

    int n = Check::readIntMin("Количество позиций: ", 1);
    int left = Check::readInt("Левая граница: ");
    int right = Check::readInt("Правая граница: ");

    if (left > right) {
        int t = left;
        left = right;
        right = t;
    }

    static bool seeded = false;
    if (!seeded) {
        srand((unsigned)time(nullptr));
        seeded = true;
    }

    vector<int> values;
    values.reserve(n);

    cout << "Сгенерировано: ";
    for (int i = 0; i < n; ++i) {
        int x = left + rand() % (right - left + 1);
        values.push_back(x);
        cout << x << ' ';
    }
    cout << '\n';

    buildByLevels(values);
    return true;
}

// Вывести пробелы
static void printSpaces(int count) {
    using namespace std;
    for (int i = 0; i < count; ++i) {
        cout << ' ';
    }
}

// Вывести дерево сверху вниз
void BinaryTree::print() const {
    using namespace std;
    if (!root) {
        cout << "Дерево пустое\n";
        return;
    }

    int h = height(root);
    queue<BinaryTree::Node*> q;
    q.push(root);

    for (int level = 0; level < h; ++level) {
        int nodesCount = 1 << level;
        int firstSpaces = (1 << (h - level)) - 1;
        int betweenSpaces = (1 << (h - level + 1)) - 1;

        printSpaces(firstSpaces * 2);

        for (int i = 0; i < nodesCount; ++i) {
            BinaryTree::Node* cur = q.front();
            q.pop();

            if (cur) {
                cout << setw(2) << cur->getData();
                q.push(cur->getLeft());
                q.push(cur->getRight());
            } else {
                cout << "  ";
                q.push(nullptr);
                q.push(nullptr);
            }

            printSpaces(betweenSpaces * 2);
        }

        cout << "\n\n";
    }
}


// Вывести листья слева направо
void BinaryTree::printLeaves(BinaryTree::Node* p) const {
    using namespace std;
    if (!p) return;

    printLeaves(p->getLeft());

    if(!p->getLeft() && !p->getRight()){
        cout << p->getData() << ' ';
    }

    printLeaves(p->getRight());
}

// Посчитать листья
int BinaryTree::countLeaves(BinaryTree::Node* p) const {
    if (!p) return 0;

    if(!p->getLeft() && !p->getRight()){
        return 1;
    }
    return countLeaves(p->getLeft()) + countLeaves(p->getRight());
}

// Высота дерева
int BinaryTree::height(BinaryTree::Node* p) const{
    if(!p) return 0;

    int lefth = height(p->getLeft());
    int righth = height(p->getRight());

    if(lefth > righth){
        return lefth + 1;
    }

    return righth + 1;
}

// Проверить АВЛ-сбалансированность
bool BinaryTree::isAvl(BinaryTree::Node* p) const{
    if(!p) return true;

    int lefth = height(p->getLeft());
    int righth = height(p->getRight());

    int diff = lefth - righth;
    if(diff < 0) diff = -diff;

    if(diff > 1){
        return false;
    }

    return isAvl(p->getLeft()) && isAvl(p->getRight());
}

// TreeWork4
void BinaryTree::runTreeWork4() const {
    using namespace std;
    cout << "Листья слева направо: ";
    printLeaves(root);
    cout << '\n';
}

// TreeWork13
void BinaryTree::runTreeWork13() const {
    using namespace std;
    cout << "Количество листьев: " << countLeaves(root) << '\n';
}

// TreeWork20
void BinaryTree::runTreeWork20() const {
    using namespace std;
    cout << "АВЛ-сбалансированное: " << (isAvl(root) ? "True" : "False") << '\n';
}

// Заполнить дерево выбранным способом
static bool fillTreeByMode(BinaryTree& tree) {
    using namespace std;
    int mode = Check::readIntRange("Заполнение: 1-клавиатура, 2-файл, 3-случайно: ", 1, 3);

    if (mode == 1) {
        return tree.fillKeyboardBinary();
    }

    if (mode == 2) {
        return tree.fillFileBinary();
    }

    return tree.fillRandomBinary();
}

// Задание 1
void TreeWork4() {
    using namespace std;
    BinaryTree tree;

    if (!fillTreeByMode(tree)) {
        cout << "Ошибка заполнения дерева\n";
        return;
    }

    cout << "\nДерево до обработки:\n";
    tree.print();

    tree.runTreeWork4();

    cout << "\nДерево после обработки:\n";
    tree.print();
}

// Задание 2
void TreeWork13() {
    using namespace std;
    BinaryTree tree;

    if (!fillTreeByMode(tree)) {
        cout << "Ошибка заполнения дерева\n";
        return;
    }

    cout << "\nДерево до обработки:\n";
    tree.print();

    tree.runTreeWork13();

    cout << "\nДерево после обработки:\n";
    tree.print();
}

// Задание 3
void TreeWork20() {
    using namespace std;
    BinaryTree tree;

    if (!fillTreeByMode(tree)) {
        cout << "Ошибка заполнения дерева\n";
        return;
    }

    cout << "\nДерево до обработки:\n";
    tree.print();

    tree.runTreeWork20();

    cout << "\nДерево после обработки:\n";
    tree.print();
}
