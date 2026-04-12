#include "funcion.h"

#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <limits>
#include <queue>
#include <iomanip>


using namespace std;

// Считать целое число
int Check::readInt(const char* text){
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
    while (true) {
        int x = readInt(text);

        if (x >= left && x <= right) {
            return x;
        }

        cout << "Число должно быть в диапазоне [" << left << "; " << right << "].\n";
    }
}

// Создать узел
Node::Node(int value) : data(value), left(nullptr), right(nullptr) {
}

// Создать дерево
BinaryTree::BinaryTree() : root(nullptr) {
}

// Удалить дерево
BinaryTree::~BinaryTree() {
    clear();
}

// Очистить поддерево
void BinaryTree::clear(Node* p){
    if(!p) return;

    clear(p->left);
    clear(p->right);
    delete p;
}

// Очистить дерево
void BinaryTree::clear(){
    clear(root);
    root = nullptr;
}

// Вставить значение в поддерево
void BinaryTree::insert(Node*& p, int value){
    if(!p){
        p = new Node(value);
        return;
    }

    if(value < p->data){
        insert(p->left, value);
    }
    else{
        insert(p->right, value);
    }
}

// Вставить значение в дерево
void BinaryTree::insert(int value) {
    insert(root, value);
}

// Заполнить дерево с клавиатуры
bool BinaryTree::fillKeyboard() {
    clear();

    int n = Check::readIntMin("Количество вершин: ", 1);

    for (int i = 0; i < n; ++i) {
        int x = Check::readInt("Введите значение: ");
        insert(x);
    }

    return true;
}

// Заполнить дерево из файла
bool BinaryTree::fillFile() {
    clear();

    string fileName;
    cout << "Имя файла: ";
    cin >> fileName;

    ifstream fin(fileName);
    if (!fin.is_open()) {
        return false;
    }

    int n;
    if (!(fin >> n) || n <= 0) {
        return false;
    }

    for (int i = 0; i < n; ++i) {
        int x;

        if (!(fin >> x)) {
            return false;
        }

        insert(x);
    }

    return true;
}

// Заполнить дерево случайно
bool BinaryTree::fillRandom() {
    clear();

    int n = Check::readIntMin("Количество вершин: ", 1);
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

    cout << "Сгенерировано: ";
    for (int i = 0; i < n; ++i) {
        int x = left + rand() % (right - left + 1);
        cout << x << ' ';
        insert(x);
    }
    cout << '\n';

    return true;
}

// Вывести пробелы
static void printSpaces(int count) {
    for (int i = 0; i < count; ++i) {
        cout << ' ';
    }
}

// Вывести дерево обычным видом сверху вниз
void BinaryTree::printTree(Node* p, int space) const {
    if(!p) return;

    const int step = 5;
    printTree(p->right, space + step);

    for(int i = 0; i < space; i++){
        cout << ' ';
    }
    cout << p->data << endl;
    printTree(p->left, space + step);

}

// Вывести дерево сверху вниз
void BinaryTree::print() const {
    if (!root) {
        cout << "Дерево пустое\n";
        return;
    }

    int h = height(root);
    queue<Node*> q;
    q.push(root);

    for (int level = 0; level < h; ++level) {
        int nodesCount = 1 << level;
        int firstSpaces = (1 << (h - level)) - 1;
        int betweenSpaces = (1 << (h - level + 1)) - 1;

        printSpaces(firstSpaces * 2);

        for (int i = 0; i < nodesCount; ++i) {
            Node* cur = q.front();
            q.pop();

            if (cur) {
                cout << setw(2) << cur->data;
                q.push(cur->left);
                q.push(cur->right);
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
void BinaryTree::printLeaves(Node* p) const {
    if (!p) return;

    printLeaves(p->left);

    if(!p->left && !p->right){
        cout << p->data << ' ';
    }

    printLeaves(p->right);
}

// Посчитать листья
int BinaryTree::countLeaves(Node* p) const {
    if (!p) return 0;

    if(!p->left && !p->right){
        return 1;
    }
    return countLeaves(p->left) + countLeaves(p->right);
}

// Высота дерева
int BinaryTree::height(Node* p) const{
    if(!p) return 0;

    int lefth = height(p->left);
    int righth = height(p->right);

    if(lefth > righth){
        return lefth + 1;
    }

    return righth + 1;
}

// Проверить АВЛ-сбалансированность
bool BinaryTree::isAvl(Node* p) const{
    if(!p) return true;

    int lefth = height(p->left);
    int righth = height(p->right);

    int diff = lefth - righth;
    if(diff < 0) diff = -diff;

    if(diff > 1){
        return false;
    }

    return isAvl(p->left) && isAvl(p->right);
}

// TreeWork4
void BinaryTree::runTreeWork4() const {
    cout << "Листья слева направо: ";
    printLeaves(root);
    cout << '\n';
}

// TreeWork13
void BinaryTree::runTreeWork13() const {
    cout << "Количество листьев: " << countLeaves(root) << '\n';
}

// TreeWork20
void BinaryTree::runTreeWork20() const {
    cout << "АВЛ-сбалансированное: " << (isAvl(root) ? "True" : "False") << '\n';
}

// Заполнить дерево выбранным способом
static bool fillTreeByMode(BinaryTree& tree) {
    int mode = Check::readIntRange("Заполнение: 1-клавиатура, 2-файл, 3-случайно: ", 1, 3);

    if (mode == 1) {
        return tree.fillKeyboard();
    }

    if (mode == 2) {
        return tree.fillFile();
    }

    return tree.fillRandom();
}

// Задание 1
void TreeWork4() {
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