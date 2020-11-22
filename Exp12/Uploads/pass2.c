/**
 * Implementation of Pass 2 of Macro Processor
 * Author: Kowsik Nandagopan D
*/

// Librabries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void main(){
    FILE *minp,*ntab,*dtab,*atab,*op;
    int i,len;
    char mne[20],opnd[20],la[20],name[20],mne1[20],opnd1[20],arg[20];

    // Opening files
    minp=fopen("minp2.txt","r"); // input
    ntab=fopen("ntab2.txt","r"); // name tab from pass 1
    dtab=fopen("dtab2.txt","r"); // def tab from pass 1
    atab=fopen("atab2.txt","w+"); // argument tab to store the positional argument
    op=fopen("op2.txt","w"); // output - expanded code
    fscanf(minp,"%s%s%s",la,mne,opnd); // reading input
    while(strcmp(mne,"END")!=0) { // till not END
        if(strcmp(mne,"MACRO")==0) { // If macro skip the defenition part
            fscanf(minp,"%s%s%s",la,mne,opnd); // skip till MEND
            while(strcmp(mne,"MEND")!=0)
                fscanf(minp,"%s%s%s",la,mne,opnd);
        } else { // if not macro body
            fscanf(ntab,"%s",name); // read the name tab
            if(strcmp(mne,name)==0) { // (Macro invocation) check whether the mnemonic is name -> name of macro or not
                len=strlen(opnd); // getting the positional arguments
                for(i=0;i<len;i++) {
                    if(opnd[i]!=',') // if comma encountered next variable
                        fprintf(atab,"%c",opnd[i]); // enter into argument tab
                    else
                        fprintf(atab,"\n"); // Enter each arg in a new line
                }
                fseek(ntab,SEEK_SET,0); // rewind
                fseek(atab,SEEK_SET,0); // rewind
                fscanf(dtab,"%s%s",mne1,opnd1); // reading the def tab
                fprintf(op,".\t%s\t%s\n",mne1,opnd); // print the def as comment in the code -> a convention to display comment. For debugging
                fscanf(dtab,"%s%s",mne1,opnd1); // scan next line
                while(strcmp(mne1,"MEND")!=0) { // till MEND
                    if((opnd1[0]=='&')) { // If postional arg encountered
                        fscanf(atab,"%s",arg); // scan the arg tab and replace it
                        fprintf(op,"-\t%s\t%s\n",mne1,arg); // Enter into the output
                    } else
                        fprintf(op,"-\t%s\t%s\n",mne1,opnd1); // Enter to output if not &
                    fscanf(dtab,"%s%s",mne1,opnd1); // scan next instruction from def tab
                }
            } else
                fprintf(op,"%s\t%s\t%s\n",la,mne,opnd); // if not macro invocation then enter the instruction as such
        }
        fscanf(minp,"%s%s%s",la,mne,opnd); // Scan the instruction from the input
    }
    fprintf(op,"%s\t%s\t%s\n",la,mne,opnd); // Add the end to the final output
    // Close file
    fclose(minp);
    fclose(ntab);
    fclose(dtab);
    fclose(atab);
    fclose(op);
    printf("Pass 2 is succesful\n");

}
    
