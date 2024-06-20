#include<bits/stdc++.h>
using namespace std;

class heap
{
    int heap1[20],heap2[20],x,n1,i;
    public:
    heap()
    {
        heap1[0]=0;
        heap2[0]=0;
    }
    void datain();
    void insert1(int heap1[],int);
    void upadj1(int heap1[],int);
    void insert2(int heap2[],int);
    void upadj2(int heap2[],int);
    void minmax();
};

void heap::datain()
{
    cout<<"Enter the number of students: ";
    cin>>n1;
    cout<<"Enter the marks:"<<endl;
    for (i=1;i<=n1;i++)
    {
        cout<<"Enter the marks of student "<<i<<" :";
        cin>>x;
        insert1(heap1,x);
        insert2(heap2,x);
    }
}

void heap::insert1(int heap1[20],int x)
{
    int n;
    n=heap1[0];
    heap1[n+1]=x;
    heap1[0]=n+1;
    upadj1(heap1,n+1);
}

void heap:: upadj1(int heap1[20],int i)
{
    int temp;
    while(i>1&&heap1[i]>heap1[i/2])
    {
        temp=heap1[i];
        heap1[i]=heap1[i/2];
        heap1[i/2]=temp;
        i=i/2;
    }
}

void heap:: insert2(int heap2[20],int x)
{
    int n;
    n=heap2[0];
    heap2[n+1]=x;
    heap2[0]=n+1;
    upadj2(heap2,n+1);
}

void heap:: upadj2(int heap2[20],int i)
{
    int temp1;

    while (i>1&&heap2[i]<heap2[i/2])
    {
        temp1=heap2[i];
        heap2[i]=heap2[i/2];
        heap2[i/2]=temp1;
        i=i/2;
    }
}

void heap::minmax()
{
    cout<<"max marks:"<<heap1[1]<<endl;
    cout<<"min marks:"<<heap2[1]<<endl;
}

int main()
{
    heap h;
    h.datain();
    h.minmax();
    return 0;
}
