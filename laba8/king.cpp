#include <iostream>
#include <fstream>
#include <climits>

#include "tasks.h"

const int MAXN = 80;
const int INF = INT_MAX / 4;

int a[MAXN][MAXN];
int dp[MAXN][MAXN];
char parentmove[MAXN][MAXN];

// Ввод: читает N и матрицу a[N][N] из потока (файл или клавиатура).
// Возврат: true если прочиталось, иначе false.
bool read(std::istream& in, int& N){
    using namespace std;
    if(!(in >> N)) return false;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            in >> a[i][j];
        }
    }
    return true;
}

// Считает таблицу dp и массив parentMove для восстановления пути.
// Стартовая клетка: (0, N-1) — правый верхний угол.
// Конечная клетка:  (N-1, 0) — левый нижний угол.
// Разрешённые ходы короля: только влево (L) или вниз (D).
void solvedp(int n){
    for(int i = 0; i < n; i++){
        for(int j = n - 1; j >= 0; j--){
            if(i == 0 && j == n - 1){
                dp[i][j] = a[i][j];
                parentmove[i][j] = 'S';
                continue;
            }

            int best = INF;
            char move = '?';

            if(j + 1 < n && dp[i][j + 1] < best){
                best = dp[i][j + 1];
                move = 'L';
            }

            if(i - 1 >= 0 && dp[i - 1][j] < best){
                best = dp[i - 1][j];
                move = 'D';
            }

            dp[i][j] = a[i][j] + best;
            parentmove[i][j] = move;
        }
    }
}

// Записывает путь в массив path (символы 'L' и 'D') и возвращает длину пути.
int buildPath(int N, char* path) {
    int i = N - 1;
    int j = 0;
    int len = 0;

    while (!(i == 0 && j == N - 1)) {
        char mv = parentmove[i][j];
        path[len++] = mv;
        if (mv == 'L') {
            j += 1;
        } else if (mv == 'D') {
            i -= 1;
        } else {
            break;
        }
    }

    for (int k = 0; k < len / 2; ++k) {
        char tmp = path[k];
        path[k] = path[len - 1 - k];
        path[len - 1 - k] = tmp;
    }
    return len;
}

// 1 строка — минимальная сумма неприятностей
// 2 строка — путь (строка из символов L и D)
void writeAnswer(std::ostream& out, int minSum, const char* path, int pathLen) {
    out << minSum << '\n';
    for (int i = 0; i < pathLen; ++i) out << path[i];
    out << '\n';
}

void solveLameKing(std::istream& in, std::ostream& out) {
    int N;
    if (!read(in, N)) return;

    solvedp(N);

    char path[2 * MAXN];
    int len = buildPath(N, path);

    writeAnswer(out, dp[N - 1][0], path, len);
}
