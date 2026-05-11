#include "funcion.h"

#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <queue>
#include <string>
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

// Считать число не меньше minValue
int Check::readIntMin(const char* text, int minValue){
    using namespace std;

    while(true){
        int x = readInt(text);

        if(x >= minValue){
            return x;
        }

        cout << "Число должно быть >= " << minValue << ".\n";
    }
}

// Считать число в диапазоне
int Check::readIntRange(const char* text, int left, int right){
    using namespace std;

    while(true){
        int x = readInt(text);

        if(x >= left && x <= right){
            return x;
        }

        cout << "Число должно быть в диапазоне [" << left << "; " << right << "].\n";
    }
}

// Создать узел
Node::Node(int value) : data(value), left(nullptr), right(nullptr){
}

// Получить значение
int Node::getData() const{
    return data;
}

// Получить левую ссылку
Node* Node::getLeft() const{
    return left;
}

// Получить правую ссылку
Node* Node::getRight() const{
    return right;
}

// Изменить значение
void Node::setData(int value){
    data = value;
}

// Изменить левую ссылку
void Node::setLeft(Node* p){
    left = p;
}

// Изменить правую ссылку
void Node::setRight(Node* p){
    right = p;
}

// Создать список
DoublyList::DoublyList() : head(nullptr), tail(nullptr){
}

// Удалить список
DoublyList::~DoublyList(){
    clear();
}

// Очистить список
void DoublyList::clear(){
    while(head){
        Node* p = head;
        head = head->getRight();
        delete p;
    }

    tail = nullptr;
}

// Добавить элемент в конец списка
void DoublyList::pushBack(int value){
    Node* p = new Node(value);

    if(!head){
        head = p;
        tail = p;
        return;
    }

    tail->setRight(p);
    p->setLeft(tail);
    tail = p;
}

// Вставить готовый узел в отсортированный список
void DoublyList::insertSortedNode(Node* p){
    p->setLeft(nullptr);
    p->setRight(nullptr);

    if(!head){
        head = p;
        tail = p;
        return;
    }

    if(p->getData() <= head->getData()){
        p->setRight(head);
        head->setLeft(p);
        head = p;
        return;
    }

    Node* cur = head;

    while(cur->getRight() && cur->getRight()->getData() < p->getData()){
        cur = cur->getRight();
    }

    p->setRight(cur->getRight());
    p->setLeft(cur);

    if(cur->getRight()){
        cur->getRight()->setLeft(p);
    }
    else{
        tail = p;
    }

    cur->setRight(p);
}

// Отсортировать список без создания новых узлов
void DoublyList::sortAscending(){
    Node* oldHead = head;
    head = nullptr;
    tail = nullptr;

    while(oldHead){
        Node* p = oldHead;
        oldHead = oldHead->getRight();

        insertSortedNode(p);
    }
}

// Заполнить список с клавиатуры
bool DoublyList::fillKeyboard(){
    clear();

    int n = Check::readIntMin("Количество элементов списка: ", 1);

    for(int i = 0; i < n; ++i){
        int x = Check::readInt("Введите число: ");
        pushBack(x);
    }

    return true;
}

// Заполнить список из файла
bool DoublyList::fillFile(){
    using namespace std;

    clear();

    string fileName;
    cout << "Имя файла: ";
    cin >> fileName;

    ifstream fin(fileName);

    if(!fin.is_open()){
        return false;
    }

    int n;

    if(!(fin >> n) || n < 1){
        return false;
    }

    for(int i = 0; i < n; ++i){
        int x;

        if(!(fin >> x)){
            return false;
        }

        pushBack(x);
    }

    return true;
}

// Заполнить список случайно
bool DoublyList::fillRandom(){
    using namespace std;

    clear();

    int n = Check::readIntMin("Количество элементов списка: ", 1);
    int left = Check::readInt("Левая граница: ");
    int right = Check::readInt("Правая граница: ");

    if(left > right){
        int t = left;
        left = right;
        right = t;
    }

    static bool seeded = false;

    if(!seeded){
        srand((unsigned)time(nullptr));
        seeded = true;
    }

    cout << "Сгенерировано: ";

    for(int i = 0; i < n; ++i){
        int x = left + rand() % (right - left + 1);

        cout << x << ' ';
        pushBack(x);
    }

    cout << '\n';

    return true;
}

// Посчитать элементы списка
int DoublyList::count() const{
    int result = 0;
    Node* p = head;

    while(p){
        ++result;
        p = p->getRight();
    }

    return result;
}

