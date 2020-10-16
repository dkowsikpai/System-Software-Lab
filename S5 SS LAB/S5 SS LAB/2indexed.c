    #include <stdio.h>
    #define BLOCKS 10
    void main()
    {
        
        int i,j,k=0,req[50]={0},indexed[10]={0},c,index[10][10]={0},p[10]={0},f[10]={0},fr=1,ind,len[10];
        char content[10];
        char s[50];
        do
        {
            printf("Enter length,index and contents:\n");
            scanf("%d%d%s",&len[k],&ind,s);
           
            req[k]= ind;
            if(!f[ind])
            {
                indexed[ind] =1;
                f[ind]=1;
                p[k]=0;
                for(j=0;j<len[k];j++)
                {
                    if(!f[fr])
                    {
                    index[ind][j] = fr;
                    content[fr]=s[j];
                    f[fr]=1;
                    fr++;
                    }
                    else{
                        fr++;
                    }
                }
            }
            else{
                p[k]=1;
     
            }
            k++;
            printf("Enter another file?(0/1)");
        
            scanf("%d",&c);
        } while (c!=0);
        
        printf("\n\n");
        for(i=0;i<k;i++)
        {
            printf("P%d \t",i+1);
            if(!p[i])
            {
                int l;
                
                    if(indexed[req[i]])
                    {
                        printf("%d\t",req[i]);
                        j=0;
                        while(index[req[i]][j]!=0)
                        {
                            if(j==0)
                                printf("%d",index[req[i]][j]);
                            else
                                printf(",%d",index[req[i]][j]);
                            j++;
                        }
                        
                    }
                printf("\tAllocated\n");
            }
            else
                printf("%d\t\tNot Allocated\n",req[i]);
     
        }
        printf("Index \t Allocated block\tContent \n");
        for(i=0;i<BLOCKS;i++ )
        {
            
            if(indexed[i])
            {
                j=0;
                while(index[i][j]!=0)
                {
                     printf("s%d \t",i);
                     printf("\t%d \t ",index[i][j]);
                     printf("\t%c \n",content[index[i][j]]);
                     j++;
                }
     
            }
            
        }
     
    }
