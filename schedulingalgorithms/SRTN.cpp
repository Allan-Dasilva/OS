#include<iostream>

using namespace std;

struct process
{
    int pno,at,bt,ct,tat,wt,remaining_time;
}*p;

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



}