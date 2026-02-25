#include "funcion.h"
#include <fstream>
#include <iostream>

//добавить элемент в вершину стека
void push(PNode& top, int value){
    PNode p = new Node(value);
    p->next = top;
    top = p;
}

//извлечь верхний элемент стека и вернуть его в value

bool pop(PNode& top, int& value){
    if(!top) return false;

    PNode p = top;
    value = p->data;
    top = top->next;
    delete p;
    return true;

}

//вывести стек от вершины к низу
void printstack(PNode top){
    using namespace std;
    cout << "stack: ";
    while(top){
        cout << top->data << ' ';
        top = top->next;
    }
    cout << endl;
}

//очистить стек и освободить память
void clearstack(PNode& top){
    while(top){
        PNode p = top;
        top = top->next;
        delete p;
    }
}

//добавить элемент в конец очереди
void enqueue(Queue& q, int value){
    PNode p = new Node(value);

    if(!q.head){
        q.head = p;
        q.tail = p;
    }
    else{
        q.tail->next = p;
        q.tail = p;
    }
}

//удалить элемент из начала очереди и вернуть его в value
bool dequeue(Queue& q, int& value){
    if(!q.head) return false;

    PNode p = q.head;
    value = p->data;
    q.head = q.head->next;
    if(!q.head) q.tail = nullptr;

    delete p;
    return true;
}

//вывести очередь от head к tail
void printqueue(const Queue& q){
    using namespace std;
    cout << "queue: ";
    PNode p = q.head;
    while(p){
        cout << p->data << ' ';
        p = p->next;
    }
    cout << endl;
}

//очистить очередь и освободить память
void clearqueue(Queue& q){
    while(q.head){
        PNode p = q.head;
        q.head = q.head->next;
        delete p;
    }
    q.tail = nullptr;
}

//добавить элемент в конец односвязного списка
void pushback(PNode& head, PNode& tail, int value){
    PNode p = new Node(value);

    if(!head){
        head = p;
        tail = p;
    }
    else{
        tail->next = p;
        tail = p;
    }
}

//вывести список от головы к концу
void printlist(PNode head){
    using namespace std;
    cout << "list: ";
    while(head){
        cout << head->data << ' ';
        head = head->next;
    }
    cout << endl;
}

//очистить список и освободить память
void clearlist(PNode& head){
    while(head){
        PNode p = head;
        head = head -> next;
        delete p;
    }
}

void fillStack(PNode& top, int minN) {
    using namespace std;
    int method = 0;
    cout << "Способ заполнения стека: 1-клавиатура, 2-файл, 3-случайно: ";
    cin >> method;

    int n = 0;

    if (method == 1) {
        cout << "Введите количество элементов: ";
        cin >> n;
        if (n < minN) {
            cout << "Нужно минимум " << minN << " элементов\n";
            return;
        }

        cout << "Введите " << n << " чисел: ";
        for (int i = 0; i < n; ++i) {
            int x;
            cin >> x;
            push(top, x);
        }
    } else if (method == 2) {
        string fileName;
        cout << "Введите имя файла: ";
        cin >> fileName;
        ifstream fin(fileName);
        if (!fin.is_open()) {
            cout << "Не удалось открыть файл\n";
            return;
        }

        fin >> n;
        if (n < minN) {
            cout << "В файле меньше чем " << minN << " элементов\n";
            return;
        }

        for (int i = 0; i < n; ++i) {
            int x;
            fin >> x;
            push(top, x);
        }
    } else if (method == 3) {
        int l, r;
        cout << "Введите количество элементов: ";
        cin >> n;
        if (n < minN) {
            cout << "Нужно минимум " << minN << " элементов\n";
            return;
        }

        cout << "Введите диапазон [L R]: ";
        cin >> l >> r;
        if (l > r) {
            int t = l;
            l = r;
            r = t;
        }

        cout << "Сгенерировано: ";
        for (int i = 0; i < n; ++i) {
            int x = l + rand() % (r - l + 1);
            cout << x << ' ';
            push(top, x);
        }
        cout << '\n';
    } else {
        cout << "Неверный способ\n";
    }
}

