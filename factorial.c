#include <stdio.h>

int fact(int val) {
	if(val == 0 || val == 1)
			return (1);
	return  val * fact ( val-1 );
}

int main(int argc, char *argv[]) {
	int val = 5;
	printf("Factorial of %d using recursion is %d",val, fact(val));
}