#include <stdio.h>

int n, m;
void read(int alloc[][10], int max[][10], int avail[10], int need[][10], int n, int m);
void display(int temp[][10], int n, int m);
int safety(int alloc[][10], int avail[10], int need[][10], int n, int m);

int main()
{
    int alloc[10][10], max[10][10], avail[10], need[10][10];
    read(alloc, max, avail, need, n, m);
}

void read(int alloc[][10], int max[][10], int avail[10], int need[][10], int n, int m)
{
    int i, j;
    printf("Enter total number of processes: ");
    scanf("%d", &n);
    printf("Enter total number of resources: ");
    scanf("%d", &m);
    for (i = 0; i < n; i++)
    {
        printf("\nProcess %d\n", i);
        printf("Allocation Resources: ");
        for (j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);
        printf("Maximum Resources: ");
        for (j = 0; j < m; j++)
            scanf("%d", &max[i][j]);
    }
    printf("\nAvailable System Resources: ");
    for (i = 0; i < m; i++)
        scanf("%d", &avail[i]);

    // Calculating Need matrix
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];        //need = max - allocated

    printf("\n\t\tNEED\n\tA\tB\tC\n");
    display(need, n, m);

    safety(alloc, avail, need, n, m);
}

//Safety algorithm

int safety(int alloc[][10], int avail[10], int need[][10], int n, int m)
{
    int i, j, k, index = 0;
    int isDone[10], sequence[10], count = 0;            
    for (i = 0; i < n; i++)
        isDone[i] = 0;
    for (k = 0; k < n; k++)
    {
	for (i = 0; i < n; i++)
        {
            if (isDone[i] == 0)
	    {                      
                for (j = 0; j < m; j++)
                {
                    if (avail[j] >= need[i][j])
                        continue;
                    else
                        break;
                }
                if (j == m)
		{                          
                    for (j = 0; j < m; j++)
                        avail[j] += alloc[i][j];
                    count++;                            
                    isDone[i] = 1;
                    sequence[count - 1] = i;        /* safe state sequence */
                }
            }
        }
        if (count == n)				 /* safe state */
	{
            printf("\nIT'S A SAFE STATE\n");
            printf("Safe Sequence:\t");
            int i;
            for (i = 0; i < n; i++)
                printf("P%d ", sequence[i]);
            printf("\n");
            break;
        }

    }
    if (count != n)
        printf("\nDeadlock has occured.\n");            /* deadlock */
}

void display(int temp[][10], int n, int m)
{
    int i, j;
    for (i = 0; i < n; i++)
    {
        printf("P%d", i);
        for (j = 0; j < m; j++)
            printf("\t%d", temp[i][j]);
        printf("\n");
    }
    printf("\n");
}
