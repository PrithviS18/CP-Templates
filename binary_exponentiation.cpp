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

ll power(ll A, ll B,ll mod)
{
    if (B == 0)
        return 1;
    long long res = power(A, B / 2);
    if (B % 2)
        return (res * res * A)%mod;
    else
        return (res * res)%mod;
}