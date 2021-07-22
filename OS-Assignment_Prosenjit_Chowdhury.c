/*Program  - LAB ASSIGNMENT Operating Systems
Author   - Md. Prosenjit Chowdhury
ID - 183-16-346
Dept. of Computing & Information System
Daffodil International University
Language - C Language
Date     - 07/03/2020*/
#include <stdio.h>

void sjfchar(int grtp[],int time);
struct process{
    int name;
    int at,bt,wt,tt,rt;
    int completed;
    float ntt;
}p[50];

int n;
int q[50];  //queue
int front=-1,rear=-1;
// enqueue function for round robin
void enqueue(int i){
    if(rear==50)
        printf("Queue is overflow");
    rear++;
    q[rear]=i;
    if(front==-1)
        front=0;
}

int dequeue(){
    if(front==-1)
        printf("Queue is empty");
    int temp=q[front];
    if(front==rear)
        front=rear=-1;
    else
        front++;
    return temp;
}
//check weather the value is in queue or not
int isInQueue(int i){
    int k;
    for(k=front;k<=rear;k++){
        if(q[k]==i)
            return 1;
    }
    return 0;
}
void sortByArrival(){
    struct process temp;
    int i,j;
    //for(i=0;i<n-1;i++)
    for(j=i+1;j<n;j++){
        if(p[i].at>p[j].at){
            temp=p[i];
            p[i]=p[j];
            p[j]=temp;
        }
    }
}

// SJF Gantt chart
void sjfchart(int grtp[],int time){
    int old=-1,processtime[50],bttime=0;
    int process[30];
    int i,m=0;

    for(i=0;i<time;i++){
        if(grtp[i] == old){
            processtime[m-1] = processtime[m-1]+1;
        }else{
            process[m] =grtp[i];
            processtime[m] =1;
            m++;
            old = grtp[i];
        }
    }
    printf("\nGantt chart:SJF preemptive\n");
    for(i=0;i<m;i++){
        printf("   p[%d] ",process[i]+1);
    }
    printf("\n0\t");
    for(i=0;i<m;i++){
        bttime = bttime+processtime[i];
        printf("%d\t",bttime);
    }
}


