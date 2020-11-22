/**
 * Implementation of Pass 1 of Macro Processor
 * Author: Kowsik Nandagopan D
*/

// Librabries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void main() {
    FILE *min,*ntab,*dtab;
    char mne[20],opnd[20],la[20];

    // Opening files
    min=fopen("minp2.txt","r"); // input
    ntab=fopen("ntab2.txt","w+"); // name table
    dtab=fopen("dtab2.txt","w+"); // defenition table
    fscanf(min,"%s%s%s",la,mne,opnd);
    while(strcmp(mne,"MEND")!=0) { // till file end
        if(strcmp(mne,"MACRO")==0) { // if macro
            fprintf(ntab,"%s\n",la); // enter the name to name tab
            fprintf(dtab,"%s\t%s\n",la,opnd); // enter the defenition to defenition tab
        }
        else
            fprintf(dtab,"%s\t%s\n",mne,opnd); // enter the body of macro till the MEND
        fscanf(min,"%s%s%s",la,mne,opnd);
    }
    fprintf(dtab,"%s",mne); // Enter MEND to def tab
    // Closing file
    fclose(min);
    fclose(ntab);
    fclose(dtab);
    printf("PASS 1 is successful\n");
}
    
