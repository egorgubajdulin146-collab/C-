#include "funcion.h"

#include <iostream>
#include <limits>

using namespace std;

// Считать целое число с проверкой
static int readInt(const string& prompt) {
    int x;
    while (true) {
        cout << prompt;
        if (cin >> x) return x;

        cout << "Ошибка ввода. Введите целое число.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// Считать целое число не меньше minVal
static int readIntMin(const string& prompt, int minVal) {
    while (true) {
        int x = readInt(prompt);
        if (x >= minVal) return x;
        cout << "Число должно быть >= " << minVal << ".\n";
    }
}

// Считать целое число в диапазоне [l; r]
static int readIntRange(const string& prompt, int l, int r) {
    while (true) {
        int x = readInt(prompt);
        if (x >= l && x <= r) return x;
        cout << "Число должно быть в диапазоне [" << l << "; " << r << "].\n";
    }
}

// Считать одно слово
static string readWord(const string& prompt) {
    string s;
    cout << prompt;
    cin >> s;
    return s;
}

// Выбрать режим: демонстрация или клавиатура
static int readMode() {
    return readIntRange("1 - демонстрация, 2 - клавиатура: ", 1, 2);
}

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
    cout << toString() << '\n';
}

// Конструктор Person
Person::Person(const string& n, int h) : name(n), height(h) {
}

// Преобразовать Person в строку
string Person::toString() const {
    return name + ", рост: " + to_string(height);
}

// Вывести Person
void Person::print() const {
    cout << toString() << '\n';
}

// Конструктор Department
Department::Department(const string& t) : title(t), boss(nullptr) {
}

// Назначить начальника
void Department::setBoss(Employee* b) {
    boss = b;
}

// Добавить сотрудника в отдел
void Department::addEmployee(Employee* e) {
    for (vector<Employee*>::iterator it = workers.begin(); it != workers.end(); ++it) {
        if (*it == e) return;
    }
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

// Получить список сотрудников
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
    cout << toString() << '\n';
}

// Вывести сотрудников отдела
void Department::printWorkers() const {
    cout << "Сотрудники отдела " << title << ": ";
    for (vector<Employee*>::const_iterator it = workers.begin(); it != workers.end(); ++it) {
        cout << (*it)->getName() << ' ';
    }
    cout << '\n';
}

// Конструктор Employee
Employee::Employee(const string& n, Department* d) : name(n), department(nullptr) {
    setDepartment(d);
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
    cout << toString() << '\n';
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
    cout << toString() << '\n';
}

// Выстрел
void Pistol::shoot() {
    if (bullets > 0) {
        cout << "Бах!\n";
        bullets--;
    } else {
        cout << "Клац!\n";
    }
}

// Задание 1
void runTask1() {
    cout << "\nЗадание 1\n";
    int mode = readMode();

    if (mode == 1) {
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
    } else {
        cout << "\nВведите 3 объекта Name:\n";

        Name n1(readWord("Личное имя 1: "));
        Name n2(
            readWord("Личное имя 2: "),
            readWord("Отчество 2: "),
            readWord("Фамилия 2: ")
        );
        Name n3(
            readWord("Личное имя 3: "),
            readWord("Фамилия 3: ")
        );

        cout << "\nИмена:\n";
        n1.print();
        n2.print();
        n3.print();

        cout << "\nВведите 3 объекта Person:\n";
        Person p1(readWord("Имя 1: "), readIntMin("Рост 1: ", 1));
        Person p2(readWord("Имя 2: "), readIntMin("Рост 2: ", 1));
        Person p3(readWord("Имя 3: "), readIntMin("Рост 3: ", 1));

        cout << "\nЛюди:\n";
        p1.print();
        p2.print();
        p3.print();
    }
}

// Задание 2
void runTask2() {
    cout << "\nЗадание 2\n";
    int mode = readMode();

    if (mode == 1) {
        Department dep("IT");

        vector<Employee> staff;
        staff.reserve(3);

        staff.emplace_back("Петров");
        staff.emplace_back("Козлов");
        staff.emplace_back("Сидоров");

        for (vector<Employee>::iterator it = staff.begin(); it != staff.end(); ++it) {
            it->setDepartment(&dep);
        }

        dep.setBoss(&staff[1]);

        cout << "\nИнформация о сотрудниках:\n";
        for (vector<Employee>::iterator it = staff.begin(); it != staff.end(); ++it) {
            it->print();
        }

        cout << "\nИнформация об отделе:\n";
        dep.print();
    } else {
        string depTitle = readWord("Название отдела: ");
        Department dep(depTitle);

        int n = readIntMin("Количество сотрудников: ", 1);

        vector<Employee> staff;
        staff.reserve(n);

        for (int i = 0; i < n; ++i) {
            string empName = readWord("Имя сотрудника: ");
            staff.emplace_back(empName);
        }

        for (vector<Employee>::iterator it = staff.begin(); it != staff.end(); ++it) {
            it->setDepartment(&dep);
        }

        cout << "\nСотрудники:\n";
        for (int i = 0; i < n; ++i) {
            cout << i + 1 << " - " << staff[i].getName() << '\n';
        }

        int bossIndex = readIntRange("Номер начальника: ", 1, n);
        dep.setBoss(&staff[bossIndex - 1]);

        cout << "\nИнформация о сотрудниках:\n";
        for (vector<Employee>::iterator it = staff.begin(); it != staff.end(); ++it) {
            it->print();
        }

        cout << "\nИнформация об отделе:\n";
        dep.print();
    }
}

// Задание 3
void runTask3() {
    cout << "\nЗадание 3\n";
    int mode = readMode();

    if (mode == 1) {
        Department dep("IT");

        vector<Employee> staff;
        staff.reserve(3);

        staff.emplace_back("Петров");
        staff.emplace_back("Козлов");
        staff.emplace_back("Сидоров");

        for (vector<Employee>::iterator it = staff.begin(); it != staff.end(); ++it) {
            it->setDepartment(&dep);
        }

        dep.setBoss(&staff[1]);

        cout << "\nИнформация о сотрудниках:\n";
        for (vector<Employee>::iterator it = staff.begin(); it != staff.end(); ++it) {
            it->print();
        }

        cout << "\nИнформация об отделе:\n";
        dep.print();
        dep.printWorkers();
    } else {
        string depTitle = readWord("Название отдела: ");
        Department dep(depTitle);

        int n = readIntMin("Количество сотрудников: ", 1);

        vector<Employee> staff;
        staff.reserve(n);

        for (int i = 0; i < n; ++i) {
            string empName = readWord("Имя сотрудника: ");
            staff.emplace_back(empName);
        }

        for (vector<Employee>::iterator it = staff.begin(); it != staff.end(); ++it) {
            it->setDepartment(&dep);
        }

        cout << "\nСотрудники:\n";
        for (int i = 0; i < n; ++i) {
            cout << i + 1 << " - " << staff[i].getName() << '\n';
        }

        int bossIndex = readIntRange("Номер начальника: ", 1, n);
        dep.setBoss(&staff[bossIndex - 1]);

        cout << "\nИнформация о сотрудниках:\n";
        for (vector<Employee>::iterator it = staff.begin(); it != staff.end(); ++it) {
            it->print();
        }

        cout << "\nИнформация об отделе:\n";
        dep.print();
        dep.printWorkers();
    }
}

// Задание 4
void runTask4() {
    cout << "\nЗадание 4\n";
    int mode = readMode();

    if (mode == 1) {
        Name n1("Клеопатра");
        Name n2("Александр", "Сергеевич", "Пушкин");
        Name n3("Владимир", "Маяковский");
        Name n4("Христофор", "Бонифатьевич");

        n1.print();
        n2.print();
        n3.print();
        n4.print();
    } else {
        cout << "\nСоздание через разные конструкторы:\n";

        Name n1(readWord("Только личное имя: "));
        Name n2(
            readWord("Личное имя (объект 2): "),
            readWord("Отчество (объект 2): "),
            readWord("Фамилия (объект 2): ")
        );
        Name n3(
            readWord("Личное имя (объект 3): "),
            readWord("Фамилия (объект 3): ")
        );
        Name n4(
            readWord("Личное имя (объект 4): "),
            readWord("Фамилия (объект 4): ")
        );

        cout << "\nРезультат:\n";
        n1.print();
        n2.print();
        n3.print();
        n4.print();
    }
}

// Задание 5
void runTask5() {
    cout << "\nЗадание 5\n";
    int mode = readMode();

    if (mode == 1) {
        Pistol gun(3);
        gun.print();

        for (int i = 0; i < 5; ++i) {
            gun.shoot();
        }

        gun.print();
    } else {
        cout << "1 - пистолет по умолчанию, 2 - задать количество патронов\n";
        int type = readIntRange("Выбор: ", 1, 2);

        Pistol gun;

        if (type == 2) {
            int bullets = readIntMin("Количество патронов: ", 0);
            gun = Pistol(bullets);
        }

        int shots = readIntMin("Сколько раз стрелять: ", 1);

        gun.print();
        for (int i = 0; i < shots; ++i) {
            gun.shoot();
        }
        gun.print();
    }
}
