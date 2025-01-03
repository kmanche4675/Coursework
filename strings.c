#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main (int argc, char * argv[]){
    char buf[512];     	// a string that can hold a maximiumu of 511
			  	// characters + the terminating NULL
    char buf[0] = 0;   	// string is now empty

    strcat(buf , "Hi"); 	// string is now "Hi"
    strcat(buf , "there.");      // strign is now "Hi there."
				//
    // output length of string
    printf("The string is %lu characters in length.\n", strlen(buf));

    char *location;

    location = strchr(buf, 't'); //returns pointer to first 't' or NULL if not found
   
    if(location) {
    printf("Found: %s\n", location);
    } 
    else {
    printf("'t' not found.\n");
    }

   location = strstr(buf, "there"); // returns pointer to first "there or NULL"
   
   if(location){
   printf("Found: %s\n", location);
   }
   else{
   printf("\"there\" not found. \n");
   }
	
   int cmp = strcmp("Hi there.", buf); //strcamp returns < 0, 0, or > 0 to indicate 
				       //s1 < s2, s1 == s2, s1 > s2
   if(cmp < 0){
   printf("\"Hi there.\" < buf\n");
   }

   else if (! cmp){
   printf("\"Hi there.\" = buf \n");
   }
   
   else {
   printf("\" Hi there.\" > buf\n");
   }

   char *token, *string, *tofree; 
   tofree = string = strdup("milk,bread,cheese,coffee");// duplicate literal string 
   
   while ((token = strsep(&string, ",")) != NULL) {
   printf("%s\n", token);
   }

   // must be called to release memory assciated with strdup() call free(tofree);
   //There are LOTS more string functions! See, e.g.:
   //https://www.tutorialspoint.com/c_standard_linrary/string_h.htm
   return 0;

}
