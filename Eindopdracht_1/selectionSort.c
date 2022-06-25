#include <stdio.h>

void selectionSort(int a[], size_t n);

void swap(int *p1, int *p2)
{
    int t = *p1;
    *p1 = *p2;
    *p2 = t;
}

// This function must be implemented in LEGv7 Pinky assembly
void selectionSort(int a[], size_t n)
{
	for (size_t j = 0; j != n - 1; j++)
	{
		size_t iMin = j;
        for (size_t i = j + 1; i != n; i++)
        {
            if (a[i] < a[iMin])
            {
                iMin = i;
            }
        }
        if (iMin != j)
        {
            swap(&a[j], &a[iMin]);
        }
	}
}

int main()
{
	extern void initialise_monitor_handles(void);
	initialise_monitor_handles();

	int a[] = {1, -2, 7, -4, 5};
    int b[] = {-4, -2, 1, 5, 7};

    selectionSort(a, sizeof(a)/sizeof(a[0]));
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
