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
 
    // Initialize answer
    int res = 1;
 
    // Check till the number becomes zero
    while (y > 0) {
 
        // If y is odd, multiply x with result
        if (y % 2 == 1)
            res = (res * x);
 
        // y = y/2
        y = y >> 1;
 
        // Change x to x^2
        x = (x * x);
    }
    return res % p;
}