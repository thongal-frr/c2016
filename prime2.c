#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
/*
 * A number which is only divisible by 1 or itself is a a prime number.
 * e.g 2, 3,5, 7, 11 13 17
 * 2 is the only even and smallest prime number
 */

void printPrime(int in) {
  bool prime;
  if (in <= 1) {
    return;
  }
  for(int n = 0; n <= in; n++) {
    prime = true;
    for(int i = 2; i < n-1; i++){
      if (n%i == 0) {
	prime = false;
	break;
      }
    }
    if(prime) {
      prime = false;
      printf("%d ", n);
    }
  }
}

int main(int argc, char *argv[]) {
  int num=0;
  printf("Enter a number\n");
  scanf("%5d", &num);
  printf("Prime number in range 1 to %d:",num);
  printPrime(num);
}
