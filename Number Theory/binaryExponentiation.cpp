long long power(long long A, long long B)
{
    if (B == 0)
        return 1;
    long long res = power(A, B / 2);
    if (B % 2)
        return res * res * A;
    else
        return res * res;
}

long long power(long long a, long long b, long long m) {
    a %= m;
    long long res = 1;
    while (b > 0) {
        if (b & 1)
            res = res * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return res;
}