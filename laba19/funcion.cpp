#include "funcion.h"

#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
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

// Проверить строку из 0 и 1
bool Check::isBinaryString(const std::string& s){
    if(s.empty()){
        return false;
    }

    for(size_t i = 0; i < s.size(); ++i){
        if(s[i] != '0' && s[i] != '1'){
            return false;
        }
    }

    return true;
}

// Создать код Хемминга
HammingCode::HammingCode(const std::string& bits) : data(bits), m((int)bits.size()), r(0), n(0){
    while((1 << r) < m + r + 1){
        ++r;
    }

    n = m + r;
    code.assign(n + 1, 0);
}

// Проверить, степень ли это двойки
bool HammingCode::isPowerOfTwo(int x) const{
    return x > 0 && (x & (x - 1)) == 0;
}

// Построить кодовое слово с пустыми контрольными битами
void HammingCode::buildEmptyCode(){
    int j = 0;

    for(int i = 1; i <= n; ++i){
        if(isPowerOfTwo(i)){
            code[i] = 0;
        }
        else{
            code[i] = data[j] - '0';
            ++j;
        }
    }
}

// Посчитать контрольные биты
void HammingCode::calculateControlBits(){
    for(int p = 1; p <= n; p *= 2){
        int sum = 0;

        for(int i = 1; i <= n; ++i){
            if((i & p) && i != p){
                sum ^= code[i];
            }
        }

        code[p] = sum;
    }
}

// Закодировать сообщение
void HammingCode::encode(){
    buildEmptyCode();
    calculateControlBits();
}

// Посчитать синдром
int HammingCode::calculateSyndrome() const{
    int syndrome = 0;

    for(int p = 1; p <= n; p *= 2){
        int sum = 0;

        for(int i = 1; i <= n; ++i){
            if(i & p){
                sum ^= code[i];
            }
        }

        if(sum != 0){
            syndrome += p;
        }
    }

    return syndrome;
}

// Вывести таблицу до подсчета контрольных битов
void HammingCode::printEmptyTable() const{
    using namespace std;

    cout << "\nПозиции:\n";
    for(int i = 1; i <= n; ++i){
        cout << setw(3) << i;
    }

    cout << "\nБиты:\n";

    int j = 0;

    for(int i = 1; i <= n; ++i){
        if(isPowerOfTwo(i)){
            cout << setw(3) << "_";
        }
        else{
            cout << setw(3) << data[j];
            ++j;
        }
    }

    cout << '\n';
}

// Вывести готовую таблицу
void HammingCode::printFullTable() const{
    using namespace std;

    cout << "\nПозиции:\n";
    for(int i = 1; i <= n; ++i){
        cout << setw(3) << i;
    }

    cout << "\nКод:\n";
    for(int i = 1; i <= n; ++i){
        cout << setw(3) << code[i];
    }

    cout << '\n';
}

// Вывести контрольные биты
void HammingCode::printControlBits() const{
    using namespace std;

    cout << "\nИнформационных бит: " << m << '\n';
    cout << "Контрольных бит: " << r << '\n';
    cout << "Длина кода: " << n << '\n';

    cout << "\nКонтрольные биты:\n";

    for(int p = 1; p <= n; p *= 2){
        cout << "C" << p << " = ";

        bool first = true;

        for(int i = 1; i <= n; ++i){
            if((i & p) && i != p){
                if(!first){
                    cout << " + ";
                }

                cout << code[i];
                first = false;
            }
        }

        cout << " = " << code[p] << '\n';
    }
}

// Получить длину кода
int HammingCode::getLength() const{
    return n;
}

// Добавить ошибку
void HammingCode::addError(int position){
    if(position >= 1 && position <= n){
        code[position] = 1 - code[position];
    }
}

// Найти ошибку
int HammingCode::findError() const{
    return calculateSyndrome();
}

// Исправить ошибку
void HammingCode::fixError(int position){
    if(position >= 1 && position <= n){
        code[position] = 1 - code[position];
    }
}

// Вывести код
void HammingCode::printCode() const{
    using namespace std;

    for(int i = 1; i <= n; ++i){
        cout << code[i];
    }

    cout << '\n';
}

