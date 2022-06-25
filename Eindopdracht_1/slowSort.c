#include <stdio.h>

void slowSort(int a[], size_t first, size_t last);

void swap(int *p1, int *p2)
{
    int t = *p1;
    *p1 = *p2;
    *p2 = t;
}

// This function must be implemented in LEGv7 Pinky assembly
void slowSort(int a[], size_t first, size_t last)
{
    if (first != last)
    {
        size_t middle = (first + last) >> 1;
        slowSort(a, first, middle);
        slowSort(a, middle + 1, last);
        if (a[last] < a[middle])
        {
            swap(&a[last], &a[middle]);
        }
        slowSort(a, first, last - 1);
    }
}

int main()
{
	extern void initialise_monitor_handles(void);
	initialise_monitor_handles();

    int a[] = {1, -2, 7, -4, 5};
    int b[] = {-4, -2, 1, 5, 7};

    slowSort(a, 0, sizeof(a)/sizeof(a[0]) - 1);
    for (size_t i = 0; i < sizeof(a)/sizeof(a[0]); i++)
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
