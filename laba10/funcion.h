#ifndef FUNCION_H
#define FUNCION_H

#include <string>

class Stack {
private:
    struct Node {
        int data;
        Node* next;
        Node(int v, Node* n = nullptr) : data(v), next(n) {}
    };

    Node* top_;
    void copyFrom(const Stack& other);

public:
    Stack();
    Stack(const Stack& other);
    Stack& operator=(const Stack& other);
    ~Stack();

    void push(int value);
    bool pop(int& value);
    bool find(int value) const;
    bool isEmpty() const;
    void clear();
    void print() const;
    const void* topAddress() const;

    bool fillKeyboard(int minN);
    bool fillFile(const std::string& fileName, int minN);
    bool fillRandom(int n, int l, int r, int minN);

    void solveDynamic6();
};

class QueueDS {
private:
    struct Node {
        int data;
        Node* next;
        explicit Node(int v) : data(v), next(nullptr) {}
    };

    Node* head_;
    Node* tail_;
    void copyFrom(const QueueDS& other);

public:
    QueueDS();
    QueueDS(const QueueDS& other);
    QueueDS& operator=(const QueueDS& other);
    ~QueueDS();

    void enqueue(int value);
    bool dequeue(int& value);
    bool find(int value) const;
    bool isEmpty() const;
    void clear();
    void print() const;
    const void* headAddress() const;
    const void* tailAddress() const;

    bool fillKeyboard();
    bool fillFile(const std::string& fileName);
    bool fillRandom(int n, int l, int r);

    void moveAllTo(QueueDS& second);
};

class SinglyList {
private:
    struct Node {
        int data;
        Node* next;
        explicit Node(int v) : data(v), next(nullptr) {}
    };

    Node* head_;
    Node* tail_;
    void copyFrom(const SinglyList& other);

public:
    SinglyList();
    SinglyList(const SinglyList& other);
    SinglyList& operator=(const SinglyList& other);
    ~SinglyList();

    void pushBack(int value);
    bool find(int value) const;
    bool removeFirst(int value);
    bool isEmpty() const;
    void clear();
    void print() const;
    const void* headAddress() const;
    const void* tailAddress() const;

    bool fillKeyboard(int minN);
    bool fillFile(const std::string& fileName, int minN);
    bool fillRandom(int n, int l, int r, int minN);

    const void* fifthAddress() const;
    bool fifthValue(int& value) const;

    void insertBeforeEachSecond(int m);

    void insertSortedDesc(int value);
    bool buildSortedDescFromFile(const std::string& fileName);
};

#endif
