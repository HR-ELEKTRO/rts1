#include <stdio.h>

void stoogeSort(int a[], size_t first, size_t last);

void swap(int *p1, int *p2)
{
    int t = *p1;
    *p1 = *p2;
    *p2 = t;
}

// This function must be implemented in LEGv7 Pinky assembly
void stoogeSort(int a[], size_t first, size_t last)
{
    if (a[first] > a[last])
    {
        swap(&a[first], &a[last]);
    }
    if ((last - first + 1) > 2)
    {
        size_t third = (last - first + 1) / 3;
        stoogeSort(a, first, last - third);
        stoogeSort(a, first + third, last);
        stoogeSort(a, first, last - third);
    }
}

int main()
{
	extern void initialise_monitor_handles(void);
	initialise_monitor_handles();

    int a[] = {1, -2, 7, -4, 5};
    int b[] = {-4, -2, 1, 5, 7};

    stoogeSort(a, 0, sizeof(a)/sizeof(a[0]) - 1);
    size_t i;
    for (i = 0; i < sizeof(a)/sizeof(a[0]); i++)
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
