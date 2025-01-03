// this expands the simple C skeleton to illustrate how strings are used in C. Importantly, 
// C strings are simply arrays of characters, with the string terminated with a binary 0 character

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
  char buf[512]; // a string that can hold a minimum of 511
		 // characters + the terminating NULL
  buf[0] = 0;    // string is now empty 
  
  strcat(buf, "Hi "); // string is now "Hi "
  strcat(buf, "there."); // string is now "Hi there."
  
  // output length of string
  printf("The string is %lu characters in lenght. \n", strlen(buf));

  char *location;

  // return pointer to first 't' or NULL if not found
  location = strchr(buf, 't');

  if (location){
    printf("Found: %s\n", location);
  }
  else {
  printf("'t' not found.\n");
  }
  // return pinter to first "there" or NULL
  location = strstr(buf, "there");

  if(location){
    printf("Found: %s\n", location); 
  }
  else {
  printf("\"there\" not found.\n");
  }

  //strcmp returns < 0, 0, or > 0 to indicate
  // s1 < s2, s1 == s2, s1 > s2
  int cmp = strcmp("Hi there.", buf);

  if (cmp < 0){
  printf("\"Hi there.\" < buf \n");
  }

  else if (! cmp){
  printf("\"Hi there.\" = buf \n");
  }
  else{
  printf("\"Hi there.\" > buf \n");
  }

  // parse a comma-delimeted string into sepreate compenents and output them
  char *token, *string, *tofree;

  // duplicate literal string
  tofree = string = strdup("milk,bread,cheese,coffee");

  while ((token = strsep(&string, ",")) != NULL) {
  printf("%s\n", token);
  }

  // must be called to release memerory associated with strdup() call
  free(tofree);
  return 0;
}
