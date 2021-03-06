// TODO
// NOTE: Don't know why, but there are not enough
// accuracy with more than 1 digit in 1 block.
// Maybe it was because of some bugs whitch were
// fixed, but i'm too lazy to remake the programm now.

#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <math.h>
//2^19
#define POLINOM_SIZE 524288
#define MAX_NUM_SIZE 250000
#define PI 3.1415926535897932384626433832795

int read_num(int* a, size_t size)
{
    char c;
    int sign, fig_read = 1;
    if ((c = getchar()) == '-')
    {
        sign = -1;
        c = getchar();
    }
    else
    {
        sign = 1;
    }
    char num[MAX_NUM_SIZE];
    num[0] = c;
    for (size_t i = 1; i < MAX_NUM_SIZE; ++i)
    {
        if ((c = getchar()) == '\n' || c == EOF)
        {
            break;
        }
        num[i] = c;
        ++fig_read;
    }

    for (int i = 0; i < fig_read && i < size; ++i)
    {
        a[i] = num[fig_read - i - 1] - '0';
    }

    for (int i = fig_read; i < size; ++i)
    {
        a[i] = 0;
    }

    return sign;
}

void write_num(int* a, size_t size, int sign)
{
    if (!size)
    {
        putchar('0');
        return;
    }

    if (sign < 0)
    {
        putchar('-');
    }

    for (size_t i = 1; i <= size; ++i)
    {
        putchar(a[size - i]  + '0');
    }
}

void dft(double complex* a, size_t size, char rev)
{
    if (size == 1)
    {
        return;
    }

    size_t new_size = size >> 1;
    double complex* a0 = (double complex*)malloc((new_size) * sizeof(double complex));
    double complex* a1 = (double complex*)malloc((new_size) * sizeof(double complex));

    for (size_t i = 0; i < size; i += 2)
    {
        a0[i >> 1] = a[i];
        a1[i >> 1] = a[i + 1];
    }

    dft(a0, new_size, rev);
    dft(a1, new_size, rev);

    double ang = 2 * PI / size * (rev ? -1 : 1);
    double complex w = 1, w_step = cos(ang) + sin(ang) * I;
    for (size_t i = 0; i < new_size; ++i)
    {
        a[i] = a0[i] + w * a1[i];
        a[i + new_size] = a0[i] - w * a1[i];
        if (rev)
        {
            a[i] /= 2;
            a[i + new_size] /= 2;
        }
        w *= w_step;
    }

    free(a0);
    free(a1);
}

int main()
{
    //freopen("input.in", "r", stdin);
    //freopen("output.out", "w", stdout);
    int sign, div = 0;
    int* a_i = (int*)malloc(POLINOM_SIZE * sizeof(int));
    int* b_i = (int*)malloc(POLINOM_SIZE * sizeof(int));
    double complex* a = (double complex*)malloc(POLINOM_SIZE * sizeof(double complex));
    double complex* b = (double complex*)malloc(POLINOM_SIZE * sizeof(double complex));

    sign = read_num(a_i, POLINOM_SIZE);
    
    for (size_t i = 0; i < POLINOM_SIZE; ++i)
    {
        a[i] = (double complex)a_i[i];
    }

    sign *= read_num(b_i, POLINOM_SIZE);

    for (size_t i = 0; i < POLINOM_SIZE; ++i)
    {
        b[i] = (double complex)b_i[i];
    }

    dft(a, POLINOM_SIZE, 0);
    dft(b, POLINOM_SIZE, 0);

    for (size_t i = 0; i < POLINOM_SIZE; ++i)
    {
        a[i] *= b[i];
    }

    dft(a, POLINOM_SIZE, 1);

    for(size_t i = 0; i < POLINOM_SIZE; ++i)
    {
        a_i[i] = (int)(creal(a[i]) + 0.5);
    }

    size_t not_null = 0;

    for (size_t i = 0; i < POLINOM_SIZE; ++i)
    {
        a_i[i] += div;
        div = a_i[i] / 10;
        a_i[i] %= 10;
        if (a_i[i])
        {
            not_null = i + 1;
        }
    }

    write_num(a_i, not_null, sign);

    free(a);
    free(b);
    free(a_i);
    free(b_i);
    
    return 0;
}
