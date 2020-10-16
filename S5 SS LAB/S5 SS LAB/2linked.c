#include <stdio.h>

struct file{
    int len;
    char content[10];
    int alloc;
};
struct block{
	int val;
	int next;
};

int main(){
    int n,fileno,i,j,flag,cur,curtemp,nxt;
    printf("No of Blocks in Memory : ");
    scanf("%d",&n);
    char memory[n];
    struct block blocks[n];
    for(i=0;i<n;i++)
        memory[i]='#';
    printf("Enter current nodes and links (-1 to exit)\n");
    while(1){
        printf("Current Node : ");
        scanf("%d",&cur);
        if(cur==-1)
            break;
        printf("Next Node : ");
        scanf("%d",&nxt);
        blocks[cur-1].next=nxt-1;
    }
    blocks[nxt-1].next = -1;
    printf("No of Files : ");
    scanf("%d",&fileno);
    struct file files[fileno];
    int start[fileno],end[fileno];
    for(i=0;i<fileno;i++){
    	start[i]=-1;
    	end[i] = -1;
    }
    for(i=0;i<fileno;i++){
        printf("Enter Length and Content of File %d : ",(i+1));
        scanf("%d %s",&files[i].len,files[i].content);
        files[i].alloc = 0;
    }
    cur=0;
    for(i=0;i<fileno;i++){
        flag=0;
        curtemp=cur;
        start[i]=cur+1;
        for(j=0;j<files[i].len;j++){
            if(blocks[cur].next == -1){
                flag=1;
                break;
            }
            else
                curtemp=blocks[curtemp].next;
        }
        if(flag==0){
            files[i].alloc=1;
            for(j=0;j<files[i].len;j++){
                memory[cur]=files[i].content[j];
                if(j == files[i].len-1)
                	end[i] = cur+1;
                cur=blocks[cur].next;
            }
        }
    }
    cur=0;
    printf("\nCurrent Process\t\tStarting Address\tEnding Address\tStatus\n");
    for(i=0;i<fileno;i++){
        printf("\tP%d\t",(i+1));
        if(start[i]!=-1)
        	printf("\t\t%d",start[i]);
        else
        	printf("\t\t");
        if(end[i]!=-1)
        	printf("\t\t%d",end[i]);
        else
        	printf("\t\t");        	
        if(files[i].alloc == 1)
            printf("\t\tAlloted\n");
        else
            printf("\t\tNot Alloted\n");
    }    
    i=0;
    cur=0;
    while(files[i].alloc == 1){
        printf("\nAllocation of P%d  \n",i+1);
        for(j=0;j<files[i].len;j++){
            printf("%d  %c\n",(cur+1),memory[cur]);
            cur=blocks[cur].next;
        }
        i++;
    }
    return 0;
}
