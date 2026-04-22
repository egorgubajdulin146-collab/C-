#ifndef FUNCION_H
#define FUNCION_H

#include <fstream>
#include <string>

class Check{
public:
    static int readInt(const char* text);
    static int readIntMin(const char* text, int minValue);
    static int readIntRange(const char* text, int left, int right);
};

class CalcTree{
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
    int height(Node* p) const;

    int calculate(Node* p) const;
    int calculateWithX(Node* p, int x) const;

    void replaceDivision(Node*& p);
    bool containsX(Node* p) const;
    void replaceXSubtrees(Node*& p, int x);

    void printNodeValue(int value) const;
    void printSideToFile(Node* p, std::ofstream& fout, int level) const;

    std::string makeRandomPostfix(int countOperands) const;

    Node* parseExpression(const std::string& s, int& i);
    Node* parseAddSub(const std::string& s, int& i);
    Node* parseMulDivMod(const std::string& s, int& i);
    Node* parsePower(const std::string& s, int& i);
    Node* parseValue(const std::string& s, int& i);

public:
    CalcTree();
    ~CalcTree();

    void clear();

    bool buildPostfix(const std::string& expression);
    bool buildInfix(const std::string& expression);

    bool fillKeyboardPostfix();
    bool fillFilePostfix();
    bool fillRandomPostfix();

    bool fillKeyboardInfix(int& x, std::string& outFileName);
    bool fillFileInfix(int& x, std::string& outFileName);
    bool fillRandomInfix(int& x, std::string& outFileName);

    void print() const;

    void removeDivisionOperations();
    void replaceXOperations(int x);

    int calculateExpression(int x) const;

    void printRootPointer() const;
    void writeCalcTree26Result(const std::string& outFileName, int result) const;
};

void CalcTree4();
void CalcTree26();
void printCat();

#endif
