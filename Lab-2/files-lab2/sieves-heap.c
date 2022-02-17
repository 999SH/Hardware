
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define COLUMNS 6


int cc = 0; // cc = column counter

void print_number(int number){
  printf("%5d ", number);
  cc++;
  if(cc%COLUMNS == 0){
    printf("\n");
  }
}
//so we initialize an array that is the size of the input -1 since indexing from 0
//we need a boolean array that states if a value is a prime or not, since boolean is not a datatype in C we will use 1 and 0 instead
void print_sieves(int input){  	 
	char *primes = malloc (sizeof (char)* input-1); //Allocate memory for the array

	for (int t = 0;  t <= input-1; t++){
		primes[t]= 1;
	}

	for(int i = 2; i <= (int) sqrt(input); i++){
 	     if(primes[i] == 1){                             // This is to check if we already covered a number
		     for(int j = i*i; j < input; j+=i){     // For every multiple of that number
     		    		 primes[j] = 0;              // Mark it as non-prime
        		}
     	     	}
	}
	for(int i = 2; i <= input-1; i++){
      		if(primes[i] == 1){
        	print_number(i);
      		}
    	}
	free(primes);
}

// 'argv' is an array of char pointers, where each
// char pointer points to a null-terminated string.
int main(int argc, char *argv[]){
  if(argc == 2)
    print_sieves(atoi(argv[1]));
  else
    printf("Please state an interger number.\n");
}
