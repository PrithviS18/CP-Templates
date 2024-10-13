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

int power(int x, int y, int p)
{
    int res = 1;
    while (y > 0) {
        if (y % 2 == 1)
            res = (res * x);
        y = y >> 1;
        x = (x * x);
    }
    return res % p;
}