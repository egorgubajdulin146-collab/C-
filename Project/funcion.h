#ifndef FUNCION_H
#define FUNCION_H

#include <stdexcept>
#include <string>

class ProjectException : public std::runtime_error{
public:
    ProjectException(const std::string& message);
};

class FileReadException : public ProjectException{
public:
    FileReadException(const std::string& message);
};

class Check{
public:
    static bool readInt(const char* text, int& value);
    static bool readIntRange(const char* text, int left, int right, int& value);
};

class Card{
private:
    int value;

public:
    Card();
    Card(int value);

    int getValue() const;
    void setValue(int value);
    bool beats(const Card& other) const;
};

class CardQueue{
private:
    class Node{
    private:
        Card card;
        Node* next;

    public:
        Node(const Card& card);

        Card getCard() const;
        Node* getNext() const;
        void setNext(Node* p);
    };

    Node* head;
    Node* tail;
    int count;

public:
    CardQueue();
    ~CardQueue();

    CardQueue(const CardQueue& other);
    CardQueue& operator=(const CardQueue& other);

    void clear();
    void push(const Card& card);
    bool pop(Card& card);
    bool empty() const;
    int size() const;
    void print() const;
};

class PlayerBase{
protected:
    std::string name;

public:
    PlayerBase(const std::string& name);
    virtual ~PlayerBase();

    virtual std::string getName() const = 0;
};

class Player : public PlayerBase{
private:
    CardQueue cards;

public:
    Player(const std::string& name);

    std::string getName() const override;
    void clear();
    void giveCard(const Card& card);
    bool takeTop(Card& card);
    void takeWinCards(const Card& firstCard, const Card& secondCard);
    bool hasCards() const;
    int cardCount() const;
    void printDeck() const;
};

class DrunkardGame{
private:
    Player first;
    Player second;
    int maxMoves;

    bool cardsAreUnique(const int firstCards[], const int secondCards[]) const;

public:
    DrunkardGame();

    bool setCards(const int firstCards[], const int secondCards[]);
    void printPlayers() const;
    void play(bool showProtocol);
};

void runProject();

#endif
