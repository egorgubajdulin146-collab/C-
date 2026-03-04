#ifndef LAB11_H
#define LAB11_H

#include <string>

class Node {
public:
    int data;
    Node* next;

    Node(int value = 0);
};

class PNode {
public:
    int data;
    PNode* prev;
    PNode* next;

    PNode(int value = 0);
};

class CircularList {
private:
    Node* head;
    int sizeList;

    Node* getTail() const;
    void copyFrom(const CircularList& other);

public:
    CircularList();
    CircularList(const CircularList& other);
    CircularList& operator=(const CircularList& other);
    ~CircularList();

    bool empty() const;
    int size() const;

    void pushBack(int value);
    bool removeFirst(int value);
    bool contains(int value) const;
    void clear();
    void print() const;

    bool fillKeyboard(int minCount);
    bool fillFile(const std::string& fileName, int minCount);
    bool fillRandom(int n, int left, int right, int minCount);

    bool writeByStepAndErase(int k, const std::string& outFileName); // ListWork69
};

class DoublyList {
private:
    PNode* head;
    PNode* tail;
    int sizeList;

    void copyFrom(const DoublyList& other);

public:
    DoublyList();
    DoublyList(const DoublyList& other);
    DoublyList& operator=(const DoublyList& other);
    ~DoublyList();

    bool empty() const;
    int size() const;

    void pushBack(int value);
    bool removeFirstValue(int value);
    bool contains(int value) const;
    void clear();

    void printForward() const;
    void printBackward() const;

    bool fillKeyboard(int minCount);
    bool fillFile(const std::string& fileName, int minCount);
    bool fillRandom(int n, int left, int right, int minCount);

    void printBetweenMinMax() const;                         // ListWork41
    bool writeReverseAndErase(const std::string& outFileName); // ListWork63
};

void ListWork69();
void ListWork41();
void ListWork63();
void ListWork46();
void Text4();

#endif
