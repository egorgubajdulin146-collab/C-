#include "funcion.h"
#include <fstream>
#include <iostream>
using namespace std;

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
    if(!q.head) q.head = nullptr;

    delete p;
    return true;
}

//вывести очередь от head к tail
void printqueue(const Queue& q){
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

//снять 9 верхних элементов стека и вывести новый P2
void dynamic6(PNode& top){
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


