#include "init.h"

llint mulMod(llint x, llint y, llint p) {
    if (y == 0) return 0;
    if (x < 1000111000111000111LL / y) return x * y % p;
    llint mid = mulMod((x+x)%p, y>>1LL, p);
    if (y & 1) return (mid + x) % p;
    else return mid;
}
llint powMod(llint x, llint k, llint m) {
    if (k == 0) return 1;
    if ((k & 1)) return mulMod(x,powMod(x, k-1, m), m);
    else return powMod(mulMod(x,x,m), k/2, m);
}
bool suspect(llint a, llint s, llint d, llint n) {
    llint x = powMod(a, d, n);
    if (x == 1) return true;
    for (int r = 0; r < s; ++r) {
        if (x == n - 1) return true;
        x = mulMod(x, x, n);
    }
    return false;
}
// {2,7,61,-1}                 is for n < 4759123141 (= 2^32)
// {2,3,5,7,11,13,17,19,23,-1} is for n < 10^15 (at least)
// Killer prime: 5555555557LL (fail when not used mulMod)
bool isPrime(llint n) {
    if (n <= 1 || (n > 2 && n % 2 == 0)) return false;
    llint test[] = {2,3,5,7,11,13,17,19,23,-1};
    llint d = n - 1, s = 0;
    while (d % 2 == 0) ++s, d /= 2;
    for (int i = 0; test[i] < n && test[i] != -1; ++i)
        if (!suspect(test[i], s, d, n)) return false;
    return true;
}