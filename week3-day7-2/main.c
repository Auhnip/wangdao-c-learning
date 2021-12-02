#include <stdio.h>

int main(void)
{
	int count = 0;
	int sum;
	int money_count;

	for (int money10 = 1; money10 < 10; ++money10)
		for (int money5 = 1; money5 < 20; ++money5)
			for (int money2 = 1; money2 < 40; ++money2)
				for (int money1 = 1; money1 < 40; ++money1)
				{
					money_count = money10 + money5 + money2 + money1;
					sum = 10 * money10 + 5 * money5 + 2 * money2 + money1;

					if (money_count == 40 && sum == 100)
						++count;
				}
				
	printf("%d\n", count);
	return 0;
}