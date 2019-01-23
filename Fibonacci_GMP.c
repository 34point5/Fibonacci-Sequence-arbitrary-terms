#include<gmp.h>
#include<stdio.h>
#include<stdlib.h>

int main(int argc, char **argv)
{
	// check the arguments
	if(argc != 3)
	{
		printf("usage:\n");
		printf("\t./Fibonacci.out <number of terms> <output file>\n");
		return 1;
	}

	// read input argument
	mpz_t last;
	mpz_init(last);
	if(mpz_set_str(last, argv[1], 10))
	{
		printf("%s is not a valid input.\n", argv[1]);
		return 2;
	}

	// check if it is allowed
	if(mpz_cmp_si(last, 2) <= 0)
	{
		printf("Enter a number greater than 2.\n");
		return 3;
	}

	// open file to write output to
	FILE *list;
	list = fopen(argv[2], "w");
	if(list == NULL)
	{
		printf("Failed to open the file %s for writing.\n", argv[2]);
		return 4;
	}

	// initialize first term
	mpz_t small;
	mpz_init(small);
	mpz_set_ui(small, 0);

	// initialize second term
	mpz_t large;
	mpz_init(large);
	mpz_set_ui(large, 1);

	// variable to store the sum
	mpz_t sum;
	mpz_init(sum);

	// counter variable, also arbitrary precision
	mpz_t count;
	mpz_init(count);

	// loop to calculate
	fprintf(list, "0\n");
	fprintf(list, "1\n");
	for(mpz_set_ui(count, 2); mpz_cmp(last, count) > 0; mpz_add_ui(count, count, 1))
	{
		mpz_add(sum, small, large);
		mpz_set(small, large);
		mpz_set(large, sum);
		mpz_out_str(list, 10, sum);
		fputc('\n', list);
	}

	// release multiple-precision numbers
	mpz_clear(small);
	mpz_clear(large);
	mpz_clear(count);
	mpz_clear(sum);

	// close file
	fclose(list);

	return 0;
}
