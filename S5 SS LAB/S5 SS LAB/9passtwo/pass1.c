    #include<stdio.h>
    #include<stdlib.h>
    #include<string.h>
    void main()
    {
    FILE *f1,*f2,*f3,*f4;
    int lc,start,op1,optab_num,len;
    char opcode[20],label[20],operand[20],optab_code[20];
    f1=fopen("input.txt","r");
    f3=fopen("symtab.txt","w");
    fscanf(f1,"%s %s %d",label,opcode,&op1);
    if(strcmp(opcode,"START")==0)
    {
     start=op1;
     lc=start;
     printf("\t%s\t%s\t%d\n",label,opcode,op1);
     }
     else
     lc=0;
    fscanf(f1,"%s %s",label,opcode);
    while(!feof(f1))
    {
     fscanf(f1,"%s",operand);
     printf("\n%d\t%s\t%s\t%s\n",lc,label,opcode,operand);
     if(strcmp(label,"-")!=0)
     {
     fprintf(f3,"\n%d\t%s\n",lc,label);
     }
     f2=fopen("optab.txt","r");
     fscanf(f2,"%s %d",optab_code,&optab_num);
     while(!feof(f2))
     {
      if(strcmp(opcode,optab_code)==0)
      {
        lc=lc+3;
        break;
      }
      fscanf(f2,"%s %d",optab_code,&optab_num);
      }
      fclose(f2);
      if(strcmp(opcode,"WORD")==0)
     
        {
       lc=lc+3;
       }
       else if(strcmp(opcode,"RESW")==0)
       {
        op1=atoi(operand);
        lc=lc+(3*op1);
        }
        else if(strcmp(opcode,"BYTE")==0)
        {
        if(operand[0]=='X')
          lc=lc+1;
          else
          {
          len=strlen(operand)-2;
          lc=lc+len;}
        }
        else if(strcmp(opcode,"RESB")==0)
        {
         op1=atoi(operand);
         lc=lc+op1;
         }
        fscanf(f1,"%s%s",label,opcode);
        }
        if(strcmp(opcode,"END")==0)
        {
        printf("Program length = %d",lc-start);
        }
        fclose(f1);
        fclose(f3);
    }