// Создать лист дерева Хаффмана
HuffmanNode::HuffmanNode(char symbol, int count)
    : symbol(symbol), count(count), left(nullptr), right(nullptr){
}

// Создать внутренний узел дерева Хаффмана
HuffmanNode::HuffmanNode(HuffmanNode* left, HuffmanNode* right)
    : symbol('\0'), count(left->getCount() + right->getCount()), left(left), right(right){
}

// Получить символ
char HuffmanNode::getSymbol() const{
    return symbol;
}

// Получить количество
int HuffmanNode::getCount() const{
    return count;
}

// Получить левый потомок
HuffmanNode* HuffmanNode::getLeft() const{
    return left;
}

// Получить правый потомок
HuffmanNode* HuffmanNode::getRight() const{
    return right;
}

// Проверить, лист ли это
bool HuffmanNode::isLeaf() const{
    return !left && !right;
}

// Создать кодер Хаффмана
HuffmanCode::HuffmanCode(const std::string& text) : text(text), root(nullptr){
}

// Удалить кодер
HuffmanCode::~HuffmanCode(){
    clear(root);
}

// Очистить дерево Хаффмана
void HuffmanCode::clear(HuffmanNode* p){
    if(!p) return;

    clear(p->getLeft());
    clear(p->getRight());

    delete p;
}

// Найти индекс символа
int HuffmanCode::findSymbol(char c) const{
    for(size_t i = 0; i < symbols.size(); ++i){
        if(symbols[i] == c){
            return (int)i;
        }
    }

    return -1;
}

// Построить дерево Хаффмана
void HuffmanCode::build(){
    std::vector<HuffmanNode*> nodes;

    for(size_t i = 0; i < text.size(); ++i){
        char c = text[i];
        int index = findSymbol(c);

        if(index == -1){
            symbols.push_back(c);
            codes.push_back("");
            nodes.push_back(new HuffmanNode(c, 1));
        }
        else{
            HuffmanNode* old = nodes[index];
            nodes[index] = new HuffmanNode(c, old->getCount() + 1);
            delete old;
        }
    }

    while(nodes.size() > 1){
        int first = 0;
        int second = 1;

        if(nodes[second]->getCount() < nodes[first]->getCount()){
            int t = first;
            first = second;
            second = t;
        }

        for(size_t i = 2; i < nodes.size(); ++i){
            if(nodes[i]->getCount() < nodes[first]->getCount()){
                second = first;
                first = (int)i;
            }
            else if(nodes[i]->getCount() < nodes[second]->getCount()){
                second = (int)i;
            }
        }

        if(first > second){
            int t = first;
            first = second;
            second = t;
        }

        HuffmanNode* left = nodes[first];
        HuffmanNode* right = nodes[second];

        nodes.erase(nodes.begin() + second);
        nodes.erase(nodes.begin() + first);

        nodes.push_back(new HuffmanNode(left, right));
    }

    if(!nodes.empty()){
        root = nodes[0];
    }

    buildCodes(root, "");
}

// Построить коды символов
void HuffmanCode::buildCodes(HuffmanNode* p, const std::string& code){
    if(!p) return;

    if(p->isLeaf()){
        int index = findSymbol(p->getSymbol());

        if(index != -1){
            if(code.empty()){
                codes[index] = "0";
            }
            else{
                codes[index] = code;
            }
        }

        return;
    }

    buildCodes(p->getLeft(), code + "0");
    buildCodes(p->getRight(), code + "1");
}

// Вывести дерево Хаффмана
void HuffmanCode::printTree() const{
    using namespace std;

    cout << "\nДерево Хаффмана:\n";
    printTree(root, 0);
}

// Вывести дерево Хаффмана боком
void HuffmanCode::printTree(HuffmanNode* p, int level) const{
    using namespace std;

    if(!p) return;

    printTree(p->getRight(), level + 1);

    for(int i = 0; i < level; ++i){
        cout << "    ";
    }

    if(p->isLeaf()){
        if(p->getSymbol() == ' '){
            cout << "[space]";
        }
        else{
            cout << p->getSymbol();
        }

        cout << ":" << p->getCount() << '\n';
    }
    else{
        cout << "*:" << p->getCount() << '\n';
    }

    printTree(p->getLeft(), level + 1);
}