// Построить сбалансированное дерево из отсортированного списка
Node* DoublyList::buildBalanced(int countNodes){
    if(countNodes <= 0){
        return nullptr;
    }

    Node* leftRoot = buildBalanced(countNodes / 2);
    Node* root = head;

    head = head->getRight();

    root->setLeft(leftRoot);
    root->setRight(buildBalanced(countNodes - countNodes / 2 - 1));

    return root;
}

// Преобразовать список в дерево без новых узлов
Node* DoublyList::toBalancedTree(){
    int n = count();

    Node* treeRoot = buildBalanced(n);

    head = nullptr;
    tail = nullptr;

    return treeRoot;
}

// Вывести список
void DoublyList::print() const{
    using namespace std;

    cout << "list: ";

    Node* p = head;

    while(p){
        cout << p->getData() << ' ';
        p = p->getRight();
    }

    cout << '\n';
}

// Создать дерево
BinaryTree::BinaryTree() : root(nullptr){
}

// Удалить дерево
BinaryTree::~BinaryTree(){
    clear();
}

// Очистить поддерево
void BinaryTree::clear(Node* p){
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

// Установить готовый корень
void BinaryTree::setRoot(Node* p){
    clear();
    root = p;
}

// Построить обычное дерево по уровням слева направо
void BinaryTree::buildByLevels(const std::vector<int>& values){
    clear();

    if(values.empty() || values[0] == -1){
        return;
    }

    std::vector<Node*> nodes(values.size(), nullptr);
    nodes[0] = new Node(values[0]);

    for(size_t i = 1; i < values.size(); ++i){
        size_t parentIndex = (i - 1) / 2;

        if(values[i] != -1 && nodes[parentIndex]){
            nodes[i] = new Node(values[i]);
        }
    }

    for(size_t i = 0; i < values.size(); ++i){
        if(!nodes[i]){
            continue;
        }

        size_t leftIndex = 2 * i + 1;
        size_t rightIndex = 2 * i + 2;

        if(leftIndex < values.size()){
            nodes[i]->setLeft(nodes[leftIndex]);
        }

        if(rightIndex < values.size()){
            nodes[i]->setRight(nodes[rightIndex]);
        }
    }

    root = nodes[0];
}

// Заполнить дерево с клавиатуры
bool BinaryTree::fillKeyboard(){
    using namespace std;

    cout << "Ввод дерева по уровням слева направо.\n";
    cout << "-1 означает пустую позицию.\n";

    int n = Check::readIntMin("Количество позиций: ", 1);
    vector<int> values;
    values.reserve(n);

    for(int i = 0; i < n; ++i){
        int x = Check::readInt("Введите значение: ");
        values.push_back(x);
    }

    buildByLevels(values);

    if(!root){
        cout << "Дерево не должно быть пустым.\n";
        return false;
    }

    return true;
}

// Заполнить дерево из файла
bool BinaryTree::fillFile(){
    using namespace std;

    string fileName;
    cout << "Имя файла: ";
    cin >> fileName;

    ifstream fin(fileName);

    if(!fin.is_open()){
        return false;
    }

    int n;

    if(!(fin >> n) || n < 1){
        return false;
    }

    vector<int> values;
    values.reserve(n);

    for(int i = 0; i < n; ++i){
        int x;

        if(!(fin >> x)){
            return false;
        }

        values.push_back(x);
    }

    buildByLevels(values);

    return root != nullptr;
}

// Заполнить дерево случайно
bool BinaryTree::fillRandom(){
    using namespace std;

    int n = Check::readIntMin("Количество позиций: ", 1);
    int left = Check::readInt("Левая граница: ");
    int right = Check::readInt("Правая граница: ");

    if(left > right){
        int t = left;
        left = right;
        right = t;
    }

    static bool seeded = false;

    if(!seeded){
        srand((unsigned)time(nullptr));
        seeded = true;
    }

    vector<int> values;
    values.reserve(n);

    cout << "Сгенерировано: ";

    for(int i = 0; i < n; ++i){
        int x = left + rand() % (right - left + 1);

        values.push_back(x);
        cout << x << ' ';
    }

    cout << '\n';

    buildByLevels(values);

    return true;
}

// Высота дерева
int BinaryTree::height(Node* p) const{
    if(!p) return 0;

    int leftHeight = height(p->getLeft());
    int rightHeight = height(p->getRight());

    if(leftHeight > rightHeight){
        return leftHeight + 1;
    }

    return rightHeight + 1;
}

// Вывести пробелы
static void printSpaces(int count){
    using namespace std;

    for(int i = 0; i < count; ++i){
        cout << ' ';
    }
}

// Вывести дерево сверху вниз
void BinaryTree::print() const{
    using namespace std;

    if(!root){
        cout << "Дерево пустое\n";
        return;
    }

    int h = height(root);
    queue<Node*> q;
    q.push(root);

    for(int level = 0; level < h; ++level){
        int nodesCount = 1 << level;
        int firstSpaces = (1 << (h - level)) - 1;
        int betweenSpaces = (1 << (h - level + 1)) - 1;

        printSpaces(firstSpaces * 2);

        for(int i = 0; i < nodesCount; ++i){
            Node* cur = q.front();
            q.pop();

            if(cur){
                cout << setw(3) << cur->getData();

                q.push(cur->getLeft());
                q.push(cur->getRight());
            }
            else{
                cout << "   ";

                q.push(nullptr);
                q.push(nullptr);
            }

            printSpaces(betweenSpaces * 2);
        }

        cout << "\n\n";
    }
}

// Создать итератор обхода корень-право-лево
BinaryTree::Iterator BinaryTree::iteratorRootRightLeft() const{
    return Iterator(root);
}

// Создать итератор
BinaryTree::Iterator::Iterator(Node* root){
    if(root){
        stack.push_back(root);
    }
}

// Проверить, есть ли следующий элемент
bool BinaryTree::Iterator::hasNext() const{
    return !stack.empty();
}

// Получить следующий элемент
int BinaryTree::Iterator::next(){
    Node* p = stack.back();
    stack.pop_back();

    if(p->getLeft()){
        stack.push_back(p->getLeft());
    }

    if(p->getRight()){
        stack.push_back(p->getRight());
    }

    return p->getData();
}

// Рекурсивно посчитать камеры
int BinaryTree::camerasDfs(Node* p, int& cameras) const{
    if(!p){
        return 2;
    }

    int leftState = camerasDfs(p->getLeft(), cameras);
    int rightState = camerasDfs(p->getRight(), cameras);

    if(leftState == 0 || rightState == 0){
        ++cameras;
        return 1;
    }

    if(leftState == 1 || rightState == 1){
        return 2;
    }

    return 0;
}

// Минимальное количество камер
int BinaryTree::minCameras() const{
    int cameras = 0;

    int rootState = camerasDfs(root, cameras);

    if(rootState == 0){
        ++cameras;
    }

    return cameras;
}


// Выбрать способ заполнения списка
static bool fillListByMode(DoublyList& list){
    int mode = Check::readIntRange("Заполнение: 1-клавиатура, 2-файл, 3-случайно: ", 1, 3);

    if(mode == 1){
        return list.fillKeyboard();
    }

    if(mode == 2){
        return list.fillFile();
    }

    return list.fillRandom();
}

// Выбрать способ заполнения дерева
static bool fillTreeByMode(BinaryTree& tree){
    int mode = Check::readIntRange("Заполнение: 1-клавиатура, 2-файл, 3-случайно: ", 1, 3);

    if(mode == 1){
        return tree.fillKeyboard();
    }

    if(mode == 2){
        return tree.fillFile();
    }

    return tree.fillRandom();
}

// TreeFun2
void TreeFun2(){
    using namespace std;

    DoublyList list;

    if(!fillListByMode(list)){
        cout << "Ошибка заполнения списка\n";
        return;
    }

    cout << "\nИсходный список:\n";
    list.print();

    list.sortAscending();

    cout << "Список по возрастанию:\n";
    list.print();

    BinaryTree tree;
    tree.setRoot(list.toBalancedTree());

    cout << "\nПолучившееся дерево поиска:\n";
    tree.print();
}

// TreeFun6
void TreeFun6(){
    using namespace std;

    BinaryTree tree;

    if(!fillTreeByMode(tree)){
        cout << "Ошибка заполнения дерева\n";
        return;
    }

    cout << "\nДерево:\n";
    tree.print();

    cout << "Обход корень-право-лево: ";

    BinaryTree::Iterator it = tree.iteratorRootRightLeft();

    while(it.hasNext()){
        cout << it.next() << ' ';
    }

    cout << '\n';
}

// TreeFun9
void TreeFun9(){
    using namespace std;

    BinaryTree tree;

    if(!fillTreeByMode(tree)){
        cout << "Ошибка заполнения дерева\n";
        return;
    }

    cout << "\nДерево:\n";
    tree.print();

    cout << "Минимальное количество камер: " << tree.minCameras() << '\n';
}
