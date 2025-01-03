#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file;
    char data[] = "Hello, ZFS!";
    char buffer[50];

    // Create and open a file for writing
    file = fopen("example.txt", "w");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    // Write data to the file
    if (fwrite(data, sizeof(char), sizeof(data), file) != sizeof(data)) {
        perror("Error writing to file");
        fclose(file);
        return EXIT_FAILURE;
    }

    // Close the file
    fclose(file);

    // Open the file for reading
    file = fopen("example.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    // Read data from the file
    if (fread(buffer, sizeof(char), sizeof(data), file) != sizeof(data)) {
        perror("Error reading from file");
        fclose(file);
        return EXIT_FAILURE;
    }

    // Print the data read from the file
    printf("Data read from file: %s\n", buffer);

    // Close the file
    fclose(file);

    return EXIT_SUCCESS;
}
