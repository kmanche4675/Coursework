#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    // Ensure a Single Commnad Line Argument is Provide
	if(argc != 2){
	fprintf(stderr, "usage: %s <filename>\n", argv[0]);
	return 1;
	}

	FILE *file = fopen(argv[1], "r");
	if (file == NULL){
	fprintf(stderr, "Error : Could not open file %s\n", argv[1]);
	return 1;
	}

	fseek(file, 0, SEEK_END);
	long file_size = ftell(file);
	rewind(file);
	char *content =(char *)malloc((file_size+1)*sizeof(char));
	if (content==NULL){
	fprintf(stderr, "Error: Memory allocation fialed\n");
	fclose(file);
	return 1;
	}

	size_t read_size=fread(content, sizeof (char), file_size, file);
	if(read_size!=file_size){
	printf("Error: failed to reaf file content \n");
	free(content);
	fclose(file);
	return 1;
	}
	fclose(file);
	content[file_size]= '\0';
        char *token=strtok(content, "\t\n,");
	while (token != NULL){
	printf("%s\n", token);
        token = strtok(NULL, "\t\n,");
	}
	free(content);
	return 0;
}
