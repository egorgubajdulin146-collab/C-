#ifndef FUNCION_H
#define FUNCION_H

class Check{
public:
    static int readInt(const char* text);
    static int readIntMin(const char* text, int minValue);
    static int readIntRange(const char* text, int left, int right);
};

class Node{
public:
    int data;
    Node* left;
    Node* right;

    Node(int value);
};

class BinaryTree{
private:
    Node* root;

    void clear(Node* p);
    void insert(Node*& p, int value);
    void printTree(Node* p, int space) const;

    void printLeaves(Node* p) const;
    int countLeaves(Node* p) const;

    int height(Node* p) const;
    bool isAvl(Node* p) const;

public:
    BinaryTree();
    ~BinaryTree();

    void clear();
    void insert(int value);

    bool fillKeyboard();
    bool fillFile();
    bool fillRandom();

    void print() const;

    void runTreeWork4() const;
    void runTreeWork13() const;
    void runTreeWork20() const;
};

void TreeWork4();
void TreeWork13();
void TreeWork20();


#endif