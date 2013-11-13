#include <stdio.h>

int isPrime(int n) {
	int a;
	if (n > 2) {
		for(a = 2; a*a <= n; a++) {
			if (n % a == 0) {
				return 0;
			}
		}
		return 1;
	}
	return 0;
}	

int main(int argc, char const *argv[])
{
	int i;
	int pr = 1;
	for (i = 1; i <=100; i++) {
		if (isPrime(i)){
			printf("Prime Number %d = %d\n", pr, i);
			pr++;
		}
	}
	return 0;
}