#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct funcs{
int (*openit)(char *name, int prot);
void (*closeit)(void);

} funcs;

int  my_openit(char *name, int prot);
void  my_closeit(void);
int  my_openit(char *name, int prot){
printf("proof open is here\n");
return 0;
}
void  my_closeit(void){
 printf("proof close is here\n");
}

funcs f(funcs* func_pntr){
	(*func_pntr).openit = my_openit;
	(*func_pntr).closeit = my_closeit;
	return *func_pntr;
}

int main(int argc, char *argv[]){
	static funcs myFunctions = {.openit = my_openit, .closeit =  my_closeit};
        printf("testing myFunctions\n");
	myFunctions.openit("hello", 1);
	myFunctions.closeit();
	static funcs someFunctions;
	f(&someFunctions);
	printf("\ntesting someFunctions\n");
	someFunctions.openit("Kendrick\n", 1);
	someFunctions.closeit();
	return 0;
}
