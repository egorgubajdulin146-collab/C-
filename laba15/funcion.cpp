#include "funcion.h"

#include <iostream>


// Конструктор Name
Name::Name(const std::string& s, const std::string& f, const std::string& p)
    : surname(s), firstName(f), patronymic(p) {
}

// Преобразовать Name в строку
std::string Name::toString() const {
    using namespace std;
    string result;

    if (!surname.empty()) {
        result += surname;
    }

    if (!firstName.empty()) {
        if (!result.empty()) result += " ";
        result += firstName;
    }

    if (!patronymic.empty()) {
        if (!result.empty()) result += " ";
        result += patronymic;
    }

    return result;
}

// Вывести Name
void Name::print() const {
    using namespace std;
    cout << toString() << endl;
}

// Конструктор Person
Person::Person(const std::string& n, int h)
    : name(n), height(h) {
}

// Преобразовать Person в строку
std::string Person::toString() const {
    return name + ", рост: " + std::to_string(height);
}

// Вывести Person
void Person::print() const {
    using namespace std;
    cout << toString() << endl;
}

// Конструктор Department
Department::Department(const std::string& t)
    : title(t), boss(nullptr) {
}

// Назначить начальника
void Department::setBoss(Employee* b) {
    boss = b;
}

// Добавить сотрудника в отдел
void Department::addEmployee(Employee* e) {
    workers.push_back(e);
}

// Получить название отдела
std::string Department::getTitle() const {
    return title;
}

// Получить начальника
Employee* Department::getBoss() const {
    return boss;
}

// Получить список сотрудников
const std::vector<Employee*>& Department::getWorkers() const {
    return workers;
}

// Преобразовать Department в строку
std::string Department::toString() const {
    if (boss == nullptr) {
        return title + ", начальник не назначен";
    }

    return title + ", начальник: " + boss->getName();
}

// Вывести Department
void Department::print() const {
    using namespace std;
    cout << toString() << endl;
}

// Вывести всех сотрудников отдела
void Department::printWorkers() const {
    using namespace std;
    cout << "Сотрудники отдела " << title << ": ";

    for (vector<Employee*>::const_iterator it = workers.begin(); it != workers.end(); ++it) {
        cout << (*it)->getName() << ' ';
    }

    cout << endl;
}

// Конструктор Employee
Employee::Employee(const std::string& n, Department* d)
    : name(n), department(d) {
    if (department != nullptr) {
        department->addEmployee(this);
    }
}

// Назначить отдел
void Employee::setDepartment(Department* d) {
    department = d;
    if (department != nullptr) {
        department->addEmployee(this);
    }
}

// Получить имя сотрудника
std::string Employee::getName() const {
    return name;
}

// Получить отдел сотрудника
Department* Employee::getDepartment() const {
    return department;
}

// Преобразовать Employee в строку
std::string Employee::toString() const {
    if (department == nullptr) {
        return name + " не работает ни в одном отделе";
    }

    if (department->getBoss() == this) {
        return name + " начальник отдела " + department->getTitle();
    }

    if (department->getBoss() == nullptr) {
        return name + " работает в отделе " + department->getTitle() + ", начальник не назначен";
    }

    return name + " работает в отделе " + department->getTitle() +
           ", начальник которого " + department->getBoss()->getName();
}

// Вывести Employee
void Employee::print() const {
    using namespace std;
    cout << toString() << endl;
}

// Задание 1
void runTask1() {
    using namespace std;
    cout << "\nЗадание 1\n";

    cout << "\nИмена:\n";
    Name n1("", "Клеопатра", "");
    Name n2("Пушкин", "Александр", "Сергеевич");
    Name n3("Маяковский", "Владимир", "");

    n1.print();
    n2.print();
    n3.print();

    cout << "\nЛюди:\n";
    Person p1("Клеопатра", 152);
    Person p2("Пушкин", 167);
    Person p3("Владимир", 189);

    p1.print();
    p2.print();
    p3.print();
}

// Задание 2
void runTask2() {
    using namespace std;
    cout << "\nЗадание 2\n";

    Department it("IT");

    Employee p1("Петров", &it);
    Employee p2("Козлов", &it);
    Employee p3("Сидоров", &it);

    it.setBoss(&p2);

    p1.print();
    p2.print();
    p3.print();
}

// Задание 3
void runTask3() {
    using namespace std;
    cout << "\nЗадание 3\n";

    Department it("IT");

    Employee p1("Петров", &it);
    Employee p2("Козлов", &it);
    Employee p3("Сидоров", &it);

    it.setBoss(&p2);

    cout << "\nИнформация о сотрудниках:\n";
    p1.print();
    p2.print();
    p3.print();

    cout << "\nПолучаем отдел по сотруднику Петров:\n";
    Department* dep = p1.getDepartment();

    if (dep != nullptr) {
        dep->print();
        dep->printWorkers();
    }
}

// Задание 4
void runTask4() {
    using namespace std;
    cout << "\nЗадание 4 пока не реализовано.\n";
}

// Задание 5
void runTask5() {
    using namespace std;
    cout << "\nЗадание 5 пока не реализовано.\n";
}
