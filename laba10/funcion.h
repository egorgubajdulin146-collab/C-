#ifndef LAB10_VARIANT4_H
#define LAB10_VARIANT4_H

#include <string>

// Узел для стека/очереди/списка
struct Node {
    int data;
    Node* next;

    explicit Node(int value) : data(value), next(nullptr) {}
};

using PNode = Node*;

struct Queue {
    PNode head;
    PNode tail;

    Queue() : head(nullptr), tail(nullptr) {}
};

void push(PNode& top, int value);
bool pop(PNode& top, int& value);
void printstack(PNode top);
void clearstack(PNode& top);

void enqueue(Queue& q, int value);
bool dequeue(Queue& q, int& value);
void printqueue(const Queue& q);
void clearqueue(Queue& q);

void pushback(PNode& head, PNode& tail, int value);
void printlist(PNode head);
void clearlist(PNode& head);
void sortik(PNode& head, int value);
void fillStack(PNode& top, int minN);
void fillQueue(Queue& q);
void fillList(PNode& head, PNode& tail, int minN);

void dynamic6(PNode& top);

void dynamic21(Queue& first, Queue& second);

PNode listWork4(PNode head);

PNode listWork25(PNode& head, int m);

bool listWork62(const std::string& fileName, PNode& head);

#endif
