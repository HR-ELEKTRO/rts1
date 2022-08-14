#include <stdio.h>

unsigned int dotProduct(unsigned int a[], unsigned int b[], size_t n);

// This function must be implemented in LEGv7 Pinky assembly
unsigned int dotProduct(unsigned int a[], unsigned int b[], size_t n)
{
    unsigned int p = 0;
    for (size_t i = 0; i != n; i++)
    {
        p = p + a[i] * b[i];
    }
    return p;
}

int main()
{
    extern void initialise_monitor_handles(void);
    initialise_monitor_handles();

    unsigned int a[] = { 1,  2,  3,  4,  5};
    unsigned int b[] = {10, 11, 12, 13, 14};

    if (dotProduct(a, b, 5) == 190)
    {
        printf("OK\n");
    }
    else
    {
        printf("Error\n");
    }
    return 0;
}
