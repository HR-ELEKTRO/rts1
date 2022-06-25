#include <stdio.h>

unsigned int power(unsigned int n, unsigned int m);

// This function must be implemented in LEGv7 Pinky assembly
unsigned int power(unsigned int n, unsigned int m)
{
    if (m == 0) return 1;

    unsigned int p = 1;

    while (m != 1)
    {
        if ((m & 1) == 1) /* m is odd */
        {
            p = p * n;
        }
        n = n * n;
        m = m >> 1;
    }

    return p * n;
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
