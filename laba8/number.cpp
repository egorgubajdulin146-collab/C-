#include <iostream>
#include <iomanip>

#include "tasks.h"

//ункция подсчета K-ичных чисел длины N
long double countKNumbers(int N, int K) {
    long long int nz, _nz, oz, _oz, tz, _tz, trz, _trz, fz, _fz;

    nz = K - 1;
    oz = 1;
    tz = 0;
    trz = 0;
    fz = 0;
    for(int i = 2; i <= N; i++){
        _nz = nz;
        _oz = oz;
        _tz = tz;
        _trz = trz;
        _fz = fz;
        nz = _nz * (K - 1) + _oz * (K - 1) + _tz * (K - 1) + _trz * (K - 1);
        oz = _nz;
        tz = _oz;
        trz = _tz;
        fz = _fz * K + _trz;
    }

    return fz;

}

void solveKNumbers(std::istream& in, std::ostream& out) {
    using namespace std;
    int N, K;
    if (!(in >> N >> K)) return;

    long double ans = countKNumbers(N, K);
    cout << "Ответ: ";
    out << fixed << setprecision(0) << ans << '\n';
}

