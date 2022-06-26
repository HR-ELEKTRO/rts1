#include <stdio.h>

void insertionSort(int a[], size_t n);

void swap(int *p1, int *p2)
{
    int t = *p1;
    *p1 = *p2;
    *p2 = t;
}

// This function must be implemented in LEGv7 Pinky assembly
void insertionSort(int a[], size_t n)
{
    for (size_t i = 0; i != n; i++)
    {
        for (size_t j = i; j != 0 && a[j-1] > a[j]; j--)
        {
            swap(&a[j], &a[j-1]);
        }
    }
}

int main(void)
{
    extern void initialise_monitor_handles(void);
    initialise_monitor_handles();

    int a[] = {1, -2, 7, -4, 5};
    int b[] = {-4, -2, 1, 5, 7};

    insertionSort(a, sizeof(a)/sizeof(a[0]));
    for (size_t i = 0; i != sizeof(a)/sizeof(a[0]); i++)
    {
        if (a[i] != b[i])
        {
            printf("Error\n");
            return 1;
        }
    }
    printf("OK\n");
    return 0;
}
