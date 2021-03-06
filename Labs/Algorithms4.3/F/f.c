#include <stdio.h>

unsigned long long mul(unsigned long long a, unsigned long long b, unsigned long long n)
{
    unsigned long long d = 0;
    for (size_t i = 64; i > 0; --i)
    {
        d = (d + d) % n;
        if ((b >> (i - 1)) & 1)
        {
            d = (d + a) % n;
        }
    }
    return d;
}

unsigned long long mod_exp(unsigned long long a, unsigned long long b, unsigned long long n)
{
    unsigned long long d = 1;
    for (size_t i = 64; i > 0; --i)
    {
        d = mul(d, d, n);
        if ((b >> (i - 1)) & 1)
        {
            d = mul(d, a, n);
        }
    }
    return d;
}

long long inv(long long a, long long n)
{
    long long tmpa = a, tmpn = n, x = 1, y = 0, tmp;
    while (tmpn)
    {
        tmp = x - tmpa / tmpn * y;
        x = y;
        y = tmp;
        tmp = tmpa % tmpn;
        tmpa = tmpn;
        tmpn = tmp;
    }
    if (tmpa != 1)
    {
        return 0;
    }
    return (x + n) % n;
}

int main()
{
    unsigned long long n, e, C, q, p, M;
    long long d;
    scanf("%llu\n%llu\n%llu", &n, &e, &C);
    if (n & 1)
    {
        for (size_t i = 3; i * i <= n; i += 2)
        {
            if (!(n % i))
            {
                p = i;
                q = n / i;
                break;
            }
        }
    }
    else
    {
        p = 2;
        q = n >> 1;
    }

    //e * d = (p - 1) * (q - 1) * x + 1;

    d = inv(e, (p - 1) * (q - 1));

    M = mod_exp(C, d, n);
    printf("%llu\n", M);

    return 0;
}
