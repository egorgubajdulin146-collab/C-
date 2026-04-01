#ifndef FUNCION_H
#define FUNCION_H

#include <string>
#include <vector>

class Name {
private:
    std::string surname;
    std::string firstName;
    std::string patronymic;

public:
    Name(const std::string& s = "", const std::string& f = "", const std::string& p = "");

    std::string toString() const;
    void print() const;
};

class Person {
private:
    std::string name;
    int height;

public:
    Person(const std::string& n = "", int h = 0);

    std::string toString() const;
    void print() const;
};

class Employee;

class Department {
private:
    std::string title;
    Employee* boss;
    std::vector<Employee*> workers;

public:
    Department(const std::string& t = "");

    void setBoss(Employee* b);
    void addEmployee(Employee* e);

    std::string getTitle() const;
    Employee* getBoss() const;
    const std::vector<Employee*>& getWorkers() const;

    std::string toString() const;
    void print() const;
    void printWorkers() const;
};

class Employee {
private:
    std::string name;
    Department* department;

public:
    Employee(const std::string& n = "", Department* d = nullptr);

    void setDepartment(Department* d);

    std::string getName() const;
    Department* getDepartment() const;

    std::string toString() const;
    void print() const;
};

void runTask1();
void runTask2();
void runTask3();
void runTask4();
void runTask5();

#endif
