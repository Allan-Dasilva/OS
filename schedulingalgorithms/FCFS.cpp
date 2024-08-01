#include<iostream>
#include<algorithm>

using namespace std;

struct process
{
 int pno,at,ct,bt,tat,wt;
}*p;

void sort_processes(int n)
{struct process temp;
    for(int i=0;i<n-1;i++)
    {
       for(int j=0;j<n-1-i;j++)
       {
            if(p[j].at>p[j+1].at)
            {    
                temp=p[j];
                p[j]=p[j+1];
                p[j+1]=temp;
            }
       }
    }
}


void showganttchart( int n)
{
    
   cout<<endl<<"\e[1mGANTT CHART\e[0m"<<endl<<endl;;
    cout<<"|";
    int current=0;
    for(int i=0;i<n;i++)
    {   
        if(current<p[i].at&& current!=0)
        {   cout<<"ID";
            for(int k=current;k<=p[i].at;k++)
                cout<<" ";
        cout<<"|";
        }
        for(int j=0;j<=p[i].bt;j++)
        {
            cout<<" ";
            if(j==(p[i].bt)/2)
              cout<<"P"<<p[i].pno;
        }
       cout<<"|";
       current=current+p[i].bt;
    }
     cout<<endl;

     cout<<p[0].at;
    int ct=p[0].ct;
     for(int i=0;i<n;i++)
    {   
        if(ct<p[i].at)
        {
            for(int j=ct;j<p[i].at;j++)
            { 
                cout<<" ";
                ct++;
            }
            cout<<"   "<<ct;
            
        }
        for(int j=0;j<p[i].bt;j++)
        {  cout<<" ";
            if(j==(p[i].bt/2))
                cout<<"   ";
        }
       cout<<p[i].ct;
       ct=p[i].ct;
    }
    cout<<endl;

}

void showtable(int n)
{   cout<<endl<<"\e[1mPROCESS TABLE\e[0m"<<endl<<endl;;
    cout<<"\e[1mPNo.\tAT\tBT\tCT\tTAT\tWT\e[0m"<<endl;
    for( int i=0;i<n;i++)
	{
     cout<<p[i].pno<<"\t"<<p[i].at<<" \t"<<p[i].bt<<" \t"<<p[i].ct<<" \t"<<p[i].tat<<" \t"<<p[i].wt<<endl;
	}

}

int main()
{
	
 int n;
cout<<"Enter the number of processes: ";
cin>>n;
 p= new process[n];
int sum=0;
float avgtat=0,avgwt=0;

cout<<"Enter the processes arrival time  and burst time\n";
for(int i=0;i<n;i++)
{
   p[i].pno=i+1;
   cin>>p[i].at>>p[i].bt; 
}

sort_processes(n);

for(int i=0;i<n;i++)
{
    sum=max(sum,p[i].at);
   sum+=p[i].bt;
   p[i].ct=sum;
   p[i].tat=p[i].ct-p[i].at;
   p[i].wt=p[i].tat-p[i].bt;
   avgtat+=p[i].tat;
   avgwt+=p[i].wt;

}

showganttchart(n);
showtable(n);

cout<<endl;
cout<<"Average Turn Around Time(TAT)= \e[1m"<<avgtat/n<<"\e[0m"<<endl;
cout<<"Average Waiting Time(WT)= \e[1m"<<avgwt/n<<"\e[0m"<<endl<<endl;

}