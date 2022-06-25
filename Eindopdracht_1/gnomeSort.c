#include <stdio.h>

void gnomeSort(int a[], size_t n);

void swap(int *p1, int *p2)
{
    int t = *p1;
    *p1 = *p2;
    *p2 = t;
}

// This function must be implemented in LEGv7 Pinky assembly
void gnomeSort(int a[], size_t n)
{
    size_t i = 0;
    while (i != n)
    {
        if (i == 0 || a[i] >= a[i-1])
        {
            i++;
        }
        else
        {
            swap(&a[i], &a[i-1]);
            i--;
        }
    }
}

int main()
{
	extern void initialise_monitor_handles(void);
	initialise_monitor_handles();

    int a[] = {1, -2, 7, -4, 5};
    int b[] = {-4, -2, 1, 5, 7};

    gnomeSort(a, sizeof(a)/sizeof(a[0]));
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
