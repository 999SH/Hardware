/*
 prime.c
 By David Broman.
 Last modified: 2015-09-15
 This file is in the public domain.
*/


#include <stdio.h>

int is_prime(int n){
  int c; // Counter

  for(c=2; c<=n-1; c++){ // check if n is divisble by any integer 
      if(n%c==0){        // less than itself, if it is then it is
        return 0;        // not a prime and should return 0
      }
  }
  if (c==n){
    return 1;
  }
}

int main(void){
  printf("%d\n", is_prime(11));  // 11 is a prime.      Should print 1.
  printf("%d\n", is_prime(383)); // 383 is a prime.     Should print 1.
  printf("%d\n", is_prime(987)); // 987 is not a prime. Should print 0.
  printf("%d\n", is_prime(7));   // 7 is a prime.       Should print 1.
}
