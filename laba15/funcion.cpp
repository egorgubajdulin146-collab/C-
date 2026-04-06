#include "funcion.h"

#include <iostream>

using namespace std;

// Конструктор Name без параметров
Name::Name() : firstName(""), patronymic(""), surname("") {
}

// Конструктор Name только с именем
Name::Name(const string& first) : firstName(first), patronymic(""), surname("") {
}

// Конструктор Name с именем и фамилией
Name::Name(const string& first, const string& sur)
    : firstName(first), patronymic(""), surname(sur) {
}

// Конструктор Name с именем, отчеством и фамилией
Name::Name(const string& first, const string& patr, const string& sur)
    : firstName(first), patronymic(patr), surname(sur) {
}

// Преобразовать Name в строку
string Name::toString() const {
    string result;

    if (!firstName.empty()) {
        result += firstName;
    }

    if (!patronymic.empty()) {
        if (!result.empty()) result += " ";
        result += patronymic;
    }

    if (!surname.empty()) {
        if (!result.empty()) result += " ";
        result += surname;
    }

    return result;
}

// Вывести Name
void Name::print() const {
    cout << toString() << endl;
}

// Конструктор Person
Person::Person(const string& n, int h)
    : name(n), height(h) {
}

// Преобразовать Person в строку
string Person::toString() const {
    return name + ", рост: " + to_string(height);
}

// Вывести Person
void Person::print() const {
    cout << toString() << endl;
}

// Конструктор Department
Department::Department(const string& t)
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
string Department::getTitle() const {
    return title;
}

// Получить начальника
Employee* Department::getBoss() const {
    return boss;
}

// Получить сотрудников
const vector<Employee*>& Department::getWorkers() const {
    return workers;
}

// Преобразовать Department в строку
string Department::toString() const {
    if (boss == nullptr) {
        return title + ", начальник не назначен";
    }

    return title + ", начальник: " + boss->getName();
}

// Вывести Department
void Department::print() const {
    cout << toString() << endl;
}

// Вывести сотрудников отдела
void Department::printWorkers() const {
    cout << "Сотрудники отдела " << title << ": ";

    for (vector<Employee*>::const_iterator it = workers.begin(); it != workers.end(); ++it) {
        cout << (*it)->getName() << ' ';
    }

    cout << endl;
}

// Конструктор Employee
Employee::Employee(const string& n, Department* d)
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
string Employee::getName() const {
    return name;
}

// Получить отдел
Department* Employee::getDepartment() const {
    return department;
}

// Преобразовать Employee в строку
string Employee::toString() const {
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
    cout << toString() << endl;
}

// Конструктор Pistol без параметров
Pistol::Pistol() : bullets(5) {
}

// Конструктор Pistol с количеством патронов
Pistol::Pistol(int count) : bullets(count) {
}

// Преобразовать Pistol в строку
string Pistol::toString() const {
    return "Пистолет, патронов: " + to_string(bullets);
}

// Вывести Pistol
void Pistol::print() const {
    cout << toString() << endl;
}

// Выстрел
void Pistol::shoot() {
    if (bullets > 0) {
        cout << "Бах!" << endl;
        bullets--;
    } else {
        cout << "Клац!" << endl;
    }
}

// Задание 1
void runTask1() {
    cout << "\nЗадание 1\n";

    cout << "\nИмена:\n";
    Name n1("Клеопатра");
    Name n2("Александр", "Сергеевич", "Пушкин");
    Name n3("Владимир", "Маяковский");

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

    cout << "\nПо ссылке на сотрудника Петров получаем список отдела:\n";
    Department* dep = p1.getDepartment();

    if (dep != nullptr) {
        dep->print();
        dep->printWorkers();
    }
}

// Задание 4
void runTask4() {
    cout << "\nЗадание 4\n";

    Name n1("Клеопатра");
    Name n2("Александр", "Сергеевич", "Пушкин");
    Name n3("Владимир", "Маяковский");
    Name n4("Христофор", "Бонифатьевич");

    n1.print();
    n2.print();
    n3.print();
    n4.print();
}

// Задание 5
void runTask5() {
    cout << "\nЗадание 5\n";

    Pistol gun(3);
    gun.print();

    gun.shoot();
    gun.shoot();
    gun.shoot();
    gun.shoot();
    gun.shoot();

    gun.print();
}
