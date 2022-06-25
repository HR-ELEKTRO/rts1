#include <stdio.h>

unsigned int multiply(unsigned int a, unsigned int b);

/**
 * Multiplies two unsigned int values
 * @param unsigned int a
	The value of the multiplier a (0-4294967295)
 * @param unsigned int b
	The value of the multiplicand b (0-4294967295)
 * @return unsigned int
	The answer of a times b given that a * b < 4294967295
 */

// This function must be implemented in LEGv7 Pinky assembly
unsigned int multiply(unsigned int a, unsigned int b)
{
	unsigned int m = 0;

	while (b != 0)
	{
		if ((b & 1) == 1) /* b is odd */
        {
			m = m + a;
		}
		a = a << 1;
		b = b >> 1;
	}

	return m;
}

int main()
{
	extern void initialise_monitor_handles(void);
	initialise_monitor_handles();

	unsigned int a[] = {0, 1, 0, 1, 2000,      2,     10000,          1 ,      65535 };
    unsigned int b[] = {0, 0, 1, 1,    2,  65535,     65535, 4294967295u,      65535 };
    unsigned int r[] = {0, 0, 0, 1, 4000, 131070, 655350000, 4294967295u, 4294836225u};

    for (size_t i = 0; i != sizeof(a)/sizeof(a[0]); i++)
    {
    	printf("%u x %u: ", a[i], b[i]);
    	unsigned int result = multiply(a[i], b[i]);
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
