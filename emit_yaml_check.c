#include <stdio.h>
#include <stdlib.h>

// --- Step 3: Include the C header file generated in the previous step ---
#include "instruction.h"

/*
 * This program reads the compiled-in instruction data and writes it
 * out to a new YAML file.
 */
int main() {
    // Define the output filename
    const char* output_filename = "final.yaml";
    FILE *file;

    // Open the file for writing
    file = fopen(output_filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    printf("Generating YAML file: %s\n", output_filename);

    // --- Step 4: Emit the contents of the C header file in YAML format ---
    // We write the data from the 'instruction_data' struct into the file.
    // The format is a simple key-value structure.

    fprintf(file, "name: \"%s\"\n", instruction_data.name);
    fprintf(file, "long_name: \"%s\"\n", instruction_data.long_name);
    fprintf(file, "assembly: \"%s\"\n", instruction_data.assembly);

    // For the description, we use the YAML literal block scalar style `|`
    // to preserve newlines, making it clean.
    fprintf(file, "description: |\n");
    fprintf(file, "  %s\n", instruction_data.description);

    fprintf(file, "funct7: \"%s\"\n", instruction_data.funct7);
    fprintf(file, "funct3: \"%s\"\n", instruction_data.funct3);
    fprintf(file, "opcode: \"%s\"\n", instruction_data.opcode);

    // Close the file
    fclose(file);

    printf("Successfully wrote data to %s\n", output_filename);

    return 0;
}