        #include<stdio.h>
        #include<stdlib.h>
        #include<string.h>
        #define MAX 11
        char l[10];
        void search();
        
        struct symb
        {
        int add;
        char label[10];
        }sy[11];
        
        void main()
        {
        int a[MAX],num,key,i,ch;
        char ans;
        int create(int);
        void lprob(int [],int,int);
        void display(int []);
        for(i=0;i<MAX;i++)
        a[i]=0;
        do
        {
        printf("\n\n1.Create a symbol table \n2.Search in the symbol table\nEnter your choice:");
        scanf("%d",&ch);
        switch(ch)
        {
        case 1:
        do
        {
        printf("\nEnter the address:");
        scanf("%d",&num);
        key=create(num);
        printf("Enter The label:");
        scanf("%s",l);
        lprob(a,key,num);
        printf("\nContinue(y/n): ");
        scanf("%s",&ans);
        }
        while(ans=='y');
        display(a);
        break;
        case 2:
        search();
        break;
        }
        }while(ch<=2);
        }
         
        int create(int num)
        {
        int key;
        key=num%11;
        return key;
        }
         
        void lprob(int a[MAX],int key,int num)
        {
        int flag,i,count=0;
        void display(int a[]);
        flag=0;
        if(a[key]==0)
        {
        a[key]=num;
        sy[key].add=num;
        strcpy(sy[key].label,l);
        }
        else
        {
        i=0;
        while(i<MAX)
        {
        if(a[i]!=0)
        count++;
        i++;
        }
        if(count==MAX)
        {
        printf("\nHash table is full");
        display(a);
        exit(1);
        }
        for(i=key+1;i<MAX;i++)
        if(a[i]==0)
        {
        a[i]=num;
        flag=1;
        sy[key].add=num;
        strcpy(sy[key].label,l);
        break;
        }
        for(i=0;i<key && flag==0;i++)
        if(a[i]==0)
        {
        a[i]=num;
        flag=1;
        sy[key].add=num;
        strcpy(sy[key].label,l);
        break;
        }
        }
        }
        void display(int a[MAX])
        {
        FILE *fp;
        int i;
        fp=fopen("symbol.txt","w");
        printf("\nThe Symbol Table is\n");
        printf("\nHashvalues\t address\t label");
        for(i=0;i<MAX;i++)
        {
        printf("\n%d\t\t %d\t\t %s",i,sy[i].add,sy[i].label);
        fprintf(fp,"\n%d %d %s",i,sy[i].add,sy[i].label);
        }
        fclose(fp);
	printf("\n");
	printf("\n");
        }
         
        void search()
        {
        FILE *fp1;
        char la[10];
        int set=0,s;
        int j,i;
        printf("Enter the label: ");
        scanf("%s",la);
        fp1=fopen("symbol.txt","r");
        for(i=0;i<MAX;i++)
        {
        fscanf(fp1,"%d%d",&j,&sy[i].add);
        if(sy[i].add!=0)
        fscanf(fp1,"%s",sy[i].label);
        }
        for(i=0;i<MAX;i++)
        {
        if(sy[i].add!=0)
        {
        if(strcmp(sy[i].label,la)==0)
        {
        set=1;
        s=sy[i].add;
        }
        }
        }
        if(set==1)
        printf("\nThe label <--%s--> is present in the symbol table at address: <--%d-->\n",la,s);
        else
        printf("\n***The label is not present in the symbol table***\n");
        }
         
