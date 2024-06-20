/* Following is the code is of a pizza parlour
where FIFO is applied to receive and deliver orders.*/
#include<iostream>
using namespace std;
class queue
{
	int front,rear,a;   // a is maximum order to be placed in 					    // queue
	int arrq[20];      // array of queue
	public:
		queue()
		{
		   	a=0;
			front=-1;
			rear=-1;
		}
		void add();
		void deliver_order();
		int qempty();
		int qfull();
		void display_first();
		void display_last();
};
int queue :: qfull()
{
	if(front==(rear+1)%a)
		return 1;
	else
		return 0;
}
int queue :: qempty()
{
	if(front==-1)
		return 1;
	else
		return 0;
}
void queue :: add()
{
    if(a==0)
    {
        cout<<"Enter maximum number orders to be placed in a day : ";
        cin>>a;
    }
    int order,ans,order_no,count;
    count=1;    // order number
	do
    {
        if(qfull()==1)
        {
            cout<<"Orders are full can't place your your order !!\n";
            break;
        }
        else
        {
            cout<<"Pizza Types :\n1.A\n2.B\n3.C\n4.D\n";
            cout<<"Enter your order for : ";
            cin>>order;
            cout<<"\nYour Order No. is "<<count<<"\n";
            if(front==-1) // if empty
            {
                rear=front=0;
                count=1;
                arrq[rear]=order;
            }
            else
            {
                rear=(rear+1)%a;
                arrq[rear]=order;
            }
            count++;
            cout<<"Do you wish to add another order(1=yes/0=no).... : ";
            cin>>ans;
        }

    }
    while(ans==1);
}
void queue :: deliver_order()
{
	if(qempty()==1)
		cout<<"All orders are delivered !!\n";
	else
	{
		int x=arrq[front];
		cout<<"Order for "<<x<<" no. pizza delivered\n";
		if(front==rear)
			front=rear=-1;
		else
			front=front+1%a;
	}
}
void queue :: display_first()
{
	if(qempty()==1)
		cout<<"\nAll orders are delivered !!\n";
	else
	{
		cout<<"\nFirst Order is for "<<arrq[front]<<" no. pizza delivered\n";
	}
}
void queue :: display_last()
{
	if(qempty()==1)
		cout<<"\nAll orders are delivered !!\n";
	else
	{
		cout<<"\nLast Order is for  "<<arrq[rear]<<" no. pizza\n";
	}
}
int main()
{
	queue q;
	int ch;
	char ans;
	do
	{
		cout<<"WELCOME TO PIZZA PARLOR \n1.Place Your Order.\n2.Display First Order\n3.Display Last Order.\n4.Deliver Order.\n";
		cout<<"\nEnter your choice : ";
		cin>>ch;
		switch(ch)
		{
			case 1 :q.add();
				break;
			case 2 :q.display_first();
				break;
			case 3 :q.display_last();
				break;
			case 4 :q.deliver_order();
                break;
			default : cout<<"Invalid  choice!!\n";
		}
		cout<<"Do you wish to continue..(y/n) : ";
		cin>>ans;
	}
	while(ans=='y'||ans=='Y');
	return 0;
}
