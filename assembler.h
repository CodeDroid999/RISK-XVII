#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 100

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Error: no input file specified.\n");
        return 1;
    }

    FILE* input_file = fopen(argv[1], "r");
    if (input_file == NULL) {
        printf("Error: could not open input file.\n");
        return 1;
    }

    int reg_size = 32; // Number of registers
    int* register_bank = malloc(reg_size * sizeof(int)); // Allocate memory for registers

    // Initialize registers to zero
    for (int i = 0; i < reg_size; i++) {
        register_bank[i] = 0;
    }

    char line[MAX_LINE_LENGTH];
    while (fgets(line, MAX_LINE_LENGTH, input_file) != NULL) {
        // Parse the assembly instruction and generate machine code
        char* opcode = strtok(line, " "); // Get the opcode
        if (strcmp(opcode, "add") == 0) {
            char* rd = strtok(NULL, ", "); // Get the destination register
            char* rs = strtok(NULL, ", "); // Get the first source register
            char* rt = strtok(NULL, "\n"); // Get the second source register

            int rd_val = atoi(rd + 1); // Convert rd to integer
            int rs_val = atoi(rs + 1); // Convert rs to integer
            int rt_val = atoi(rt + 1); // Convert rt to integer

            // Generate machine code
            int machine_code = (0 << 26) | (rs_val << 21) | (rt_val << 16) | (rd_val << 11) | (0 << 6) | 0b100000;

            // Store the machine code in the destination register
            register_bank[rd_val] = machine_code;
        }
        // Handle other opcodes here
    }

    // Free memory
    free(register_bank);
    fclose(input_file);
    return 0;
}
