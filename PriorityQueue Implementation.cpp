//Implementation of Job Queue
#include<iostream>
using namespace std;

class job            //class declaration for node
{
    int num;        //store serial no. of job
    job *next;        //points toward next node of job queue
public:
    job()
    {   num=0;
        next = NULL;
    }
    void setnum(int x)
    {
        num = x;
    }
    void setnext(job *y)
    {
        next = y;
    }
    int getnum()
    {
        return num;
    }
    job* getnext()
    {
        return next;
    }
};
class order
{
    job *first,*last,*temp1;    //first is front of queue and last is rear of queue, temp1 is taken for verification of data inside queue
public:
    order()
    {
        first = NULL;
        last = NULL;
        temp1=NULL;
    }
    void create();
    void add();
    void del();
    void display();
};

void order::create()        //It creates the initial queue
{
    char ans;
    do
    {
        int n;
        cout<<"\nEnter the job number: ";
        cin>>n;
        job *nn;
        nn = new job(); // new node allocation
        nn->setnum(n);
        if(first == NULL)
        {
            first = nn;
            last = nn;
            cout<<"\nFirst job inserted";
        }
        else
        {
            last->setnext(nn);
            last=last->getnext();
            cout<<"\nJob inserted.";
        }
        cout<<"\nDo you want to add another job, press Y :";
        cin>>ans;
    }while(ans == 'y' || ans == 'Y');
}

void order::add()        //Add job in queue from Rear
{
    int n;
    job *nn;
    nn = new job();
    cout<<"\nEnter the job number: ";
    cin>>n;
    nn->setnum(n);
    if(first == NULL)
    {
        first = nn;
        last = nn;
    }
    else
    {
        last->setnext(nn);
        last=last->getnext();
    }
    cout<<"\nJob Added Successfully";
}
void order::del()        //Remove job from queue from Front
{
    if(first == NULL)
    {
        cout<<"\nJob Queue is Empty";
    }
    else
    {
        job *temp;
        temp = first->getnext();
        delete(first);
        first = temp;
    }
    cout<<"\nFirst Job Removed Successfully";
}
void order::display()        //for verification(logically can't be performed) of data available inside queue
{
    cout<<"\nJob Queue :\n";
    
    temp1 = first;
    cout<<temp1->getnum()<<" ";
    while(temp1->getnext()!= NULL)
    {
        temp1 = temp1->getnext();  // temp1=temp1->next;
        cout<<temp1->getnum()<<" "; // cout<<temp1->num;
    }
    cout<<endl;
}
int main()            //main function
{
    char ans;
    order l;
    do
    {
        int choice;
        cout<<"\nChoice List: \n";            //choice list
        cout<<"\n\t1.Create Job Queue\n"<<"\t2.Insert Job in Job Queue\n"<<"\t3.Remove First Job from Job Queue\n"<<"\t4.Display Job Queue\n"<<"\t5.Exit\n";
        cout<<"Enter Choice : ";
        cin>>choice;
        cout<<endl;
        
        switch(choice)
        {
            case 1:
                l.create();
                break;
            case 2:
                l.add();
                break;
            case 3:
                l.del();
                break;
            case 4:
                l.display();
                break;
            case 5:
                exit(0);
            default:
                cout<<"\n\tInvalid option Selected, Please try Again\n";
                break;
        }
        cout<<"\nTo continue with this Queue, Press Y : ";
        cin>>ans;
        cout<<endl;
    }while(ans == 'y' || ans == 'Y');
    return 0;
}
