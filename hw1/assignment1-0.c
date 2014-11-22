#include <stdio.h>
#include <string.h>

void square_fraction(int, int, int *, int *);
void square_fraction_inplace(int *, int *, int *, int *);

void main() {
	typedef struct fraction {
		int numerator;
		int denominator;
	} frac; 
	
	frac test;
	test.numerator = 2;
	test.denominator = 5;
	int sn;
	int sd;
	frac test2;
	test2.numerator = 3;
	test2.denominator = 7;
	
	/*
	printf ("%d\n", test.numerator);
	printf ("%d\n", test.denominator);
	*/
	square_fraction(test.numerator, test.denominator, &sn, &sd);
	printf ("sn = %d\n", sn);
	printf ("sd = %d\n", sd);
	square_fraction_inplace(&test2.numerator, &test2.denominator, &sn, &sd);
	printf ("sn = %d\n", sn);
	printf ("sd = %d\n", sd);
	
}

void square_fraction(int numerator, int denominator, int *square_nume, int *square_deno) {
	*square_nume = numerator*numerator;
	*square_deno = denominator*denominator;
}	
		
void square_fraction_inplace(int *numerator, int *denominator, int *square_nume, int *square_deno) {
	*square_nume = *numerator * *numerator;
	*square_deno = *denominator * *denominator;
	*numerator = *square_nume;
	*denominator = *square_deno;

}	

