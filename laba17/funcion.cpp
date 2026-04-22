#include "funcion.h"

#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <queue>
#include <stack>
#include <string>

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

// Считать целое число в диапазоне
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
CalcTree::Node::Node(int value) : data(value), left(nullptr), right(nullptr){
}

// Получить значение узла
int CalcTree::Node::getData() const{
    return data;
}

// Получить левый потомок
CalcTree::Node* CalcTree::Node::getLeft() const{
    return left;
}

// Получить правый потомок
CalcTree::Node* CalcTree::Node::getRight() const{
    return right;
}

// Изменить значение узла
void CalcTree::Node::setData(int value){
    data = value;
}

// Изменить левый потомок
void CalcTree::Node::setLeft(CalcTree::Node* p){
    left = p;
}

// Изменить правый потомок
void CalcTree::Node::setRight(CalcTree::Node* p){
    right = p;
}

// Создать дерево
CalcTree::CalcTree() : root(nullptr){
}

// Удалить дерево
CalcTree::~CalcTree(){
    clear();
}

// Очистить поддерево
void CalcTree::clear(CalcTree::Node* p){
    if(!p) return;

    clear(p->getLeft());
    clear(p->getRight());
    delete p;
}

// Очистить дерево
void CalcTree::clear(){
    clear(root);
    root = nullptr;
}

// Проверить, является ли число кодом операции
static bool isOperationCode(int value){
    return value >= -6 && value <= -1;
}

// Проверить, является ли значение переменной x
static bool isX(int value){
    return value == -100;
}

// Превратить символ операции в код
static int operationCode(char c){
    if(c == '+') return -1;
    if(c == '-') return -2;
    if(c == '*') return -3;
    if(c == '/') return -4;
    if(c == '%') return -5;
    if(c == '^') return -6;

    return 0;
}

// Пропустить пробелы
static void skipSpaces(const std::string& s, int& i){
    while(i < (int)s.size() && s[i] == ' '){
        ++i;
    }
}

// Посчитать степень
static int intPower(int a, int b){
    int result = 1;

    for(int i = 0; i < b; ++i){
        result *= a;
    }

    return result;
}

// Построить дерево по обратной польской записи
bool CalcTree::buildPostfix(const std::string& expression){
    using namespace std;

    clear();
    stack<Node*> st;

    for(size_t i = 0; i < expression.size(); ++i){
        char c = expression[i];

        if(c == ' ' || c == '\t' || c == '\n'){
            continue;
        }

        if(c >= '0' && c <= '9'){
            st.push(new Node(c - '0'));
        }
        else{
            int code = operationCode(c);

            if(code == 0 || st.size() < 2){
                while(!st.empty()){
                    clear(st.top());
                    st.pop();
                }

                return false;
            }

            Node* right = st.top();
            st.pop();

            Node* left = st.top();
            st.pop();

            Node* p = new Node(code);
            p->setLeft(left);
            p->setRight(right);

            st.push(p);
        }
    }

    if(st.size() != 1){
        while(!st.empty()){
            clear(st.top());
            st.pop();
        }

        return false;
    }

    root = st.top();
    return true;
}

// Построить дерево по инфиксной записи
bool CalcTree::buildInfix(const std::string& expression){
    clear();

    int i = 0;
    root = parseExpression(expression, i);

    skipSpaces(expression, i);

    if(!root || i != (int)expression.size()){
        clear();
        return false;
    }

    return true;
}

// Разобрать выражение
CalcTree::Node* CalcTree::parseExpression(const std::string& s, int& i){
    return parseAddSub(s, i);
}

// Разобрать + и -
CalcTree::Node* CalcTree::parseAddSub(const std::string& s, int& i){
    Node* left = parseMulDivMod(s, i);

    while(true){
        skipSpaces(s, i);

        if(i >= (int)s.size() || (s[i] != '+' && s[i] != '-')){
            break;
        }

        char op = s[i];
        ++i;

        Node* right = parseMulDivMod(s, i);
        Node* p = new Node(operationCode(op));

        p->setLeft(left);
        p->setRight(right);

        left = p;
    }

    return left;
}