// Вывести таблицу символов
void HuffmanCode::printTable() const{
    using namespace std;

    cout << "\nТаблица кодов:\n";
    cout << "Символ | Код\n";

    for(size_t i = 0; i < symbols.size(); ++i){
        if(symbols[i] == ' '){
            cout << "space";
        }
        else{
            cout << symbols[i];
        }

        cout << " | " << codes[i] << '\n';
    }
}

// Закодировать текст
std::string HuffmanCode::encode() const{
    std::string result;

    for(size_t i = 0; i < text.size(); ++i){
        int index = findSymbol(text[i]);

        if(index != -1){
            result += codes[index];
        }
    }

    return result;
}

// Количество разных символов
int HuffmanCode::uniqueCount() const{
    return (int)symbols.size();
}

// Сколько бит надо при равномерном кодировании
int HuffmanCode::bitsForUniform() const{
    int count = uniqueCount();

    if(count <= 1){
        return 1;
    }

    int bits = 0;
    int value = 1;

    while(value < count){
        value *= 2;
        ++bits;
    }

    return bits;
}

// Вывести статистику
void HuffmanCode::printStats() const{
    using namespace std;

    string encoded = encode();

    int uniformBits = bitsForUniform();
    int uniformSize = uniformBits * (int)text.size();
    int huffmanSize = (int)encoded.size();

    cout << "\nРазмеры:\n";
    cout << "Разных символов: " << uniqueCount() << '\n';
    cout << "Бит на символ при равномерном кодировании: " << uniformBits << '\n';
    cout << "Размер при равномерном кодировании: " << uniformSize << " бит\n";
    cout << "Размер при Хаффмане: " << huffmanSize << " бит\n";
    cout << "Закодированная строка: " << encoded << '\n';
}

// Ввод сообщения с клавиатуры
static bool fillKeyboard(std::string& bits){
    using namespace std;

    cout << "Введите сообщение из 0 и 1: ";
    cin >> bits;

    return Check::isBinaryString(bits);
}

// Ввод сообщения из файла
static bool fillFile(std::string& bits){
    using namespace std;

    string fileName;
    cout << "Имя файла: ";
    cin >> fileName;

    ifstream fin(fileName);

    if(!fin.is_open()){
        return false;
    }

    fin >> bits;

    return Check::isBinaryString(bits);
}

// Случайное сообщение
static bool fillRandom(std::string& bits){
    using namespace std;

    int n = Check::readIntMin("Количество бит: ", 1);

    static bool seeded = false;

    if(!seeded){
        srand((unsigned)time(nullptr));
        seeded = true;
    }

    bits.clear();

    for(int i = 0; i < n; ++i){
        bits += char('0' + rand() % 2);
    }

    cout << "Сгенерировано: " << bits << '\n';

    return true;
}

// Выбор способа заполнения битов
static bool fillBits3Ways(std::string& bits){
    int mode = Check::readIntRange("Заполнение: 1-клавиатура, 2-файл, 3-случайно: ", 1, 3);

    if(mode == 1){
        return fillKeyboard(bits);
    }

    if(mode == 2){
        return fillFile(bits);
    }

    return fillRandom(bits);
}

// Ввод текста с клавиатуры
static bool fillTextKeyboard(std::string& text){
    using namespace std;

    cout << "Введите текст: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, text);

    return !text.empty();
}

// Ввод текста из файла
static bool fillTextFile(std::string& text){
    using namespace std;

    string fileName;
    cout << "Имя файла: ";
    cin >> fileName;

    ifstream fin(fileName);

    if(!fin.is_open()){
        return false;
    }

    getline(fin, text);

    return !text.empty();
}

// Случайный текст
static bool fillTextRandom(std::string& text){
    using namespace std;

    int n = Check::readIntMin("Длина текста: ", 1);

    const string alphabet = "abcdef ";
    text.clear();

    static bool seeded = false;

    if(!seeded){
        srand((unsigned)time(nullptr));
        seeded = true;
    }

    for(int i = 0; i < n; ++i){
        text += alphabet[rand() % alphabet.size()];
    }

    cout << "Сгенерировано: " << text << '\n';

    return true;
}

