#include <iostream>
#include <iomanip>

#include "tasks.h"

//ункция подсчета K-ичных чисел длины N
long double countKNumbers(int N, int K) {
    long double dp[21][5] = {};

    dp[1][0] = K - 1; 

    for (int i = 1; i < N; ++i) {
        for (int j = 0; j < 4; ++j) {
            dp[i+1][0] += dp[i][j] * (K - 1);
        }
        
        for (int j = 0; j < 3; ++j) {
            dp[i+1][j+1] += dp[i][j];
        }
        
        dp[i+1][4] = dp[i][4] * K + dp[i][3]; 
    }

    return dp[N][4];
}

void solveKNumbers(std::istream& in, std::ostream& out) {
    using namespace std;
    int N, K;
    if (!(in >> N >> K)) return;

    long double ans = countKNumbers(N, K);

    out << fixed << setprecision(0) << ans << '\n';
}