void fillQueue(Queue& q) {
    using namespace std;
    int method = 0;
    cout << "Способ заполнения очереди: 1-клавиатура, 2-файл, 3-случайно: ";
    cin >> method;

    int n = 0;

    if (method == 1) {
        cout << "Введите количество элементов: ";
        cin >> n;
        cout << "Введите " << n << " чисел: ";
        for (int i = 0; i < n; ++i) {
            int x;
            cin >> x;
            enqueue(q, x);
        }
    } else if (method == 2) {
        string fileName;
        cout << "Введите имя файла: ";
        cin >> fileName;
        ifstream fin(fileName);
        if (!fin.is_open()) {
            cout << "Не удалось открыть файл\n";
            return;
        }

        fin >> n;
        for (int i = 0; i < n; ++i) {
            int x;
            fin >> x;
            enqueue(q, x);
        }
    } else if (method == 3) {
        int l, r;
        cout << "Введите количество элементов: ";
        cin >> n;
        cout << "Введите диапазон [L R]: ";
        cin >> l >> r;
        if (l > r) {
            int t = l;
            l = r;
            r = t;
        }

        cout << "Сгенерировано: ";
        for (int i = 0; i < n; ++i) {
            int x = l + rand() % (r - l + 1);
            cout << x << ' ';
            enqueue(q, x);
        }
        cout << '\n';
    } else {
        cout << "Неверный способ\n";
    }
}

void fillList(PNode& head, PNode& tail, int minN) {
    using namespace std;
    int method = 0;
    cout << "Способ заполнения списка: 1-клавиатура, 2-файл, 3-случайно: ";
    cin >> method;

    int n = 0;

    if (method == 1) {
        cout << "Введите количество элементов: ";
        cin >> n;
        if (n < minN) {
            cout << "Нужно минимум " << minN << " элементов\n";
            return;
        }

        cout << "Введите " << n << " чисел: ";
        for (int i = 0; i < n; ++i) {
            int x;
            cin >> x;
            pushback(head, tail, x);
        }
    } else if (method == 2) {
        string fileName;
        cout << "Введите имя файла: ";
        cin >> fileName;
        ifstream fin(fileName);
        if (!fin.is_open()) {
            cout << "Не удалось открыть файл\n";
            return;
        }

        fin >> n;
        if (n < minN) {
            cout << "В файле меньше чем " << minN << " элементов\n";
            return;
        }

        for (int i = 0; i < n; ++i) {
            int x;
            fin >> x;
            pushback(head, tail, x);
        }
    } else if (method == 3) {
        int l, r;
        cout << "Введите количество элементов: ";
        cin >> n;
        if (n < minN) {
            cout << "Нужно минимум " << minN << " элементов\n";
            return;
        }

        cout << "Введите диапазон [L R]: ";
        cin >> l >> r;
        if (l > r) {
            int t = l;
            l = r;
            r = t;
        }

        cout << "Сгенерировано: ";
        for (int i = 0; i < n; ++i) {
            int x = l + rand() % (r - l + 1);
            cout << x << ' ';
            pushback(head, tail, x);
        }
        cout << '\n';
    } else {
        cout << "Неверный способ\n";
    }
}

//вставка значения в список по убыванию
void sortik(PNode& head, int value){
    PNode p = new Node(value);

    if(!head || value > head->data){
        p->next = head;
        head = p;
        return;
    }

    PNode cur = head;
    while(cur-> next && cur->next->data >= value){
        cur = cur->next;
    }

    p->next = cur->next;
    cur->next = p;
}

//снять 9 верхних элементов стека и вывести новый P2
void dynamic6(PNode& top){
    using namespace std;
    cout << "Извлекаем 9 элементов: ";
    for(int i = 0; i < 9; i++){
        int x;
        if(!pop(top, x)) break;
        cout << x << ' ';
    }
    cout << endl;

    if(top){
        cout << "P2 = " << top << endl;
    }
    else{
        cout << "P2 = nullptr" << endl;
    }
}

//перенести все элементы первой очереди в конец второй
void dynamic21(Queue& first, Queue& second){
    if(!first.head) return;

    if(!second.head){
        second.head = first.head;
        second.tail = first.tail;
    }
    else{
        second.tail->next = first.head;
        second.tail = first.tail;
    }

    first.head = nullptr;
    first.tail = nullptr;
}

//вернуть указатель на 5-й элемент списка
PNode listWork4(PNode head){
    for(int i = 1; i < 5 && head; i++){
        head = head->next;
    }
    return head;
}

//вставить M перед каждым вторым элементом, вернуть хвост P2
PNode listWork25(PNode& head, int m){
    if(!head || !head->next) return head;

    PNode prew = head;
    PNode curr = head->next;
    int pos = 2;

    while(curr){
        if(pos % 2 == 0){
            PNode ins = new Node(m);
            prew->next = ins;
            ins->next = curr;

            prew = curr;
            curr = curr->next;
            pos++;
        }
        else{
            prew = curr;
            curr = curr->next;
            pos++;
        }
    }

    PNode tail = head;
    while(tail && tail->next) tail = tail->next;
    return tail;
}

//прочитать N чисел из файла и собрать список по убыванию
bool listWork62(const std::string& filename, PNode& head){
    using namespace std;
    ifstream fin(filename);
    if(!fin.is_open()) return false;

    int n;
    fin >> n;

    for(int i = 0; i < n; i++){
        int x;
        fin >> x;
        sortik(head, x);
    }

    return true;
}
