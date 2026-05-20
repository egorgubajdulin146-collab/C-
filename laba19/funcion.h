#ifndef FUNCION_H
#define FUNCION_H

#include <string>
#include <vector>

class Check{
public:
    static int readInt(const char* text);
    static int readIntMin(const char* text, int minValue);
    static int readIntRange(const char* text, int left, int right);
    static bool isBinaryString(const std::string& s);
};

class HammingCode{
private:
    std::string data;
    std::vector<int> code;
    int m;
    int r;
    int n;

    bool isPowerOfTwo(int x) const;
    void buildEmptyCode();
    void calculateControlBits();
    int calculateSyndrome() const;

public:
    HammingCode(const std::string& bits);

    void encode();
    void printEmptyTable() const;
    void printFullTable() const;
    void printControlBits() const;

    int getLength() const;
    void addError(int position);
    int findError() const;
    void fixError(int position);
    void printCode() const;
};

class HuffmanNode{
private:
    char symbol;
    int count;
    HuffmanNode* left;
    HuffmanNode* right;

public:
    HuffmanNode(char symbol, int count);
    HuffmanNode(HuffmanNode* left, HuffmanNode* right);

    char getSymbol() const;
    int getCount() const;
    HuffmanNode* getLeft() const;
    HuffmanNode* getRight() const;

    bool isLeaf() const;
};

class HuffmanCode{
private:
    std::string text;
    HuffmanNode* root;
    std::vector<char> symbols;
    std::vector<std::string> codes;

    void clear(HuffmanNode* p);
    void buildCodes(HuffmanNode* p, const std::string& code);
    int findSymbol(char c) const;
    int uniqueCount() const;
    int bitsForUniform() const;

public:
    HuffmanCode(const std::string& text);
    ~HuffmanCode();

    void build();
    void printTree() const;
    void printTree(HuffmanNode* p, int level) const;
    void printTable() const;
    void printStats() const;
    std::string encode() const;
};

class TranspositionCipher{
private:
    int columns;

public:
    TranspositionCipher(int columns);

    std::string encrypt(const std::string& text) const;
    std::string decrypt(const std::string& text) const;
    void printTable(const std::string& text) const;
};

void HammingTask();
void HuffmanTask();
void TranspositionCipherTask();

#endif