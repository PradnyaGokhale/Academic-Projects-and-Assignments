#include<iostream>
#include<string.h>
using namespace std;

class dict
{
	char word[20],mean[50];
	dict *left,*right;
	int ht;
public:

	dict* create(dict *root);
	dict* insert(dict *root,char word[],char mean[]);
	void display(dict *);
	int height(dict *);
   	dict* rotateright(dict *);
   	dict* rotateleft(dict *);
        int BF(dict *);
        dict* deletion(dict *,char *);
   	dict* RR(dict*);
   	dict* LL(dict*);
   	dict* RL(dict*);
   	dict* LR(dict*);
};

dict* dict::create(dict *root)
{
	int n,i;
	char w[20],m[50];
	cout<<"\nENTER TOTAL NUMBER OF WORDS:";
	cin>>n;
	for(i=0;i<n;i++)
	{
		cout<<"\nENTER WORD "<<i+1<<" : ";
		cin>>w;
		cout<<"\nENTER MEANING : ";
		cin>>m;
		root=insert(root,w,m);

	}
	return root;
}

dict* dict::insert(dict *root,char w[],char m[])  
{
    if(root==NULL)									
    {
    	root=new dict;
    	strcpy(root->word,w);
    	strcpy(root->mean,m);
    	root->left=NULL;
    	root->right=NULL;
    	return root;
    }
    else
    {
    if(strcmp(w,root->word)>0)
    {
    	root->right=insert(root->right,w,m);   // For insertion into the right subtree
    	if(BF(root)==-2)						// balanced factor is -2 so the tree needs to be balanced
    	{
    		if(strcmp(w,root->word)>0)
    			root=RR(root);					// RR rotation is done in order to balance it.
    		else
    			root=RL(root);					// Otherwise RL rotation is done.
    	}

    }
    else
    {
    	if(strcmp(w,root->word)<0)
    	{
    	    root->left=insert(root->left,w,m);			// For insertion into the left subtree
    		if(BF(root)==2)								// Balanced factor is 2 so the tree needs to be balanced.
		
    		{											
    			if(strcmp(w,root->word)<0)				
    				root=LL(root);						// LL rotation is done to balance it.
    			else
    				root=LR(root);						// LR rotation is done.
    		}
    	}

    }
  }
root->ht=height(root);
return root;
}

void dict::display(dict* root)
{
	if(root!=NULL)
	{
		display(root->left);								// The display is done in inorder traversal.
		cout<<"\nNODE IS :"<<root->word<<"-"<<root->mean;
		display(root->right);
	}
}


int dict::height(dict *root)
{
	int lh,rh;
	if(root==NULL)
		return 0;						// If there is no root, the height is zero.
	if(root->left==NULL)
		lh=0;							
	else
		lh=1+root->left->ht;			// If there is a left child, height increases by 1
	if(root->right==NULL)
		rh=0;
	else
		rh=1+root->right->ht;			// If there is a right child, height increases by 1

	if(lh>rh)
	{
		return(lh);
	}
	else
	{
		return(rh);
	}

}

dict* dict::rotateright(dict *x)
{
	dict *y;
	y=x->left;						// Steps of rotating right
	x->left=y->right;
	y->right=x;
	x->ht=height(x);
	y->ht=height(y);
	return(y);
}

dict* dict::rotateleft(dict *x)
{
	dict *y;
	y=x->right;
	x->right=y->left; 				// Steps for rotating left
	y->left=x;
	x->ht=height(x);
	y->ht=height(y);
	return(y);
}
int dict::BF(dict *root)
{
	int lh,rh;				// Balanced factor is found out.
	if(root==NULL)
		return(0);
	if(root->left==NULL)
		lh=0;
	else
		lh=1+root->left->ht;
	if(root->right==NULL)
	  rh=0;
	else
		rh=1+root->right->ht;
	int z=lh-rh;			// BF is given by subtracting right height from left height.
	return(z);
}

dict* dict:: deletion(dict *T,char *w)
{
	dict *p;
	if(T==NULL)
	{
		cout<<"\nWORd NOT FOUND!";
		return T;
	}
	else
	if(strcmp(w,T->word)>0)				// Different rotations need to be done after deleting in order to maintain the balamced factor
	{
	    T->right=deletion(T->right,w);
	    if(BF(T)==2)
	    {
	    	if(BF(T->left)>=0)
	    		T=LL(T);
	    	else
	    		T=LR(T);
	    }

	}
	else
	if(strcmp(w,T->word)<0)
		{
			T->left=deletion(T->left,w);
			if(BF(T)==2)
				    {
				    	if(BF(T->right)<=0)
				    		T=RR(T);
				    	else
				    		T=RL(T);
				    }
		}
	else
	{
     if(T->right!=NULL)
     {
    	 p=T->right;
    	 while(p->left!=NULL)
    		 p=p->left;
    	 strcpy(T->word,p->word);
    	 strcpy(T->mean,p->mean);
    	 T->right=deletion(T->right,p->word);
    	 if(BF(T)==2)
    	 {
    		 if(BF(T->left)>=0)
    			 T=LL(T);
    		 else
    			 T=LR(T);
    	 }
     }
     else
    	 return(T->left);
	}
	T->ht=height(T);
	return(T);
}


dict* dict::RR(dict *T)
{
	T=rotateleft(T);			
	return(T);
}
dict* dict::LL(dict *T)
{
	T=rotateright(T);
	return(T);
}
dict* dict::LR(dict *T)
{
	T->left=rotateleft(T->left);
	T=rotateright(T);
	return(T);
}
dict* dict::RL(dict *T)
{
	T->right=rotateright(T->right);
	T=rotateleft(T);
	return(T);
}

int main()
{
	int ch;
	dict d,*root;
	root=NULL;
	char w[20],m[50];
	cout<<"\n ********************************||DICTIONARY||*************************************";

	do{
		cout<<"\n\n MENU:";
		cout<<"\n1.CREATE \n2.INSERT \n3.DELETE \n4.DISPLAY \n5.EXIT";
		cout<<"\nENTER YOUR CHOICE :";
		cin>>ch;

		switch(ch) 											// switch case is made so user can select with ease.
		{
		case 1: root=d.create(root);
		break;

		case 2: cout<<"\nENTER WORD :";
		        cin>>w;
		        cout<<"\nENTER MEANING :";
		        cin>>m;
		        root=d.insert(root,w,m);
		        break;

		case 3: cout<<"\nENTER WORd TO DELETE :";
		        cin>>w;
		        root=d.deletion(root,w);
		        break;


		case 4: d.display(root);
		break;


		case 5: break;
		default:cout<<"\n IVALID CHOICE!!!!";

		}
	}
	while(ch!=5);
	return 0;
}
