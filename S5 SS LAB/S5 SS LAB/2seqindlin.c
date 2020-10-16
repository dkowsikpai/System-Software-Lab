#include<stdio.h>

void main()
{
	int n,t,f,ch,q,l=1;
	int i,j,pos,next;
	printf("Enter no of processes:");
	scanf("%d",&n);
	int at[n],bt[n],bti[n],p[n],tat[n],wt[n],done[n]; //waiting time, burst time, turn around time, arrival time, priority
	for(i=0;i<n;i++)
	{
		printf("Enter arrival time of process %d:",i+1);
		scanf("%d",&at[i]); //arrival time for each process
		printf("Enter burst time of process %d:",i+1);
		scanf("%d",&bt[i]); //burst time for each process
		printf("Enter priority of process %d:",i+1);
		scanf("%d",&p[i]); //priority for each process
	}
	printf("Enter time quantum:");
	scanf("%d",&q);
	while(l!=0)
	{
		int totalwt=0,totaltat=0; //total waiting time, total turn around time
		float avgwt=0,avgtat=0; //average waiting time, average turnaround time;
		printf("1.FCFS	2.SJF	3.Round Robin	4.priority	5.Exit");
		printf("\nEnter your choice:");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1:	for(i=0;i<n;i++)
					{
						wt[i]=0;
						for(j=0;j<i;j++)
							wt[i]=wt[i]+bt[j];
						wt[i]=wt[i]-at[i];
						tat[i]=wt[i]+bt[i];                 
					}
					printf("\nProcess\tAT\tBT\tPriority\tTAT\tWT");
					for(i=0;i<n;i++)
					{
						totalwt=totalwt+wt[i];
						totaltat=totaltat+tat[i];
						printf("\nP[%d]\t%d\t%d\t%d\t\t%d\t%d",i+1,at[i],bt[i],p[i],tat[i],wt[i]);
					}
					avgwt=(float)totalwt/n;
					avgtat=(float)totaltat/n;
					printf("\n\nAverage Turnaround Time:%f",avgtat);
					printf("\nAverage Waiting Time:%f",avgwt);
					printf("\n\n");   
			break;
			case 2:	t=0;
					for(i=0;i<n;i++)
						done[i]=0;
					for(j=0;j<n;j++)
					{
						i=0;
						next=-1;
						while(at[i]<=t)
						{
							if(next==-1 && done[i]==0)
								next=i;
							else if(bt[next]>bt[i] && done[i]==0)
								next=i;
							i++;
						}
						wt[next]=t-at[next];
						t=t+bt[next];
						tat[next]=t-at[next];
						done[next]=1;
					}
					printf("\nProcess\tAT\tBT\tPriority\tTAT\tWT");
					for(i=0;i<n;i++)
					{
						totalwt=totalwt+wt[i];
						totaltat=totaltat+tat[i];
						printf("\nP[%d]\t%d\t%d\t%d\t\t%d\t%d",i+1,at[i],bt[i],p[i],tat[i],wt[i]);
					}
					avgwt=(float)totalwt/n;
					avgtat=(float)totaltat/n;
					printf("\n\nAverage Turnaround Time:%f",avgtat);
					printf("\nAverage Waiting Time:%f",avgwt);
					printf("\n\n");
			break;          
			case 3:	for(i=0;i<n;i++)
						done[i]=0;
					t=0;
					pos=0;      
					for(i=0;i<n;i++)
						bti[i]=bt[i];               
					while(1)
					{
						f=1;
						for(i=0;i<n;i++)
							if(done[i]==0)
							{
								f=0;
								break;
							}
						if(f==1)
							break;
						if(at[pos] > t)
						{
							pos=0;
							continue;
						}
						if(done[pos]==0)
						{
							if(bt[pos]<=q)
							{
								t=t+bt[pos];
								tat[pos]=t-at[pos];
								wt[pos]=tat[pos]-bti[pos];
								done[pos]=1;
							}
							else
							{
								t=t+q;
								bt[pos]=bt[pos]-q;  
							}                                   
						}
						if(pos==n-1)
							pos=0;
						else
							pos++;
					}
					printf("\nProcess\tAT\tBT\tPriority\tTAT\tWT");
					for(i=0;i<n;i++)
					{
						totalwt=totalwt+wt[i];
						totaltat=totaltat+tat[i];
						printf("\nP[%d]\t%d\t%d\t%d\t\t%d\t%d",i+1,at[i],bt[i],p[i],tat[i],wt[i]);
					}
					avgwt=(float)totalwt/n;
					avgtat=(float)totaltat/n;
					printf("\n\nAverage Turnaround Time:%f",avgtat);
					printf("\nAverage Waiting Time:%f",avgwt);
					printf("\n\n");                           
			break;
			case 4:	for(i=0;i<n;i++)
						done[i]=0;
					t=0;
					p[next]=n+1;
					for(j=0;j<n;j++)
					{
						i=0;
						next=-1;
						while(at[i]<=t)
						{
							if(next==-1 && done[i]==0)
								next=i;
							else if(p[next]>p[i] && done[i]==0)
								next = i;
							i++;
						}
						done[next]=1;
						wt[next]=t-at[next];
						t=t+bt[next];
						tat[next]=t-at[next];
					}
					printf("\nProcess\tAT\tBT\tPriority\tTAT\tWT");
					for(i=0;i<n;i++)
					{
						totalwt=totalwt+wt[i];
						totaltat=totaltat+tat[i];
						printf("\nP[%d]\t%d\t%d\t%d\t\t%d\t%d",i+1,at[i],bt[i],p[i],tat[i],wt[i]);
					}
					avgwt=(float)totalwt/n;
					avgtat=(float)totaltat/n;
					printf("\n\nAverage Turnaround Time:%f",avgtat);
					printf("\nAverage Waiting Time:%f",avgwt);
					printf("\n\n");
			break;
			case 5:	l=0;
			break;
			default: printf("Invalid choice");
        }
	}
}
