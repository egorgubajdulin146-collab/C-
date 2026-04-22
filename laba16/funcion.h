#ifndef FUNCION_H
#define FUNCION_H

#include <vector>

class Check{
public:
    static int readInt(const char* text);
    static int readIntMin(const char* text, int minValue);
    static int readIntRange(const char* text, int left, int right);
};

class BinaryTree{
private:
    class Node{
    private:
        int data;
        Node* left;
        Node* right;

    public:
        Node(int value);

        int getData() const;
        Node* getLeft() const;
        Node* getRight() const;

        void setData(int value);
        void setLeft(Node* p);
        void setRight(Node* p);
    };

    Node* root;

    void clear(Node* p);
    void insert(Node*& p, int value);
    void buildByLevels(const std::vector<int>& values);

    void printLeaves(Node* p) const;
    int countLeaves(Node* p) const;

    int height(Node* p) const;
    bool isAvl(Node* p) const;

public:
    BinaryTree();
    ~BinaryTree();

    void clear();
    void insert(int value);

    bool fillKeyboardBinary();
    bool fillFileBinary();
    bool fillRandomBinary();

    void print() const;

    void runTreeWork4() const;
    void runTreeWork13() const;
    void runTreeWork20() const;
};

void TreeWork4();
void TreeWork13();
void TreeWork20();


#endif
