/**
 * Implementation of Pass 2 of Two Pass Assmbler
 * Author: Kowsik Nandagopan D
*/

// Header files
#include <stdio.h>
#include <stdlib.h> // atoi, exit
#include <string.h> // string functions

void main(){
    // Initialize variables
    FILE *inter, *opf, *symf, *obj, *flen;
    char address[20], label[20], opcode[20], operand[20], len_str[10], start_addr[20];
    char opcode_tab[20], op_hex[20]; 
    int len;
    int loc_counter=-1;

    if((inter = fopen("inter.txt", "r")) == NULL){ // loading the source code (intermediate file of pass 1)
        printf("Error! opening file");
        exit(1);
    }

    if((opf = fopen("optab.txt", "r")) == NULL){ // loading the contents of OPTAB
        printf("Error! opening file");
        exit(1);
    }

    if((symf = fopen("symtab.txt", "r")) == NULL){ // loading the contents of SYMTAB
        printf("Error! opening file");
        exit(1);
    }

    if((flen = fopen("flen.txt", "r")) == NULL){ // loading the contents of Program Length
        printf("Error! opening file");
        exit(1);
    }

    if((obj = fopen("object.txt", "w")) == NULL){ // loading the contents of Intermediate File
        printf("Error! opening file");
        exit(1);
    }
    fscanf(inter, "%s\t%s\t%s\t%s", address, label, opcode, operand);
    // Correcting the Program Name Spacing
    for (int i=strlen(label); i<6; i++){
        strcat(label, " ");
    }
    // Correcting the start address bit size
    char temp[10];
    for (int i=strlen(operand); i<6; i++){
        strcat(temp, "0");
    }
    strcat(temp, operand);
    strcpy(operand, temp);
    strcpy(start_addr, temp); // Setting the starting address
    temp[0] = '\0'; // Re-initialize

    // Reading the length of program from flen file
    fscanf(flen, "%d", &len);

    // =============== Writing to the object file ====================
    // Header Record
    if (strcmp("START", opcode) == 0){
        fprintf(obj, "H^%s^%s^0000%d\nT^%s^", label, operand, len, start_addr);
    }

    // Text Record
    do {
        int flag = 0; // If opcode is in OPTAB
        fscanf(inter, "%s\t%s\t%s\t%s", address, label, opcode, operand);
        // OPTAB
        while (!feof(opf)){
            fscanf(opf, "%s\t%s", opcode_tab, op_hex);
            // printf("%s\t%s\n", opcode_tab, op_hex);
            if (strcmp(opcode_tab, opcode) == 0){
                fprintf(obj, "%s", op_hex);
                flag = 1;
                while (!feof(symf)){
                    fscanf(symf, "%s\t%s", op_hex, opcode);
                    // printf("%s\t%s^\n", op_hex, opcode);
                    if (strcmp(operand, opcode) == 0){
                        fprintf(obj, "%s^", op_hex);
                        break;
                    }
                }
                rewind(symf);
                break;
            }
        }
        rewind(opf);
        // If Assembler Directive
        if (flag == 0) {
            if ((strcmp(opcode, "BYTE") == 0) || (strcmp(opcode, "WORD") == 0)){ // If Byte or Word
                if (strcmp(opcode, "WORD") == 0) // WORD
                    fprintf(obj, "0000%s^", operand); // Write the operand as such
                else { // If BYTE write the operand as the ASCII
                    len = strlen(operand); 
                    for (int i = 2; i < len; i++){
                        fprintf(obj, "%d", operand[i]); // Writing the ASCII code to the file
                    }
                    fprintf(obj, "^"); // End of the object code
                }
            }
        }
    } while (strcmp("END", opcode) != 0); // Loop in the intermediate file untilo the END of file
    
    // Printing the END record
    fprintf(obj, "\nE^%s", start_addr);

    // Closing the files
    fclose(inter);
    fclose(opf);
    fclose(symf);
    fclose(obj);
    fclose(flen);

}