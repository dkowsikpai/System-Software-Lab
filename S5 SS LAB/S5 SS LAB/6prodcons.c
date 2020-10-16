    #include<stdio.h>
    #include<stdlib.h>
    int buffer,empty,full=0,mutex=1;
     
    int wait(int s){
        while(s<=0); //Busy waiting
        return --s;
    }
    int signal(int s){
        return ++s;
    }
    void produce(){
        int i;
        if(mutex==1 && empty!=0){
            mutex=wait(mutex);
            full=signal(full);
       
            empty=wait(empty);
            mutex=signal(mutex);
       
        }else
            printf("\n Buffer is Full , cannot produce\n");
           
    }
     
    void consume(){
        int i;
        if(mutex==1 && full!=0){
            mutex=wait(mutex);
           
            full=wait(full);
            empty=signal(empty);
           
            mutex=signal(mutex);
           
        }else
            printf("\nConsumer cannot consume : Buffer empty\n");
           
    }
     
     
    void main(){
        int i,n,p[10],c[10],ci,pi;
        printf("\nBuffer size: ");
        scanf("%d",&buffer);
        empty=buffer;
       
        printf("Number of Production/Consumption: ");
        scanf("%d",&n);
        printf("Production rate: ");
        for(i=0;i<n;++i)
            scanf("%d",&p[i]);
        printf("Consumption rate: ");
        for(i=0;i<n;++i)
            scanf("%d",&c[i]);
        printf("\nBuffer spaces filled: %d",full);
        consume(c[0]);
        ci=0;pi=0;
        for(;;)
        {
            if(full>c[ci])
            {    
                for(i=0;i<c[ci];++i)
                    consume();
                printf("\nConsumer consumed successfully");
                printf("\nBuffer spaces filled: %d\n",full);
                ci++;
            }
            else
            {
                for(i=0;i<p[pi];++i)
                    produce();
                printf("\nProducer produced successfully");
                printf("\nBuffer spaces filled: %d\n",full);
                pi++;
            }
            if(ci==n)
                break;
        }
    }
     
