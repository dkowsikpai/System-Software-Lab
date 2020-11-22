/**
 * Implementation of One Pass Assmbler
 * Author: Kowsik Nandagopan D
*/

// Librabries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Main
int main() {
    FILE *inpf, *optf, *symf, *outf, *resf; // File pointers
    // Initialization
    int lc, sa, i = 0, j = 0, m[10], pgmlen, len, k, len1, l = 0;
    char name[10], opnd[10], la[10], mne[10], s1[10], mne1[10], opnd1[10];
    char lcs[10], ms[10];
    char sym[10], symaddr[10], obj1[10], obj2[10], s2[10], q[10], s3[10];

    // Reading files
    inpf = fopen("input.txt", "r");
    optf = fopen("optab.txt", "r");
    symf = fopen("symtab.txt", "a+");
    outf = fopen("output.txt", "w+");
    resf = fopen("result.txt", "w+");
    fscanf(inpf, "%s%s%s", la, mne, opnd);
    // Init the LOCCTR when START is encountered
    if (strcmp(mne, "START") == 0) {
        sa = atoi(opnd);
        strcpy(name, la);
        lc = sa;
    }
    strcpy(s1, "*"); // If Symbol not defined
    fscanf(inpf, "%s%s%s", la, mne, opnd);
    while (strcmp(mne, "END") != 0) { // Until END is encountered
        if (strcmp(la, "-") == 0) { // If Instruction
            fscanf(optf, "%s%s", mne1, opnd1); // Reading OPTAB
            while (!feof(optf)) {
                if (strcmp(mne1, mne) == 0) {
                    m[i] = lc + 1; // Location where modification required
                    fprintf(symf, "%s\t%s\n", opnd, s1);
                    fprintf(outf, "%s\t0000\n", opnd1);
                    lc = lc + 3; // Increment Location. 3 Byte Instruction
                    i = i + 1;
                    break;
                }
                else
                    fscanf(optf, "%s%s", mne1, opnd1);
            }
        } else {
            fseek(symf, SEEK_SET, 0);
            fscanf(symf, "%s%s", sym, symaddr); //Adding to SYMTAB
            while (!feof(symf)) { // Scan SYMTAB and set address for not defined ones earilier
                if (strcmp(sym, la) == 0) {
                    sprintf(lcs, "%d", lc);
                    fprintf(symf, "%s\t%s\n", la, lcs);
                    sprintf(ms, "%d", m[j]);
                    j = j + 1;
                    fprintf(outf, "%s\t%s\n", ms, lcs);
                    i = i + 1;
                    break;
                } else
                    fscanf(symf, "%s%s", sym, symaddr);
            }
            if (strcmp(mne, "RESW") == 0) // If resw
                lc = lc + 3 * atoi(opnd);
            else if (strcmp(mne, "BYTE") == 0) {
                strcpy(s2, "-");
                len = strlen(opnd);
                lc = lc + len - 2;
                for (k = 2; k < len; k++) {
                    q[l] = opnd[k];
                    l = l + 1;
                }
                fprintf(outf, "%s\t%s\n", q, s2);
                break;
            } else if (strcmp(mne, "RESB") == 0)
                lc = lc + atoi(opnd);
            else if (strcmp(mne, "WORD") == 0) {
                strcpy(s3, "#");
                lc = lc + 3;
                fprintf(outf, "%s\t%s\n", opnd, s3);
                break;
            }
        } // else la=-

        fseek(optf, SEEK_SET, 0);
        fscanf(inpf, "%s%s%s", la, mne, opnd);
    }
    fseek(outf, SEEK_SET, 0);
    pgmlen = lc - sa; // Program Length
    printf("H^%s^%d^0%x\n", name, sa, pgmlen); // Printing Head record
    fprintf(resf, "H^%s^%d^0%x\n", name, sa, pgmlen); 
    printf("T^"); // Text Record
    fprintf(resf, "T^"); // Text Record
    printf("00%d^0%x", sa, pgmlen); // Printing the length and initial address
    fprintf(resf, "00%d^0%x", sa, pgmlen); // Printing the length and initial address
    fscanf(outf, "%s%s", obj1, obj2);
    while (!feof(outf)) { // Looping through output.txt and preparing O
        if (strcmp(obj2, "0000") == 0){ // If the operand is fordward referenced 0000 as address
            printf("^%s%s", obj1, obj2);
            fprintf(resf, "^%s%s", obj1, obj2);
        } else if (strcmp(obj2, "-") == 0) {
            printf("^");
            fprintf(resf, "^");
            len1 = strlen(obj1);
            for (k = 0; k < len1; k++)
                printf("%d", obj1[k]);
                fprintf(resf, "%d", obj1[k]);
        } else if (strcmp(obj2, "#") == 0) {
            printf("^");
            fprintf(resf, "^");
            fprintf(resf, "%s", obj1);
        }
        fscanf(outf, "%s%s", obj1, obj2);
    }
    fseek(outf, SEEK_SET, 0);
    fscanf(outf, "%s%s", obj1, obj2);
    while (!feof(outf)) { // Fixing the operand if fordward referenced
        if (strcmp(obj2, "0000") != 0) {
            if (strcmp(obj2, "-") != 0) {
                if (strcmp(obj2, "#") != 0) {
                    printf("\n");
                    fprintf(resf, "\n");
                    printf("T^%s^02^%s", obj1, obj2);
                    fprintf(resf, "T^%s^02^%s", obj1, obj2);
                }
            }
        }
        fscanf(outf, "%s%s", obj1, obj2);
    }
    printf("\nE^00%d\n", sa); // End Record and address of first executable instruction
    fprintf(resf, "\nE^00%d", sa);
    return 0;
}