// Разобрать *, / и %
CalcTree::Node* CalcTree::parseMulDivMod(const std::string& s, int& i){
    Node* left = parsePower(s, i);

    while(true){
        skipSpaces(s, i);

        if(i >= (int)s.size() || (s[i] != '*' && s[i] != '/' && s[i] != '%')){
            break;
        }

        char op = s[i];
        ++i;

        Node* right = parsePower(s, i);
        Node* p = new Node(operationCode(op));

        p->setLeft(left);
        p->setRight(right);

        left = p;
    }

    return left;
}

// Разобрать ^
CalcTree::Node* CalcTree::parsePower(const std::string& s, int& i){
    Node* left = parseValue(s, i);

    while(true){
        skipSpaces(s, i);

        if(i >= (int)s.size() || s[i] != '^'){
            break;
        }

        char op = s[i];
        ++i;

        Node* right = parseValue(s, i);
        Node* p = new Node(operationCode(op));

        p->setLeft(left);
        p->setRight(right);

        left = p;
    }

    return left;
}

// Разобрать число, x или скобки
CalcTree::Node* CalcTree::parseValue(const std::string& s, int& i){
    skipSpaces(s, i);

    if(i >= (int)s.size()){
        return nullptr;
    }

    if(s[i] == '('){
        ++i;

        Node* p = parseExpression(s, i);

        skipSpaces(s, i);

        if(i < (int)s.size() && s[i] == ')'){
            ++i;
        }

        return p;
    }

    if(s[i] == 'x' || s[i] == 'X'){
        ++i;
        return new Node(-100);
    }

    if(s[i] >= '0' && s[i] <= '9'){
        int number = 0;

        while(i < (int)s.size() && s[i] >= '0' && s[i] <= '9'){
            number = number * 10 + (s[i] - '0');
            ++i;
        }

        return new Node(number);
    }

    return nullptr;
}

// Заполнить дерево выражением с клавиатуры
bool CalcTree::fillKeyboardPostfix(){
    using namespace std;

    string expression;

    cout << "Введите выражение в обратной польской записи: ";
    cin >> expression;

    return buildPostfix(expression);
}

// Заполнить дерево выражением из файла
bool CalcTree::fillFilePostfix(){
    using namespace std;

    string fileName;

    cout << "Имя файла: ";
    cin >> fileName;

    ifstream fin(fileName);

    if(!fin.is_open()){
        return false;
    }

    string expression;
    fin >> expression;

    return buildPostfix(expression);
}

// Создать случайное выражение в обратной польской записи
std::string CalcTree::makeRandomPostfix(int countOperands) const{
    std::string expression;
    const char operations[] = {'+', '-', '*', '/', '%', '^'};

    expression += char('0' + rand() % 10);
    expression += char('0' + rand() % 10);
    expression += operations[rand() % 6];

    for(int i = 2; i < countOperands; ++i){
        expression += char('0' + rand() % 10);
        expression += operations[rand() % 6];
    }

    return expression;
}

// Заполнить дерево случайным выражением
bool CalcTree::fillRandomPostfix(){
    using namespace std;

    static bool seeded = false;

    if(!seeded){
        srand((unsigned)time(nullptr));
        seeded = true;
    }

    int countOperands = Check::readIntRange("Количество операндов (2..9): ", 2, 9);
    string expression = makeRandomPostfix(countOperands);

    cout << "Сгенерировано: " << expression << '\n';

    return buildPostfix(expression);
}

// Заполнить инфиксное выражение с клавиатуры
bool CalcTree::fillKeyboardInfix(int& x, std::string& outFileName){
    using namespace std;

    string expression;

    cout << "Введите выражение: ";
    cin >> expression;

    x = Check::readInt("Введите x: ");

    cout << "Имя выходного файла: ";
    cin >> outFileName;

    return buildInfix(expression);
}

