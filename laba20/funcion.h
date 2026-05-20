#ifndef FUNCION_H
#define FUNCION_H

#include <iostream>

class Check{
public:
    static int readIntRange(const char* text, int left, int right);
    static double readDoubleMin(const char* text, double minValue);
};

class RightTriangle{
private:
    double a;
    double b;

public:
    RightTriangle();
    RightTriangle(double a, double b);
    RightTriangle(const RightTriangle& other);

    void input();

    double getA() const;
    double getB() const;

    void setA(double value);
    void setB(double value);

    double area() const;
    bool exists() const;

    RightTriangle& operator++();
    RightTriangle& operator--();

    explicit operator double() const;
    operator bool() const;

    bool operator<=(const RightTriangle& other) const;
    bool operator>=(const RightTriangle& other) const;

    friend std::ostream& operator<<(std::ostream& out, const RightTriangle& t);
};

#endif