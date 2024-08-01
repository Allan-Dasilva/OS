#include<iostream>
#include<algorithm>

using namespace std;

struct process
{
 int pno,at,ct,bt,tat,wt;
}*p;

bool compareAT(const process &p1, const process &p2)
{
    return p1.at<p2.at;
}


void showganttchart( int n)
{
    
   cout<<endl<<"\e[1mGANTT CHART\e[0m"<<endl<<endl;;
    cout<<"|";
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<=p[i].bt;j=j+1)
        {
            cout<<" ";
            if(j==(p[i].bt)/2)
              cout<<"P"<<p[i].pno;
        }
       cout<<"|";
    }
     cout<<endl;

     cout<<0;

     for(int i=0;i<n;i++)
    {          for(int j=0;j<p[i].bt;j=j+1)
        {  cout<<" ";
            if(j==(p[i].bt/2))
                cout<<"   ";
        }
       cout<<p[i].ct;
    }
    cout<<endl;

}

void showtable(int n)
{   cout<<endl<<"\e[1mPROCESS TABLE\e[0m"<<endl<<endl;;
    cout<<"PNo.\tAT\tBT\tCT\tTAT\tWT"<<endl;
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

sort(p,p+n,compareAT);

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
