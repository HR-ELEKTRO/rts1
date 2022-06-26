#include <stdio.h>

unsigned int sqrtFloor(unsigned int n);

// This function must be implemented in LEGv7 Pinky assembly
unsigned int sqrtFloor(unsigned int n)
{
    unsigned int p = 1u << 15;
    unsigned int r = 0;

    do
    {
        r = p | r;
        if (r * r > n)
        {
            r = r & ~p;
        }
        p = p >> 1;
    }
    while (p != 0);

    return r;
}

int main()
{
    extern void initialise_monitor_handles(void);
    initialise_monitor_handles();

    unsigned int a[] = {0, 1, 2, 3, 4, 152399025, 152423715, 4294836225, 4294967295};
    unsigned int r[] = {0, 1, 1, 1, 2,     12345,     12345,      65535,      65535};

    for (size_t i = 0; i < sizeof(a)/sizeof(a[0]); i++)
    {
        printf("sqrtFloor(%u): ", a[i]);
        unsigned int result = sqrtFloor(a[i]);
        unsigned int correct = r[i];
        if (result != correct)
        {
            printf("Failed, function returned %u but the correct answer is %u\n", result, correct);
        }
        else
        {
            printf("Passed, %u\n", result);
        }
    }
    return 0;
}
