#include <iostream>
#include <climits>
#include <fstream>

#include "tasks.h"

void printEmpty(std::ostream& out) {
    out << '\n' << 0 << ' ' << 0 << '\n';
}

// Читает n, z и массивы c[] и d[] (выделяет память под них).
// Возвращает false, если вход пустой.
bool readInput(std::istream& in, int& n, long long& z, int*& c, long long*& d) {
    if (!(in >> n >> z)) return false;
    c = new int[n + 1];
    d = new long long[n + 1];
    for (int i = 1; i <= n; i++) in >> c[i];
    for (int i = 1; i <= n; i++) in >> d[i];
    return true;
}

// Считает сумму весов и максимальный вес.
void calcSumAndMax(int n, int* c, long long& sumw, int& maxc) {
    sumw = 0;
    maxc = 0;
    for (int i = 1; i <= n; i++) {
        sumw += c[i];
        if (c[i] > maxc) maxc = c[i];
    }
}

// Вычисляет cap = min(sumw, target + maxc) для варианта "вес не меньше target".
int calcCap(long long sumw, long long target, int maxc) {
    long long capll = sumw;
    long long alt = target + (long long)maxc;
    if (alt < capll) capll = alt;
    return (int)capll;
}

// Инициализирует dp и массивы родителей.
void initDP(int cap, long long* dp, int* parentitem, int* parentprevw, long long INF) {
    for (int i = 0; i <= cap; i++) {
        dp[i] = INF;
        parentitem[i] = -1;
        parentprevw[i] = -1;
    }
    dp[0] = 0;
}

// Основное ДП (0/1 рюкзак на минимальный налог) для варианта "вес не меньше target".
// dp[w] = минимальный налог, чтобы набрать вес w (0..cap), где cap — верхняя граница,
// а все веса > cap "склеиваются" в cap.
void runDP(int n, int cap, int* c, long long* d,
           long long* dp, int* parentitem, int* parentprevw, long long INF) {
    for (int i = 1; i <= n; i++) {
        int wi = c[i];
        long long cost = d[i];
        for (int j = cap; j >= 0; j--) {
            if (dp[j] == INF) continue;
            int nj = j + wi;
            if (nj > cap) nj = cap;
            long long nc = dp[j] + cost;
            if (nc < dp[nj]) {
                dp[nj] = nc;
                parentitem[nj] = i;
                parentprevw[nj] = j;
            }
        }
    }
}

// Выбирает вес bestw >= target с минимальным dp[bestw].
int chooseBestW(int cap, long long target, long long* dp, long long INF) {
    long long bestcost = INF;
    int bestw = -1;
    int start = (int)target;
    if (start > cap) start = cap;
    for (int w = start; w <= cap; w++) {
        if (dp[w] < bestcost) {
            bestcost = dp[w];
            bestw = w;
        }
    }
    return bestw;
}

// Восстанавливает выбранные предметы, возвращает их количество.
int restorePicked(int bestw, int* parentitem, int* parentprevw, int* picked) {
    int pickedCount = 0;
    for (int w = bestw; w > 0; ) {
        int it = parentitem[w];
        int pw = parentprevw[w];
        if (it == -1 || pw == -1) break;
        picked[pickedCount++] = it;
        w = pw;
    }
    return pickedCount;
}

// Простая сортировка вставками.
void insertionSort(int* a, int n) {
    for (int i = 1; i < n; ++i) {
        int key = a[i];
        int j = i - 1;
        while (j >= 0 && a[j] > key) {
            a[j + 1] = a[j];
            --j;
        }
        a[j + 1] = key;
    }
}

// Считает итоговый вес и налог.
void calcTotals(int pickedCount, int* picked, int* c, long long* d,
                long long& totalW, long long& totalTax) {
    totalW = 0;
    totalTax = 0;
    for (int i = 0; i < pickedCount; ++i) {
        int idx = picked[i];
        totalW += c[idx];
        totalTax += d[idx];
    }
}

// Печатает ответ.
void printAnswer(std::ostream& out, int pickedCount, int* picked, long long totalW, long long totalTax) {
    for (int i = 0; i < pickedCount; ++i) {
        if (i) out << ' ';
        out << picked[i];
    }
    out << '\n';
    out << totalW << ' ' << totalTax << '\n';
}

void solveArtifactsMinTax(std::istream& in, std::ostream& out) {
    int n;
    long long z;
    int* c = 0;
    long long* d = 0;

    if (!readInput(in, n, z, c, d)) return;

    long long target = z;
    long long sumw;
    int maxc;
    calcSumAndMax(n, c, sumw, maxc);

    if (sumw < target) {
        printEmpty(out);
        delete[] c;
        delete[] d;
        return;
    }

    int cap = calcCap(sumw, target, maxc);

    const long long INF = LLONG_MAX / 4;
    long long* dp = new long long[cap + 1];
    int* parentitem = new int[cap + 1];
    int* parentprevw = new int[cap + 1];
    initDP(cap, dp, parentitem, parentprevw, INF);

    runDP(n, cap, c, d, dp, parentitem, parentprevw, INF);

    int bestw = chooseBestW(cap, target, dp, INF);
    if (bestw == -1) {
        printEmpty(out);
        delete[] dp;
        delete[] parentitem;
        delete[] parentprevw;
        delete[] c;
        delete[] d;
        return;
    }

    int* picked = new int[n];
    int pickedCount = restorePicked(bestw, parentitem, parentprevw, picked);
    insertionSort(picked, pickedCount);

    long long totalW, totalTax;
    calcTotals(pickedCount, picked, c, d, totalW, totalTax);
    printAnswer(out, pickedCount, picked, totalW, totalTax);

    delete[] picked;
    delete[] dp;
    delete[] parentitem;
    delete[] parentprevw;
    delete[] c;
    delete[] d;
}