// Заполнить инфиксное выражение из файла
bool CalcTree::fillFileInfix(int& x, std::string& outFileName){
    using namespace std;

    string inFileName;

    cout << "Имя входного файла: ";
    cin >> inFileName;

    ifstream fin(inFileName);

    if(!fin.is_open()){
        return false;
    }

    string expression;
    fin >> expression;

    x = Check::readInt("Введите x: ");

    cout << "Имя выходного файла: ";
    cin >> outFileName;

    return buildInfix(expression);
}

// Заполнить инфиксное выражение случайно
bool CalcTree::fillRandomInfix(int& x, std::string& outFileName){
    using namespace std;

    static bool seeded = false;

    if(!seeded){
        srand((unsigned)time(nullptr));
        seeded = true;
    }

    int a = 1 + rand() % 9;
    int b = 1 + rand() % 9;

    string expression = "x*" + to_string(a) + "+" + to_string(b);

    cout << "Сгенерировано: " << expression << '\n';

    x = Check::readInt("Введите x: ");

    cout << "Имя выходного файла: ";
    cin >> outFileName;

    return buildInfix(expression);
}

// Высота дерева
int CalcTree::height(CalcTree::Node* p) const{
    if(!p) return 0;

    int leftHeight = height(p->getLeft());
    int rightHeight = height(p->getRight());

    if(leftHeight > rightHeight){
        return leftHeight + 1;
    }

    return rightHeight + 1;
}

// Вывести значение узла
void CalcTree::printNodeValue(int value) const{
    using namespace std;

    if(isX(value)) cout << 'x';
    else if(value == -1) cout << '+';
    else if(value == -2) cout << '-';
    else if(value == -3) cout << '*';
    else if(value == -4) cout << '/';
    else if(value == -5) cout << '%';
    else if(value == -6) cout << '^';
    else cout << value;
}

// Вывести пробелы
static void printSpaces(int count){
    using namespace std;

    for(int i = 0; i < count; ++i){
        cout << ' ';
    }
}

