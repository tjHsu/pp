#include <stdlib.h>
#include <stdio.h>


int main(int argc, char* argv[]) {
	printf("argc = %d\n", argc);

	int i;
	for (i = 0 ; i < argc ; ++i) {
		printf("argv[%d] is: %s\n", i, argv[i]);
		printf("argv[%d] is a integer: %d\n", i, atoi(argv[i]));
	}
}