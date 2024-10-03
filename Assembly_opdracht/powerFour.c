#include <stdio.h>

unsigned int power(unsigned int n, unsigned int m);

// Placeholder for the multiply function you already implemented in LEGv7 Pinky assembly
unsigned int multiply(unsigned int a, unsigned int b)
{
    return a * b;
}

// This function must be implemented in LEGv7 Pinky assembly
unsigned int power2(unsigned int p, unsigned int n, unsigned int m)
{
    if (m == 0) return p;
    if (m == 1) return multiply(p, n);
    if ((m & 1) == 0) /* m is even */ return power2(p, multiply(n, n),  m >> 1);
    else /* m is odd */ return power2(multiply(p, n), multiply(n, n), m >> 1);
}

unsigned int power(unsigned int n, unsigned int m)
{
    return power2(1, n, m);
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
