#ifndef FUNCION_H
#define FUNCION_H

#include <string>
#include <vector>

class Check{
public:
    static int readInt(const char* text);
    static int readIntMin(const char* text, int minValue);
    static int readIntRange(const char* text, int left, int right);
};

class Graph{
private:
    int n;
    std::vector<std::vector<int> > a;

    std::vector<int> bfs(int start) const;

public:
    Graph();

    bool fillKeyboard(int maxN);
    bool fillFile(const std::string& fileName, int maxN);
    bool fillRandom(int maxN, bool directed);

    void print() const;
    bool empty() const;
    int size() const;

    void writeIncidenceMatrix(const std::string& fileName) const;
    void printCommonCities(int k1, int k2, int l) const;
    void printCitiesFromKWithMinTransfers(int k, int l) const;
};

void Graf2();
void Graf7();
void Graf8();
void printCat();

#endif
