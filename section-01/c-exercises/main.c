#include <stdio.h>
#include <stdlib.h>

void FizzBuzz (int n) {    //exercise 2
	if (n % 3 == 0) {
		printf("Fizz");
	}
	if (n % 5 == 0) {
		printf("Buzz");
	}
}

int comp (const void *a, const void *b) { //exercise 3
	return (*(int *)b - *(int *)a);
}

int main () {
	int *a1 = malloc (20*sizeof(int)); //exercise 2

	for (int i = 0; i < 20; i++) {
		*(a1 + i) = i + 1;
	}

	printf ("FizzBuzz on the array\n");
	for (int j = 0; j < 20; j++) {
		printf("%2d: ", a1[j]);
		FizzBuzz(a1[j]);
		printf("\n");
	}

	printf ("\nFizzBuzz plugging in 1 -> 30\n");
	for (int k = 1; k <= 30; k++) {
		printf("%2d: ", k);
		FizzBuzz(k);
		printf("\n");
	}

	qsort (a1, 20, sizeof(a1[0]), comp);   //exercise 3

	printf ("Printing the sorted array:\n");
	for (int q = 0; q < 20; q++) {
		printf("%d ", a1[q]);
	}
	printf ("\n");

	printf ("Hello World!\n"); //exercise 1
	free (a1);
	return 0;
}