#include<stdio.h>
struct sjf
{
       int bt,at,wt,st,pno,tt,cbt;
};

int get(struct sjf arr[],int t,int n)
{
       int imin,min=9999,i;
       for(i=0;i<n;i++)
       {
              if(arr[i].at<=t&&arr[i].st==0)
                     if(min>arr[i].bt)
                     {
                           min=arr[i].bt;
                           imin=i;
                     }
       }
       return imin;
}

void gantt_chart(struct sjf arr[],int p[],int n,int nop)
{
       int i,a[100],s=0;
       float avgtt=0,avgwt=0;

       printf("\n======================================\n");
       printf("GANTT CHART:\n");
       printf("0");
       for(i=0;i<n-1;i++)
       {
              while(i<n-1&&p[i]==p[i+1])
              {
                     s++;
                     i++;
              }

              s++;
              printf(" | [P%d] | %d |",arr[p[i]].pno,s);
              arr[p[i]].wt=s-arr[p[i]].at-arr[p[i]].tt;
       }

       for(i=0;i<nop;i++)
       {
              arr[i].tt+=arr[i].wt;
              avgwt+=arr[i].wt;
              avgtt+=arr[i].tt;
       }
       printf("\n======================================\n");
       printf("Pr.\tA. T.\tB. T.\tW. T.\tT. T.\n");
       printf("======================================\n");
       for(i=0;i<nop;i++)
       {
              printf("[P%d]\t  %d\t  %d\t  %d\t  %d\n",arr[i].pno,arr[i].at,arr[i].cbt,arr[i].wt,arr[i].tt);
       }
       printf("======================================\n");

       avgwt = avgwt/nop;
       avgtt = avgtt/nop;
       printf("\nAverage Waiting Time: %.2f\n",avgwt);
       printf("Average Turnaround Time: %.2f\n",avgtt);
       printf("=======================================\n");
       return;
}

int iscomplite(struct sjf arr[],int n)
{
       int i;
       for(i=0;i<n;i++)
              if(arr[i].st==0)
                     return 0;
       return 1;
}
int main()
{
       int n,i,a,t=0;
       int p[100];
       float avgwt=0,avgtt=0;
       struct sjf arr[100];
       printf("\t\t\t\t\t\tSJF (Shortest Job First) - Preemptive\n");
       printf("\n\t\t\t\t\t   ===============================================\n");
       printf("\nEnter Number of Processes: ");
       scanf("%d",&n);
       for(i=0;i<n;i++)
       {
              printf("\nEnter Arrival Time & Burst Time for Process [P%d]: \n",i);
              scanf("%d%d",&arr[i].at,&arr[i].bt);
              arr[i].pno = i;
              arr[i].cbt = arr[i].bt;
              arr[i].st=0;
              arr[i].tt=arr[i].bt;
              arr[i].wt=0;
       }
       i=0;
       while(1)
       {
              if(iscomplite(arr,n))
                     break;
              a=get(arr,t,n);
              p[i]=a;
              arr[a].bt-=1;
              if(arr[a].bt==0)
                     arr[a].st=1;
              t=t+1;
              i++;
       }
       gantt_chart(arr,p,i,n);
       return 0;
}
