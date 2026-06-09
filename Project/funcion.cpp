#include "funcion.h"

#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <limits>
#include <string>

ProjectException::ProjectException(const std::string& message) : std::runtime_error(message){
}

FileReadException::FileReadException(const std::string& message) : ProjectException(message){
}

// Считать целое число
bool Check::readInt(const char* text, int& value){
    using namespace std;

    while(true){
        cout << text;

        if(cin >> value){
            return true;
        }

        if(cin.eof()){
            cout << "\nВвод завершен.\n";
            return false;
        }

        cout << "Ошибка ввода. Введите целое число.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// Считать число в диапазоне
bool Check::readIntRange(const char* text, int left, int right, int& value){
    using namespace std;

    while(true){
        if(!readInt(text, value)){
            return false;
        }

        if(value >= left && value <= right){
            return true;
        }

        cout << "Число должно быть в диапазоне [" << left << "; " << right << "].\n";
    }
}

// Создать карту
Card::Card() : value(0){
}

// Создать карту с номиналом
Card::Card(int value){
    setValue(value);
}

// Получить номинал карты
int Card::getValue() const{
    return value;
}

// Изменить номинал карты
void Card::setValue(int value){
    if(value >= 0 && value <= 9){
        this->value = value;
    }
    else{
        this->value = 0;
    }
}

// Проверить, бьет ли текущая карта другую
bool Card::beats(const Card& other) const{
    if(value == 0 && other.value == 9){
        return true;
    }

    if(value == 9 && other.value == 0){
        return false;
    }

    return value > other.value;
}

// Создать узел очереди
CardQueue::Node::Node(const Card& card) : card(card), next(nullptr){
}

// Получить карту из узла
Card CardQueue::Node::getCard() const{
    return card;
}

// Получить следующий узел
CardQueue::Node* CardQueue::Node::getNext() const{
    return next;
}

// Изменить следующий узел
void CardQueue::Node::setNext(CardQueue::Node* p){
    next = p;
}

// Создать очередь карт
CardQueue::CardQueue() : head(nullptr), tail(nullptr), count(0){
}

// Удалить очередь карт
CardQueue::~CardQueue(){
    clear();
}

// Конструктор копирования
CardQueue::CardQueue(const CardQueue& other) : head(nullptr), tail(nullptr), count(0){
    Node* p = other.head;

    while(p){
        push(p->getCard());
        p = p->getNext();
    }
}

// Оператор присваивания
CardQueue& CardQueue::operator=(const CardQueue& other){
    if(this == &other){
        return *this;
    }

    clear();
    Node* p = other.head;

    while(p){
        push(p->getCard());
        p = p->getNext();
    }

    return *this;
}

// Очистить очередь
void CardQueue::clear(){
    while(head){
        Node* p = head;
        head = head->getNext();
        delete p;
    }

    tail = nullptr;
    count = 0;
}

// Положить карту вниз колоды
void CardQueue::push(const Card& card){
    Node* p = new Node(card);

    if(!head){
        head = p;
        tail = p;
    }
    else{
        tail->setNext(p);
        tail = p;
    }

    ++count;
}

// Взять верхнюю карту
bool CardQueue::pop(Card& card){
    if(!head){
        return false;
    }

    Node* p = head;
    card = p->getCard();
    head = head->getNext();

    if(!head){
        tail = nullptr;
    }

    delete p;
    --count;
    return true;
}

// Проверить, пустая ли очередь
bool CardQueue::empty() const{
    return count == 0;
}

// Количество карт
int CardQueue::size() const{
    return count;
}

// Вывести очередь
void CardQueue::print() const{
    using namespace std;

    Node* p = head;

    while(p){
        cout << p->getCard().getValue() << ' ';
        p = p->getNext();
    }
}

// Создать базового игрока
PlayerBase::PlayerBase(const std::string& name) : name(name){
}

// Виртуальный деструктор
PlayerBase::~PlayerBase(){
}

// Создать игрока
Player::Player(const std::string& name) : PlayerBase(name){
}

// Получить имя игрока
std::string Player::getName() const{
    return name;
}

// Очистить колоду игрока
void Player::clear(){
    cards.clear();
}

// Дать карту игроку
void Player::giveCard(const Card& card){
    cards.push(card);
}

// Взять верхнюю карту игрока
bool Player::takeTop(Card& card){
    return cards.pop(card);
}

// Игрок забирает выигранные карты
void Player::takeWinCards(const Card& firstCard, const Card& secondCard){
    cards.push(firstCard);
    cards.push(secondCard);
}

// Проверить, есть ли карты
bool Player::hasCards() const{
    return !cards.empty();
}

// Количество карт игрока
int Player::cardCount() const{
    return cards.size();
}

// Вывести колоду игрока
void Player::printDeck() const{
    cards.print();
}

// Создать игру
DrunkardGame::DrunkardGame() : first("first"), second("second"), maxMoves(1000000){
}

// Проверить уникальность карт
bool DrunkardGame::cardsAreUnique(const int firstCards[], const int secondCards[]) const{
    bool used[10] = {false};

    for(int i = 0; i < 5; ++i){
        int x = firstCards[i];

        if(x < 0 || x > 9 || used[x]){
            return false;
        }

        used[x] = true;
    }

    for(int i = 0; i < 5; ++i){
        int x = secondCards[i];

        if(x < 0 || x > 9 || used[x]){
            return false;
        }

        used[x] = true;
    }

    return true;
}

// Установить карты игроков
bool DrunkardGame::setCards(const int firstCards[], const int secondCards[]){
    if(!cardsAreUnique(firstCards, secondCards)){
        return false;
    }

    first.clear();
    second.clear();

    for(int i = 0; i < 5; ++i){
        first.giveCard(Card(firstCards[i]));
    }

    for(int i = 0; i < 5; ++i){
        second.giveCard(Card(secondCards[i]));
    }

    return true;
}

// Вывести разделитель меню
static void printLine(){
    std::cout << "========================================\n";
}

// Вывести тонкий разделитель
static void printSmallLine(){
    std::cout << "----------------------------------------\n";
}

// Вывести заголовок игры
static void printTitle(){
    std::cout << '\n';
    printLine();
    std::cout << "              ИГРА ПЬЯНИЦА\n";
    printLine();
}

// Вывести главное меню
static void printMainMenu(){
    printTitle();
    std::cout << "  1. Новая игра\n";
    std::cout << "  2. Правила\n";
    std::cout << "  0. Выход\n";
    printSmallLine();
}

// Вывести меню выбора раздачи
static void printFillMenu(){
    std::cout << '\n';
    printSmallLine();
    std::cout << "Выберите способ раздачи карт\n";
    printSmallLine();
    std::cout << "  1. Ввести карты вручную\n";
    std::cout << "  2. Загрузить карты из файла\n";
    std::cout << "  3. Случайная раздача\n";
    std::cout << "  0. Выход из игры\n";
    printSmallLine();
}

// Вывести правила игры
static void printRules(){
    printTitle();
    std::cout << "Правила:\n";
    std::cout << "  * У каждого игрока по 5 карт.\n";
    std::cout << "  * Карты имеют номиналы от 0 до 9 без повторений.\n";
    std::cout << "  * Каждый ход игроки открывают верхнюю карту.\n";
    std::cout << "  * Победитель хода забирает обе карты вниз своей колоды.\n";
    std::cout << "  * Карта 0 бьет карту 9, остальные карты сравниваются по номиналу.\n";
    std::cout << "  * Если игра длится слишком долго, выводится ничья.\n";
}

// Вывести игроков
void DrunkardGame::printPlayers() const{
    using namespace std;

    printSmallLine();
    cout << "Первый игрок: ";
    first.printDeck();
    cout << '\n';

    cout << "Второй игрок: ";
    second.printDeck();
    cout << '\n';
    printSmallLine();
}

// Подобрать правильное слово для количества ходов
static const char* getMoveWord(int move){
    int lastTwo = move % 100;
    int lastOne = move % 10;

    if(lastTwo >= 11 && lastTwo <= 14){
        return "ходов";
    }

    if(lastOne == 1){
        return "ход";
    }

    if(lastOne >= 2 && lastOne <= 4){
        return "хода";
    }

    return "ходов";
}

// Запустить игру
void DrunkardGame::play(bool showProtocol){
    using namespace std;

    int move = 0;

    while(first.hasCards() && second.hasCards() && move < maxMoves){
        Card firstCard;
        Card secondCard;

        first.takeTop(firstCard);
        second.takeTop(secondCard);
        ++move;

        if(showProtocol){
            cout << "Ход " << move << ": ";
            cout << firstCard.getValue() << " против " << secondCard.getValue() << " -> ";
        }

        if(firstCard.beats(secondCard)){
            first.takeWinCards(firstCard, secondCard);

            if(showProtocol){
                cout << "выиграл первый игрок\n";
            }
        }
        else{
            second.takeWinCards(firstCard, secondCard);

            if(showProtocol){
                cout << "выиграл второй игрок\n";
            }
        }
    }

    if(move == maxMoves){
        cout << "Ничья: игра не закончилась за " << maxMoves << " ходов.\n";
        return;
    }

    if(first.hasCards()){
        cout << "Победил первый игрок за " << move << ' ' << getMoveWord(move) << ".\n";
    }
    else{
        cout << "Победил второй игрок за " << move << ' ' << getMoveWord(move) << ".\n";
    }
}

// Ручной ввод карт
static bool fillKeyboard(int firstCards[], int secondCards[]){
    printSmallLine();
    std::cout << "Введите 5 карт первого игрока:\n";
    for(int i = 0; i < 5; ++i){
        int card;
        if(!Check::readIntRange("Карта: ", 0, 9, card)){
            return false;
        }
        firstCards[i] = card;
    }

    std::cout << "Введите 5 карт второго игрока:\n";
    for(int i = 0; i < 5; ++i){
        int card;
        if(!Check::readIntRange("Карта: ", 0, 9, card)){
            return false;
        }
        secondCards[i] = card;
    }

    printSmallLine();
    return true;
}

// Ввод карт из файла
static bool fillFile(int firstCards[], int secondCards[]){
    using namespace std;

    string fileName;
    cout << "Введите имя файла: ";
    cin >> fileName;

    ifstream fin(fileName);
    if(!fin.is_open()){
        throw FileReadException("Не удалось открыть файл с картами.");
    }

    for(int i = 0; i < 5; ++i){
        int x;
        if(!(fin >> x)){
            throw FileReadException("В файле недостаточно карт первого игрока.");
        }
        firstCards[i] = x;
    }

    for(int i = 0; i < 5; ++i){
        int x;
        if(!(fin >> x)){
            throw FileReadException("В файле недостаточно карт второго игрока.");
        }
        secondCards[i] = x;
    }

    return true;
}

// Случайная раздача карт
static bool fillRandom(int firstCards[], int secondCards[]){
    using namespace std;

    int deck[10];
    for(int i = 0; i <= 9; ++i){
        deck[i] = i;
    }

    static bool seeded = false;
    if(!seeded){
        srand((unsigned)time(nullptr));
        seeded = true;
    }

    for(int i = 0; i < 10; ++i){
        int j = rand() % 10;
        int t = deck[i];
        deck[i] = deck[j];
        deck[j] = t;
    }

    for(int i = 0; i < 5; ++i){
        firstCards[i] = deck[i];
    }

    for(int i = 5; i < 10; ++i){
        secondCards[i - 5] = deck[i];
    }

    return true;
}

// Выбор способа заполнения
static bool fillCards(int firstCards[], int secondCards[]){
    while(true){
        printFillMenu();

        int mode;
        if(!Check::readIntRange("Ваш выбор: ", 0, 3, mode)){
            return false;
        }

        if(mode == 0){
            std::cout << "\nВыход из игры.\n";
            return false;
        }

        bool filled = false;

        try{
            if(mode == 1){
                filled = fillKeyboard(firstCards, secondCards);
            }
            else if(mode == 2){
                filled = fillFile(firstCards, secondCards);
            }
            else{
                filled = fillRandom(firstCards, secondCards);
            }
        }
        catch(const ProjectException& error){
            std::cout << "Ошибка: " << error.what() << '\n';
            filled = false;
        }

        if(filled){
            return true;
        }

        std::cout << "Ошибка заполнения карт. Попробуйте еще раз.\n";
    }
}

// Подготовить новую партию
static bool prepareGame(DrunkardGame& game){
    using namespace std;

    int firstCards[5];
    int secondCards[5];

    while(true){
        if(!fillCards(firstCards, secondCards)){
            return false;
        }

        if(game.setCards(firstCards, secondCards)){
            return true;
        }

        cout << "Ошибка: карты должны быть числами от 0 до 9 и не повторяться.\n";
        cout << "Попробуйте заполнить карты еще раз.\n";
    }
}

// Главный сценарий проекта
void runProject(){
    using namespace std;

    bool work = true;

    while(work){
        printMainMenu();

        int menuChoice;
        if(!Check::readIntRange("Ваш выбор: ", 0, 2, menuChoice)){
            return;
        }

        if(menuChoice == 0){
            cout << "\nВыход из игры.\n";
            return;
        }

        if(menuChoice == 2){
            printRules();
            continue;
        }

        bool playAgain = true;
        DrunkardGame game;

        if(!prepareGame(game)){
            return;
        }

        while(playAgain){
            cout << "\nНачальная раздача:\n";
            game.printPlayers();

            int protocol;
            if(!Check::readIntRange("Показывать протокол ходов? 1-да, 0-нет: ", 0, 1, protocol)){
                return;
            }

            cout << "\nРезультат игры:\n";
            printSmallLine();
            game.play(protocol == 1);
            printSmallLine();

            int answer;
            std::cout << "\nЧто дальше?\n";
            std::cout << "  1. Сыграть еще раз\n";
            std::cout << "  2. Вернуться в главное меню\n";
            std::cout << "  0. Выход из игры\n";
            printSmallLine();

            if(!Check::readIntRange("Ваш выбор: ", 0, 2, answer)){
                return;
            }

            playAgain = (answer == 1);

            if(answer == 0){
                cout << "\nВыход из игры.\n";
                return;
            }

            if(playAgain && !prepareGame(game)){
                return;
            }
        }
    }
}
