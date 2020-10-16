    #include<stdio.h>
    int safe(int max[][10],int alloc[][10],int avail[],int m, int n){
    	int order[10]={0},need[10][10],work[10];
    	int finish[10]={0},found=0,i,j,k;
    	for(i=0;i<n;++i){
    		for(j=0;j<m;++j){
    			need[i][j]=max[i][j]-alloc[i][j];
    		}
    	}
    	printf("\nNEED\nA B C\n");
    	for(i=0;i<n;++i){
    		for(j=0;j<m;++j){
    			printf("%d ",need[i][j]);
    		}
    		printf("\n");
    	}
    	for(j=0;j<m;++j){
    		work[j]=avail[j];
    	}
    	int count=0;
    	while(count<n){
    		found=0;
    		for(i=0;i<n;++i){
    			if(finish[i]==0){
    				for(j=0;j<m;++j){
    					if(need[i][j]>work[j]){
    						break;
    					}
    				}
    				if(j==m){
    					for(k=0;k<m;++k){
    						work[k]=work[k]+alloc[i][k];
    					}
    					order[count++]=i;
    					finish[i]=1;
    					found=1;
    				}
    			}
    		}
    		if(found==0){
    			printf("\nRequest Denied\n");
    			return 0;
    		}
    	}
    	printf("\nSafe Sequence :\t");
    	for(i=0;i<n-1;++i){
    		printf("P%d-",order[i]);
    	}
    	printf("P%d\n",order[n-1]);
    }
    int request(int max[][10],int alloc[][10],int avail[],int req[],int num, int m, int n){
    	int order[10]={0},need[10][10],work[10];
    	int finish[10]={0},found=0,i,j,k;
    	for(j=0;j<m;++j){
    		if(req[j]>avail[j]){
    			printf("\nDenied\n");
    			return 0;
    		}
    	}
    	for(j=0;j<m;++j){
    		alloc[num][j]=alloc[num][j]+req[j];
    		avail[j]=avail[j]-req[j];
    	}
    	for(i=0;i<n;++i){
    		for(j=0;j<m;++j){
    			need[i][j]=max[i][j]-alloc[i][j];
    		}
    	}
    	printf("\nNEED\nA B C\n");
    	for(i=0;i<n;++i){
    		for(j=0;j<m;++j){
    			printf("%d ",need[i][j]);
    		}
    		printf("\n");
    	}
    	for(j=0;j<m;++j){
    		work[j]=avail[j];
    	}
    	int count=0;
    	while(count<n){
    		found=0;
    		for(i=0;i<n;++i){
    			if(finish[i]==0){
    				for(j=0;j<m;++j){
    					if(need[i][j]>work[j]){
    						break;
    					}
    				}
    				if(j==m){
    					for(k=0;k<m;++k){
    						work[k]=work[k]+alloc[i][k];
    					}
    					order[count++]=i;
    					finish[i]=1;
    					found=1;
    				}
    			}
    		}
    		if(found==0){
    			printf("\nRequest Denied\n");
    			return 0;
    		}
    	}
    	printf("\nSafe Sequence :\t");
    	for(i=0;i<n-1;++i){
    		printf("P%d-",order[i]);
    	}
    	printf("P%d\n\n",order[n-1]);
     
    }
    void main(){
    	int i,j,k,m,n,num,max[10][10],_max[10][10],__max[10][10],alloc[10][10],_alloc[10][10],__alloc[10][10],avail[10],_avail[10],__avail[10],req[10];
    	char ch;
    	printf("Enter number of processes :");
    	scanf("%d",&n);
    	printf("Enter number of resources :");
    	scanf("%d",&m);
    	printf("\n");
	for(i=0;i<n;++i)
	{
	printf("Enter maximum resources needed for P%d :",i);
    	scanf("%d %d %d",&max[i][0],&max[i][1],&max[i][2]);
	}
    	for(i=0;i<n;++i){
    		for(j=0;j<m;++j){
    			_max[i][j]=max[i][j];
    			__max[i][j]=_max[i][j];
    		}
    	}
    	printf("\n");
	for(i=0;i<n;++i)
	{
	printf("Enter allocated resources needed for P%d :",i);
    	scanf("%d %d %d",&alloc[i][0],&alloc[i][1],&alloc[i][2]);
	}
    	for(i=0;i<n;++i){
    		for(j=0;j<m;++j){
    			_alloc[i][j]=alloc[i][j];
    			__alloc[i][j]=_alloc[i][j];
    		}
    	}
    	printf("\n");
    	for(j=0;j<m;++j){
    		printf("Enter available resource R%d :",j);
    		scanf("%d",&avail[j]);
    		_avail[j]=avail[j];
    		__avail[j]=_avail[j];
    	}
     
    	safe(max,alloc,avail,m,n);
     
    	printf("\n");
    	for(j=0;j<m;++j){
    		printf("Enter request of resource R%d :",j);
    		scanf("%d",&req[j]);
    	}
    	request(_max,_alloc,_avail,req,1,m,n);
    	for(j=0;j<m;++j){
    		printf("Enter request of resource R%d :",j);
    		scanf("%d",&req[j]);
    	}
    	request(__max,__alloc,__avail,req,4,m,n);
    }
