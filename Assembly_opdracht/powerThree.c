#include <stdio.h>

unsigned int power(unsigned int n, unsigned int m);

// This function must be implemented in LEGv7 Pinky assembly
unsigned int power(unsigned int n, unsigned int m)
{
    if (m == 0) return 1;
    if (m == 1) return n;
    if ((m & 1) == 0) /* m is even */ return power(n * n,  m >> 1);
    else /* m is odd */ return n * power(n * n, m >> 1);
}

int main()
{
    extern void initialise_monitor_handles(void);
    initialise_monitor_handles();

    unsigned int a = 7;
    unsigned int b = 11;

    if (power(a, b) == 1977326743)
    {
        printf("OK\n");
    }
    else
    {
        printf("Error\n");
    }
    return 0;
}
