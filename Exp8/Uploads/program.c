/**
 * Implementation of Pass 1 of Two Pass Assmbler
 * Author: Kowsik Nandagopan D
*/

// Header files
#include <stdio.h>
#include <stdlib.h> // atoi, exit
#include <string.h> // string functions

void main(){
    // Initialize variables
    FILE *codef, *opf, *symf;
    char label[20], opcode[20], operand[20];
    char opcode_tab[20]; 
    int op_hex, len;
    int loc_counter=-1, start_addr=0;

    if((codef = fopen("input.txt", "r")) == NULL){ // loading the source code
        printf("Error! opening file");
        exit(1);
    }

    if((opf = fopen("optab.txt", "r")) == NULL){ // loading the contents of OPTAB
        printf("Error! opening file");
        exit(1);
    }

    if((symf = fopen("symtab.txt", "w")) == NULL){ // loading the contents of OPTAB
        printf("Error! opening file");
        exit(1);
    }

    while (!feof(codef)){
        fscanf(codef, "%s\t%s\t%s\n", label, opcode, operand); // reading line by line from the source code
        if (strcmp(opcode, "START") == 0 && loc_counter == -1) {
            // Runs only when START is not defined
            loc_counter = atoi(operand); // converting string to integer
            start_addr = loc_counter; // For getting length of program
            printf("%s\t%s\t%s\n", label, opcode, operand); // Output to the console
            continue; // Go to next line
        } else {
            while (!feof(opf)) { // looping in the OPTAB
                fscanf(opf, "%s\t%d\n", opcode_tab, &op_hex); // Reading the details from OPTAB
                if (strcmp(opcode_tab, opcode) == 0){
                    printf("%d\t%s\t%s\t%s\n", loc_counter, label, opcode, operand); // Output to console
                    loc_counter += 3; // Adding word length
                    break;
                } 
            }
            rewind(opf);

            // ===================== For variable section ==============
            if (strcmp(opcode, "WORD") == 0) { // If WORD
                printf("%d\t%s\t%s\t%s\n", loc_counter, label, opcode, operand); // Output to console
                fprintf(symf, "%s\t%d\n", label, loc_counter); // Output to symtab file
                loc_counter += 3;
            } else if (strcmp(opcode, "RESW") == 0) { // If RESW
                printf("%d\t%s\t%s\t%s\n", loc_counter, label, opcode, operand); // Output to console
                fprintf(symf, "%s\t%d\n", label, loc_counter); // Output to symtab file
                loc_counter += 3*atoi(operand);
            } else if (strcmp(opcode, "BYTE") == 0) { // If BYTE
                printf("%d\t%s\t%s\t%s\n", loc_counter, label, opcode, operand); // Output to console
                fprintf(symf, "%s\t%d\n", label, loc_counter); // Output to symtab file
                if(operand[0] == 'X')
                    loc_counter += 1;
                else {                 
                    loc_counter += strlen(operand) - 3; // 3 denotes to remove C, ', " etc...
                }
            } else if (strcmp(opcode, "RESB") == 0) { // If RESB
                printf("%d\t%s\t%s\t%s\n", loc_counter, label, opcode, operand); // Output to console
                fprintf(symf, "%s\t%d\n", label, loc_counter); // Output to symtab file
                loc_counter += atoi(operand);
            } else if (strcmp(opcode, "END") == 0) { // At END
                printf("%d\t%s\t%s\t%s\n", loc_counter, label, opcode, operand); // Output to console
            }
        }

    }

    // Print the length
    printf("Program length = %d\n", loc_counter - start_addr); // Output to console

    // Closing the files
    fclose(codef);
    fclose(opf);
    fclose(symf);

}