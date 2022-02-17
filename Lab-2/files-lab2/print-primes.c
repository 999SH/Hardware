/*
 print-prime.c
 By David Broman.
 Last modified: 2015-09-15
 This file is in the public domain.
*/


#include <stdio.h>
#include <stdlib.h>

#define COLUMNS 6


int is_prime(int input){
  int divisor; // divisor
  for(divisor=2; divisor<=input-1; divisor++){    // 
      if(input%divisor==0){                      //
      	return 0; 	                          //	   
      }
  }
  if (divisor==input){                            //if the number is a prime then return 1
    return 1;
  }
}

int cc = 0; // cc = column counter

void print_number(int number){
  printf("%5d ", number);
  cc++;
  if(cc%COLUMNS == 0){
    printf("\n");
  }
}

void print_primes(int input){
  // Should print out all prime numbers less than 'n'
  // with the following formatting. Note that
  // the number of columns is stated in the define
  // COLUMNS
  int prime;
  for (prime = 2; prime < input; prime ++){ //if the number is a prime , it will be printed 
	  if(is_prime(prime) == 1){          //it will print any prime number less than the chosen one
	  print_number(prime);
	  } 
  }
}

// 'argc' contains the number of program arguments, and
// 'argv' is an array of char pointers, where each
// char pointer points to a null-terminated string.
int main(int argc, char *argv[]){
  if(argc == 2)
    print_primes(atoi(argv[1]));
  else
    printf("Please state an interger number.\n");
  return 0;
}

 
