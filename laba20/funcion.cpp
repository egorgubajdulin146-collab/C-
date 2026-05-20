#include "funcion.h"

#include <iostream>
#include <limits>

int Check::readIntRange(const char* text, int left, int right){
    using namespace std;

    int x;

    while(true){
        cout << text;

        if(cin >> x && x >= left && x <= right){
            return x;
        }

        cout << "Ошибка ввода. Введите число от " << left << " до " << right << ".\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// Считать вещественное число не меньше minValue
double Check::readDoubleMin(const char* text, double minValue){
    using namespace std;

    double x;

    while(true){
        cout << text;

        if(cin >> x && x >= minValue){
            return x;
        }

        cout << "Ошибка ввода. Введите число >= " << minValue << ".\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// Конструктор по умолчанию
RightTriangle::RightTriangle() : a(1), b(1){
}

// Конструктор с параметрами
RightTriangle::RightTriangle(double a, double b){
    setA(a);
    setB(b);
}

// Конструктор копирования
RightTriangle::RightTriangle(const RightTriangle& other) : a(other.a), b(other.b){
}

// Ввод катетов
void RightTriangle::input(){
    a = Check::readDoubleMin("Введите катет a: ", 0);
    b = Check::readDoubleMin("Введите катет b: ", 0);
}

// Получить катет a
double RightTriangle::getA() const{
    return a;
}

// Получить катет b
double RightTriangle::getB() const{
    return b;
}

// Изменить катет a
void RightTriangle::setA(double value){
    if(value >= 0){
        a = value;
    }
    else{
        a = 0;
    }
}

// Изменить катет b
void RightTriangle::setB(double value){
    if(value >= 0){
        b = value;
    }
    else{
        b = 0;
    }
}

// Проверить существование треугольника
bool RightTriangle::exists() const{
    return a > 0 && b > 0;
}

// Вычислить площадь
double RightTriangle::area() const{
    if(!exists()){
        return -1;
    }

    return a * b / 2.0;
}

//увеличивает катеты в 2 раза
RightTriangle& RightTriangle::operator++(){
    a *= 2;
    b *= 2;

    return *this;
}

//уменьшает катеты в 2 раза
RightTriangle& RightTriangle::operator--(){
    a /= 2;
    b /= 2;

    return *this;
}

// Явное приведение к double
RightTriangle::operator double() const{
    return area();
}

// Неявное приведение к bool
RightTriangle::operator bool() const{
    return exists();
}

// Сравнить площади <=
bool RightTriangle::operator<=(const RightTriangle& other) const{
    return area() <= other.area();
}

// Сравнить площади >=
bool RightTriangle::operator>=(const RightTriangle& other) const{
    return area() >= other.area();
}

// Вывод треугольника
std::ostream& operator<<(std::ostream& out, const RightTriangle& t){
    out << "a = " << t.a << ", b = " << t.b << ", S = " << t.area();

    return out;
}