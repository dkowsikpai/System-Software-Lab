#include<stdio.h>

int main()
{
	int n,i,j,k,m;
	printf("Enter number of blocks: ");
	scanf("%d",&n);
	int st_addr[4],length[4],status[4],flag[4];
	char a[11];
	char str[10];
	for(i=1;i<n+1;++i)
		a[i]='0';
	for(i=0;i<4;++i)
		flag[i]=0;
	for(i=0;i<4;++i)
		status[i]=0;
	for(i=0;i<4;++i)
	{
		printf("\nEnter start address: ");
		scanf("%d",&st_addr[i]);
		printf("Enter Length: ");
		scanf("%d",&length[i]);
		for(j=st_addr[i];j<st_addr[i]+length[i];j++)
			if(a[j]!='0')
				flag[i]=1;
		if(flag[i] == 1)
			status[i] = 0;
		else
		{
			printf("Enter file content: ");
			k=0;
			scanf("%s", str);
			for(j=st_addr[i];j<st_addr[i]+length[i];j++)
			{
				a[j]=str[k];
				k++;
			}
			status[i]=1;
		}
	}
	printf("\nRequest's starting address\tstatus");
	for(i=0;i<4;++i)
	{
		printf("\n %d \t\t\t\t",st_addr[i]);
		if(status[i]==1)
			printf("Allocated");
		else
			printf("Not Allocated");
	}
	printf("\n\n");
	printf("\nStatus of memory blocks\n");
	printf("\nBlocks\tStatus");
	for(i=1;i<n+1;++i)
	{
		printf("\n%d\t",i);
		if(a[i]=='0')
			printf("Free");
		else
			printf("Occupied");
	}
	printf("\n\n");
	printf("\nContent of memory blocks\n");
	printf("\nBlocks\tContents");
	printf("\n7 \t %c",a[7]);
	printf("\n8 \t %c",a[8]);
	printf("\n2 \t %c",a[2]);
	printf("\n\n");
	return 0;
}