int main(){
            //Program Design
        printf("\t\t\t\t---------------------------------------------------\n");
        printf("\t\t\t\t     ### OPERATING SYSTEMS LAB ASSIGNMENT ###       \n");
        printf("\t\t\t\t---------------------------------------------------\n");
        printf("\t\t\t\t       **** MADE BY - Prosenjit Chowdhury ****          \n");
        printf("\t\t\t\t               ID-> 183-16-346                  \n");
        printf("\t\t\t\t---------------------------------------------------\n\n\n");
    int n,atime[10],btime[10],i,j,rtq;
    printf("Enter number of processes: ");
    scanf("%d",&n);
    for(i=0;i<n;i++){
        printf("Enter arrival time for process p%d: ",i+1);
        scanf("%d",&atime[i]);
    }

    for(i=0;i<n;i++){
        printf("Enter burst time for process p%d: ",i+1);
        scanf("%d",&btime[i]);
    }

     printf("\nChoose any one: \n1. Show Gantt Chart\n2. Show comparison table\n");

     int number;
     scanf("%d",&number);
     if(number==1){
         //gantt chart portion
         int chartNo;
         printf("\nChoose any one:\n1. FCFS\n2. SJF preemptive\n3. Round-Robin\n");
         scanf("%d",&chartNo);
         if(chartNo == 1){
                //FCFS portion
                //FCFS code
            int at[10]={0},bt[10]={0},tat[10]={0},wt[10]={0},ct[10]={0},ctn=0;
            int sum=0,j,k;
            float totalTAT=0,totalWT=0;

            for(i=0;i<n;i++){
                at[i] = atime[i];
                bt[i] = btime[i];
            }

            for(j=0;j<n;j++){
                ct[j+1] = ct[j] + bt[j]; //calculate completion time

                tat[j]=ct[j]-at[j]; //calculate Turnaround time TAT = CT-AT
                wt[j]=tat[j]-bt[j]; //calculate Waiting time WT=  TAT+BT

                totalTAT = totalTAT+tat[j];
                totalWT = totalWT+wt[j];
            }

            printf("\n\n");

            //generating gantt chart
            printf("\n Gantt chart of FCFS\n");
            printf(" ");
            for(i=0; i<n; i++) {
                for(j=0; j<bt[i]; j++) printf("--");
                printf(" ");
            }
            printf("\n|");
            for(i=0; i<n; i++) {
                for(j=0; j<bt[i] - 1; j++) printf(" ");
                    printf("P%d", i);
                for(j=0; j<bt[i] - 1; j++) printf(" ");
                    printf("|");
            }
            printf("\n ");

            // printing bottom bar
            for(i=0; i<n; i++) {
                for(j=0; j<bt[i]; j++) printf("--");
                printf(" ");
            }
            printf("\n");

            // printing the time line
            printf("0");
            for(i=0; i<n; i++) {
                for(j=0; j<bt[i]; j++) {
                    printf("  ");
                }
                if(tat[i] > 9) printf("\b"); // backspace : remove 1 space

                ctn = ctn + bt[i];
                printf("%d",ctn);
            }
            printf("\n");

            //end of FCFS gantt chart code
         }
         else if(chartNo == 2){
             //SJF preemptive
             //SJF code
            int time,bt[10],at[10],sum_bt=0,smallest,rem,rt[10],grtp[50];
            int sumt=0,sumw=0;

            for(i=0;i<n;i++){
                at[i] = atime[i];
                bt[i] = btime[i];rt[i]=bt[i];
            }

            rt[9]=bt[9]=9999;
            rem=n;

            for(time=0;rem!=0;time++){
                smallest=9;
                for(i=0;i<n;i++){
                    if(at[i]<=time && rt[i]>0 && rt[i]<rt[smallest])
                    smallest=i;
                }
                rt[smallest]--;
                grtp[time] = smallest;

                if(rt[smallest]==0){
                    rem--;
                    sumt+=time+1-bt[smallest]-at[smallest];
                    sumw+=time+1-at[smallest];
                }
            }

            sjfchart(grtp,time);
            //end of SJF code
        }
         else if(chartNo == 3){
             //Round-Robin portion

            int j,time=0,sum_bt=0,tq,sqt[50],s=0,sql[50],sl=0;
            float avgwt=0,avgtat=0;

            for(i=0;i<n;i++){
                p[i].name = i;
                p[i].at = atime[i];
                p[i].bt = btime[i];

                p[i].rt=p[i].bt;
                p[i].completed=0;
                sum_bt+=p[i].bt;
            }

            printf("\nEnter the time quantum:");
            scanf("%d",&tq);

            sortByArrival();
            enqueue(0);          // enqueue the first process

            for(time=p[0].at;time<sum_bt;){       // run until the total burst time reached
                i=dequeue();
                if(p[i].rt<=tq){
                                          // for processes having remaining time with less than
                    time+=p[i].rt;//From here need to take remaining time
                    sqt[s] = p[i].rt;s++;
                    p[i].rt=0;
                    p[i].completed=1;
                    sql[sl] = p[i].name;sl++;
                    p[i].wt=time-p[i].at-p[i].bt;
                    p[i].tt=time-p[i].at;
                    p[i].ntt=((float)p[i].tt/p[i].bt);
                    for(j=0;j<n;j++) {               //enqueue the processes which have come
                        if(p[j].at<=time && p[j].completed!=1&& isInQueue(j)!=1){
                            enqueue(j);
                        }
                    }
                }else{              // more than time quantum
                    time+=tq;
                    p[i].rt-=tq;
                    sqt[s] = tq;s++;
                    sql[sl] = p[i].name;sl++;
                    for(j=0;j<n;j++){    //first enqueue the processes which have come while
                        if(p[j].at<=time && p[j].completed!=1&&i!=j&& isInQueue(j)!=1){
                            enqueue(j);
                        }
                    }
                    enqueue(i);   // then enqueue the uncompleted process
                }
            }

            for(i=0;i<n;i++){
                avgwt+=p[i].wt;
                avgtat = avgtat+p[i].tt;
            }

            printf("\nGantt chart in Round-Robin\n");
            for(i=0;i<sl;i++){
                printf("  p[%d]\t",sql[i]+1);
            }
            printf("\n0\t");
            int charttime = 0;
            for(i=0;i<s;i++){ //sqt = sequence time,sl = sequence list,s =sequence,sql = sequence list
                charttime=charttime+sqt[i];
                printf("%d\t",charttime);
            }
            //end of Round robin code

        }//if number not be within gantt chart
        else{

        printf("\nThe number is invalid. Try again\n");

        }
    }else if(number == 2){
        //comparison portion
        printf("\nEnter the time quantum for Round robin:");
        scanf("%d",&rtq);

        //FCFS code
        int fbt[10]={0},fat[10]={0},ftat[10]={0},fwt[10]={0},fct[10]={0};
        int fsum=0,fk;
        float ftotalTAT=0,ftotalWT=0,fcfstat=0,fcfswt=0;

        for( i=0;i<n;i++){
            fat[i] = atime[i];
            fbt[i] = btime[i];
        }

        for(j=0;j<n;j++){
            //calculate completion time
            fsum+=fbt[j];
            fct[j]+=fsum;

            ftat[j]=fct[j]-fat[j]; //calculate Turnaround time TAT = CT-AT
            fwt[j]=ftat[j]-fbt[j]; //calculate Waiting time WT=  TAT+BT

            ftotalTAT = ftotalTAT+ftat[j];
            ftotalWT = ftotalWT+fwt[j];
        }

        fcfstat = ftotalTAT/n;
        fcfswt = ftotalWT/n;

        //end of FCFS code

        //SJF code
        int sjftime,sjfbt[10],sjfat[10],sjfsum_bt=0,sjfsmallest,sjfrem,sjfrt[10],grtp[50];
        int sjfsumtat=0,sjfsumwat=0;

        for(i=0;i<n;i++){
            sjfat[i] = atime[i];
            sjfbt[i] = btime[i];
            sjfrt[i]=sjfbt[i];
        }

        sjfrt[9]=sjfbt[9]=9999;
        sjfrem=n;

        for(sjftime=0;sjfrem!=0;sjftime++){

            sjfsmallest=9;
            for(i=0;i<n;i++){

                if(sjfat[i]<=sjftime && sjfrt[i]>0 && sjfrt[i]<sjfrt[sjfsmallest])
                sjfsmallest=i;
            }
            sjfrt[sjfsmallest]--;
            grtp[sjftime] = sjfsmallest;

            if(sjfrt[sjfsmallest]==0){

                sjfrem--;
                sjfsumtat+=sjftime+1-sjfbt[sjfsmallest]-sjfat[sjfsmallest];
                sjfsumwat+=sjftime+1-sjfat[sjfsmallest];
            }
        }//end of SJF code

        //Round robin code
        int rtime=0,rsum_bt=0,sqt[50],s=0,sql[50],sl=0;
        float ravgwt=0,ravgtat=0;

        for(i=0;i<n;i++){
            p[i].name=i;
            p[i].at = atime[i];
            p[i].bt = btime[i];

            p[i].rt=p[i].bt;
            p[i].completed=0;
            rsum_bt+=p[i].bt;
        }


        sortByArrival();
        enqueue(0);          // enqueue the first process

        for(rtime=p[0].at;rtime<rsum_bt;){ // loop until until reached the total bust time
            i=dequeue();

            if(p[i].rt<=rtq){
                rtime+=p[i].rt;//From here remaining time need to take
                sqt[s] = p[i].rt;s++;
                p[i].rt=0;
                p[i].completed=1;
                sql[sl] = p[i].name;sl++;
                p[i].wt=rtime-p[i].at-p[i].bt;
                p[i].tt=rtime-p[i].at;
                p[i].ntt=((float)p[i].tt/p[i].bt);
                for(j=0;j<n;j++) {
                        //enqueue the processes which have come while scheduling
                    if(p[j].at<=rtime && p[j].completed!=1&& isInQueue(j)!=1){
                        enqueue(j);
                    }
                }
            }
            else{             // if more than time quantum
                rtime+=rtq;
                p[i].rt-=rtq;
                sqt[s] = rtq;s++;
                sql[sl] = p[i].name;sl++;
                for(j=0;j<n;j++){
                    if(p[j].at<=rtime && p[j].completed!=1&&i!=j&& isInQueue(j)!=1){
                        enqueue(j);
                    }
                }
                enqueue(i);   //enqueue the uncompleted process
            }
        }
        for(i=0;i<n;i++){
            ravgwt+=p[i].wt;
            ravgtat = ravgtat+p[i].tt;
        }

        float roundravgwt,roundravgtat;
        roundravgwt = ravgwt/n;
        roundravgtat = ravgtat/n;

        //end of Round robin code

        //display option
        printf("\nSample Comparison Table: \n\n");
        printf("Algorithm\tAvg. Waiting Time(ms)\tAvg. Turnaround Time(ms)\n");
        printf("FCFS\t\t\t%0.3f\t\t %0.3f\n",fcfswt,fcfstat);
        printf("SJF (Preemptive)\t%0.3f\t\t %0.3f\n",sjfsumtat*1.0/n,sjfsumwat*1.0/n);
        printf("Round-Robin\t\t%0.3f\t\t %0.3f\n",roundravgwt,roundravgtat);

        //comparison code
    }else{
        printf("\nThe number is invalid. Try again\n");
    }
}

