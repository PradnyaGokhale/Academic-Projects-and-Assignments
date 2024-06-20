#include<iostream>
#include<ctime>
#define MAX 10
using namespace std;
class airport
{
string city_name[MAX];
int dist [MAX][MAX];
public: int n;
void input();
void display();
airport();
};
airport::airport()
{
n = 0;
for(int i=0 ; i<MAX ; i++)
{
for(int j=0 ; j<MAX ; j++)
dist[i][j] = 0;

}
for(int i=0 ; i<MAX ; i++)
{
city_name[i]="ABC";
}
}
void airport::input()
{
int k;
cout<<"\nENTER NUMBER OF CITIES:";
cin>>n;
for(k=0;k<n;k++)
{ cout<<"\nENTER CITY NAME:";
cin>>city_name[k];
}
for (int i=0;i<n;i++)
{
for(int j=0;j<n;j++)
{
cout << "\nENTER THE DISTANCE BETWEEN " <<city_name[i]<< " TO "

<<city_name[j]<<":\n";;

cin >> dist[i][j];
dist[j][i] = dist[i][j];
}

}
}
void airport :: display()
{

cout<<"\t";
for(int k=0;k<n;k++)
{
cout<<city_name[k]<<"\t";
}
cout<<endl;
for(int i=0 ; i<n ; i++)
{

cout <<city_name[i] <<"\t";
for(int j=0 ; j<n ; j++)
{
cout<<dist[i][j] << "\t";
}
cout << "\t";
cout << "\n";

}

}
main()
{
airport obj1;
obj1.input();
obj1.display();
time_t begin,end;
double time_req;
time (& begin);
time(& end);
time_req=difftime(end,begin);
cout<<"\nTIME REQ. IS:"<<time_req;
}
/*Output:
ENTER NUMBER OF CITIES:2
ENTER CITY NAME:pune
ENTER CITY NAME:mumbai
ENTER THE DISTANCE BETWEEN pune TO pune:
0
ENTER THE DISTANCE BETWEEN pune TO mumbai:
250
ENTER THE DISTANCE BETWEEN mumbai TO pune:
250
ENTER THE DISTANCE BETWEEN mumbai TO mumbai:
0
pune mumbai
pune 0 250

mumbai 250 0

TIME REQ. IS:3*/
