#include <stdio.h>

void bubbleSortOpt(int a[], size_t n);

void swap(int *p1, int *p2)
{
    int t = *p1;
    *p1 = *p2;
    *p2 = t;
}

// This function must be implemented in LEGv7 Pinlky assembly
void bubbleSortOpt(int a[], size_t n)
{
    size_t newn;
    do
    {
        newn = 0;
        for (size_t i = 1; i != n; i++)
        {
            if (a[i-1] > a[i])
            {
                swap(&a[i-1], &a[i]);
                newn = i;
            }
        }
        n = newn;
    }
    while (n != 0);
}

int main()
{
	extern void initialise_monitor_handles(void);
	initialise_monitor_handles();

    int a[] = {1, -2, 7, -4, 5};
    int b[] = {-4, -2, 1, 5, 7};

    bubbleSortOpt(a, sizeof(a)/sizeof(a[0]));
    for (size_t i = 0; i != sizeof(a)/sizeof(a[0]); i++)
    {
        if (a[i] != b[i])
        {
            printf("Error\n");
            return 0;
        }
    }
    printf("OK\n");
    return 0;
}