// Выбор способа заполнения текста
static bool fillText3Ways(std::string& text){
    int mode = Check::readIntRange("Заполнение: 1-клавиатура, 2-файл, 3-случайно: ", 1, 3);

    if(mode == 1){
        return fillTextKeyboard(text);
    }

    if(mode == 2){
        return fillTextFile(text);
    }

    return fillTextRandom(text);
}

// Создать столбчатый шифр
TranspositionCipher::TranspositionCipher(int columns) : columns(columns){
}

// Зашифровать столбчатым шифром
std::string TranspositionCipher::encrypt(const std::string& text) const{
    std::string result;

    int rows = (int)(text.size() + columns - 1) / columns;

    for(int col = 0; col < columns; ++col){
        for(int row = 0; row < rows; ++row){
            int index = row * columns + col;

            if(index < (int)text.size()){
                result += text[index];
            }
        }
    }

    return result;
}

// Расшифровать столбчатый шифр
std::string TranspositionCipher::decrypt(const std::string& text) const{
    int rows = (int)(text.size() + columns - 1) / columns;
    int fullLastRow = (int)text.size() % columns;

    if(fullLastRow == 0){
        fullLastRow = columns;
    }

    std::string result(text.size(), ' ');

    int pos = 0;

    for(int col = 0; col < columns; ++col){
        int colHeight = rows;

        if(col >= fullLastRow){
            colHeight = rows - 1;
        }

        for(int row = 0; row < colHeight; ++row){
            int index = row * columns + col;

            result[index] = text[pos];
            ++pos;
        }
    }

    return result;
}

// Вывести таблицу шифрования
void TranspositionCipher::printTable(const std::string& text) const{
    using namespace std;

    int rows = (int)(text.size() + columns - 1) / columns;

    cout << "\nТаблица:\n";

    for(int row = 0; row < rows; ++row){
        for(int col = 0; col < columns; ++col){
            int index = row * columns + col;

            if(index < (int)text.size()){
                cout << text[index] << ' ';
            }
            else{
                cout << "_ ";
            }
        }

        cout << '\n';
    }
}

// Задание 1: код Хемминга
void HammingTask(){
    using namespace std;

    string bits;

    if(!fillBits3Ways(bits)){
        cout << "Ошибка заполнения сообщения\n";
        return;
    }

    HammingCode hamming(bits);

    cout << "\nДо подсчета контрольных битов:";
    hamming.printEmptyTable();

    hamming.encode();

    cout << "\nПосле подсчета контрольных битов:";
    hamming.printFullTable();

    hamming.printControlBits();

    cout << "\nКод Хемминга: ";
    hamming.printCode();

    int errorPosition = Check::readIntRange("Введите позицию ошибки: ", 1, hamming.getLength());

    hamming.addError(errorPosition);

    cout << "\nКод с ошибкой: ";
    hamming.printCode();

    int foundError = hamming.findError();

    if(foundError == 0){
        cout << "Ошибка не найдена\n";
    }
    else{
        cout << "Ошибка найдена в позиции: " << foundError << '\n';

        hamming.fixError(foundError);

        cout << "Исправленный код: ";
        hamming.printCode();
    }
}

// Задание 2: код Хаффмана
void HuffmanTask(){
    using namespace std;

    string text;

    if(!fillText3Ways(text)){
        cout << "Ошибка заполнения текста\n";
        return;
    }

    HuffmanCode huffman(text);
    huffman.build();

    cout << "\nИсходный текст: " << text << '\n';

    huffman.printTree();
    huffman.printTable();
    huffman.printStats();
}

// Задание 3: столбчатый шифр транспонирования
void TranspositionCipherTask(){
    using namespace std;

    string text;

    if(!fillText3Ways(text)){
        cout << "Ошибка заполнения текста\n";
        return;
    }

    int columns = Check::readIntRange("Количество столбцов: ", 2, (int)text.size());

    TranspositionCipher cipher(columns);

    cipher.printTable(text);

    string encrypted = cipher.encrypt(text);
    string decrypted = cipher.decrypt(encrypted);

    cout << "\nИсходный текст: " << text << '\n';
    cout << "Зашифрованный текст: " << encrypted << '\n';
    cout << "Расшифрованный текст: " << decrypted << '\n';

    if(text == decrypted){
        cout << "Расшифрование верное\n";
    }
    else{
        cout << "Ошибка расшифрования\n";
    }
}
