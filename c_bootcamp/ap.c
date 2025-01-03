// Illustrates arrays and pointers and their general eqivalence in C.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(int argc, char *argv[]){
  
  int nums[50]; //think of nums as a constant pointer that is assoaciated
		//with storage for 50 integers (it's also an array :)
  int i;
  int *arr=nums; // arr is initially associated with no storage, but with the initialization                  //, shares the 50 integers for nums
  srandom(time(NULL));
  i = 0;
  do {
   *arr = random();  // assign a random number
    printf("Random number from two different angles is %d and %d.\n", *arr,nums[i]);
    i++;   // increments by *one*
    arr++; // increments by sizeof(int) [the type of the array]
    printf("Value of i %d, value of arr is %lu\n", i, (unsigned long)arr);
  } while (i < 50);
  return 0;
}