// Вывести дерево сверху вниз
void CalcTree::print() const{
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
                cout << setw(3);
                printNodeValue(cur->getData());

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

// Вычислить значение поддерева
int CalcTree::calculate(CalcTree::Node* p) const{
    if(!p) return 0;

    int value = p->getData();

    if(!isOperationCode(value)){
        return value;
    }

    int a = calculate(p->getLeft());
    int b = calculate(p->getRight());

    if(value == -1) return a + b;
    if(value == -2) return a - b;
    if(value == -3) return a * b;

    if(value == -4){
        if(b == 0) return 0;
        return a / b;
    }

    if(value == -5){
        if(b == 0) return 0;
        return a % b;
    }

    if(value == -6){
        return intPower(a, b);
    }

    return 0;
}

// Вычислить значение поддерева с учетом x
int CalcTree::calculateWithX(CalcTree::Node* p, int x) const{
    if(!p) return 0;

    int value = p->getData();

    if(isX(value)){
        return x;
    }

    if(!isOperationCode(value)){
        return value;
    }

    int a = calculateWithX(p->getLeft(), x);
    int b = calculateWithX(p->getRight(), x);

    if(value == -1) return a + b;
    if(value == -2) return a - b;
    if(value == -3) return a * b;

    if(value == -4){
        if(b == 0) return 0;
        return a / b;
    }

    if(value == -5){
        if(b == 0) return 0;
        return a % b;
    }

    if(value == -6){
        return intPower(a, b);
    }

    return 0;
}

// Посчитать все выражение
int CalcTree::calculateExpression(int x) const{
    return calculateWithX(root, x);
}

// Заменить поддеревья с делением или остатком на их значение
void CalcTree::replaceDivision(CalcTree::Node*& p){
    if(!p) return;

    if(p->getData() == -4 || p->getData() == -5){
        int value = calculate(p);

        clear(p->getLeft());
        clear(p->getRight());

        p->setLeft(nullptr);
        p->setRight(nullptr);
        p->setData(value);

        return;
    }

    Node* left = p->getLeft();
    Node* right = p->getRight();

    replaceDivision(left);
    replaceDivision(right);

    p->setLeft(left);
    p->setRight(right);
}

// Выполнить преобразование CalcTree4
void CalcTree::removeDivisionOperations(){
    replaceDivision(root);
}

// Проверить, есть ли x в поддереве
bool CalcTree::containsX(CalcTree::Node* p) const{
    if(!p) return false;

    if(isX(p->getData())){
        return true;
    }

    return containsX(p->getLeft()) || containsX(p->getRight());
}

// Заменить поддеревья, где есть x, на значение
void CalcTree::replaceXSubtrees(CalcTree::Node*& p, int x){
    if(!p) return;

    if(containsX(p)){
        int value = calculateWithX(p, x);

        clear(p->getLeft());
        clear(p->getRight());

        p->setLeft(nullptr);
        p->setRight(nullptr);
        p->setData(value);

        return;
    }

    Node* left = p->getLeft();
    Node* right = p->getRight();

    replaceXSubtrees(left, x);
    replaceXSubtrees(right, x);

    p->setLeft(left);
    p->setRight(right);
}

// Выполнить преобразование CalcTree26
void CalcTree::replaceXOperations(int x){
    replaceXSubtrees(root, x);
}

// Вывести дерево в файл боком
void CalcTree::printSideToFile(CalcTree::Node* p, std::ofstream& fout, int level) const{
    if(!p) return;

    printSideToFile(p->getRight(), fout, level + 1);

    fout << std::setw(level * 8) << "";
    printNodeValue(p->getData());
    fout << '\n';

    printSideToFile(p->getLeft(), fout, level + 1);
}

// Записать результат CalcTree26 в файл
void CalcTree::writeCalcTree26Result(const std::string& outFileName, int result) const{
    using namespace std;

    ofstream fout(outFileName);

    if(!fout.is_open()){
        cout << "Не удалось открыть выходной файл\n";
        return;
    }

    fout << "Результат выражения: " << result << '\n';
    fout << "Дерево после преобразования:\n";

    printSideToFile(root, fout, 1);
}

// Вывести указатель на корень
void CalcTree::printRootPointer() const{
    using namespace std;

    cout << "Корень дерева: " << static_cast<const void*>(root) << '\n';
}

// Вывести котика
void printCat(){
    using namespace std;

    cout << " /\\_/\\\n";
    cout << "( o.o )\n";
    cout << " > ^ <\n";
}

// Задача 1: CalcTree4
void CalcTree4(){
    using namespace std;

    CalcTree tree;

    int mode = Check::readIntRange("Заполнение: 1-клавиатура, 2-файл, 3-случайно: ", 1, 3);
    bool ok = false;

    if(mode == 1){
        ok = tree.fillKeyboardPostfix();
    }
    else if(mode == 2){
        ok = tree.fillFilePostfix();
    }
    else{
        ok = tree.fillRandomPostfix();
    }

    if(!ok){
        cout << "Ошибка заполнения дерева\n";
        return;
    }

    cout << "\nДерево до обработки:\n";
    tree.print();

    tree.removeDivisionOperations();

    cout << "\nДерево после обработки:\n";
    tree.print();

    tree.printRootPointer();
    printCat();
}

// Задача 2: CalcTree26
void CalcTree26(){
    using namespace std;

    CalcTree tree;

    int mode = Check::readIntRange("Заполнение: 1-клавиатура, 2-файл, 3-случайно: ", 1, 3);
    int x;
    string outFileName;
    bool ok = false;

    if(mode == 1){
        ok = tree.fillKeyboardInfix(x, outFileName);
    }
    else if(mode == 2){
        ok = tree.fillFileInfix(x, outFileName);
    }
    else{
        ok = tree.fillRandomInfix(x, outFileName);
    }

    if(!ok){
        cout << "Ошибка заполнения дерева\n";
        return;
    }

    cout << "\nДерево до обработки:\n";
    tree.print();

    int result = tree.calculateExpression(x);

    tree.replaceXOperations(x);

    cout << "\nДерево после обработки:\n";
    tree.print();

    tree.writeCalcTree26Result(outFileName, result);
    cout << endl;

    cout << "Результат записан в файл: " << outFileName << '\n';

    tree.printRootPointer();
    printCat();
}
