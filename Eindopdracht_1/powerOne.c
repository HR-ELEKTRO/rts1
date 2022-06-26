#include <stdio.h>

unsigned int power(unsigned int n, unsigned int m);

// This function must be implemented in LEGv7 Pinky assembly
unsigned int power(unsigned int n, unsigned int m)
{
    unsigned int p = 1;

    for (unsigned int i = 0; i != m; i++)
    {
        p = p * n;
    }

    return p;
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
