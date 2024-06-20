//Simple Binary Tree Implementation
#include <iostream>
using namespace std;

class node
{
public:
    int data;
    node *left, *right;
    node()
    {
        data = 0;
        left = NULL;
        right = NULL;
    }
};

class btree
{
public:
    int flag=0;
    node *root;
    btree()
    {
        root = NULL;
    }
    void create()
    {

        int i, n, ch;

        cout << "Enter total no. of nodes: ";
        cin >> n;
        for (i = 0; i < n; i++)
        {
            node *newnode = new node;
            cout << "Enter the element: ";
            cin >> ch;

            newnode->data = ch;
            if (root == NULL)
            {
                root = newnode;
            }
            else
            {
                insert(root, newnode);
            }
        }
    }

    void insert(node *temp, node *newnode)
    {
        if (temp->data < newnode->data)
        {
            if (temp->right == NULL)
            {
                temp->right = newnode;
            }
            else
            {
                insert(temp->right, newnode);
            }
        }
        else
        {
            if (temp->left == NULL)
            {
                temp->left = newnode;
            }
            else
            {
                insert(temp->left, newnode);
            }
        }
    }
    

    
    void min_value(node *temp)
    {
        if (temp != NULL)
            while (temp->left != NULL)
            {
                temp = temp->left;
            }
        cout << temp->data;
    }
    

    void find(node *root, int key)
    {
        if (root != NULL)
        {
            if (key == root->data)
                cout << "Key found" << endl;

            else if (key < root->data)
                find(root->left, key);
            else
                find(root->right, key);
        }
        else{
            cout<<"Key Not Found.";
        }
    }

    int depth(node *root)
    {
        int hleft, hright;
        if (root == NULL || ((root->left == NULL) && (root->right == NULL)))
            return (0);
        else
        {
            hleft = depth(root->left);
            hright = depth(root->right);
        }
        if (hleft > hright)
        {
            return (hleft + 1);
        }
        else
        {
            return (hright + 1);
        }
    }

    void inorder(node *temp)
    {
        if (temp != NULL)
        {
            inorder(temp->left);
            cout << temp->data << "\t";
            inorder(temp->right);
        }
    }
    
    void preorder(node *temp)
    {
        if (temp != NULL)
        {
            cout << temp->data << "\t";
            preorder(temp->left);
            preorder(temp->right);
        }
    }
    
    void postorder(node *temp)
    {
        if (temp != NULL)
        {
            postorder(temp->left);
            postorder(temp->right);
            cout << temp->data << "\t";
        }
    }

    void disp_in()
    {
        int ch, choice;
        cout << "\n\t1-Inorder\n\t2-Preorder\n\t3-Postorder\n";
        cout << "\nEnter your choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            inorder(root);
            break;

        case 2:
            preorder(root);
            break;

        case 3:
            postorder(root);
            break;

        default:
            cout << "\nInvalid choice!!!";
            break;
        }
}
    
    void swap(node* root)
    {
        node* temp;
        if(root!=NULL)
        {
            swap(root->left);
            swap(root->right);
            node*temp=root->left;
            root->left=root->right;
            root->right=temp;
            }
    }
};

int main()
{
    btree v;
    int n;
    char ch;
    int value;

    do
    {
        cout << "\n\n## MENU ##\n\n1)Insert";
        cout << "\n2)Number of nodes in longest path from root\n3)Display\n4)Find minimum value\n5)Swap the elements\n6)Search the Elements\nEnter your choice:";
        cin >> n;
        switch (n)
        {
        case 1:
            v.create();
            cout << "Binary tree constructed successfully\n";
            break;
        case 2:
            cout << "Number of nodes in longest path from root : " << (v.depth(v.root)+1)<< endl;
            break;
        case 3:
            cout << "Inorder of tree" << endl;
            v.disp_in();
            break;
        case 4:
            cout << "Minimum value is:"<<endl;
            v.min_value(v.root);
            break;
        case 5:
            cout<<" Swap Elements:"<<endl;
            v.swap(v.root);
            v.inorder(v.root);
            break;
        case 6:
            cout<<"Enter Elements to be searched:";
            cin>>value;
            v.find(v.root,value);
            break;
        }
        cout << "\n\nContinue?(Y/N)" << endl;
        cin >> ch;
    } while (ch == 'Y' || ch == 'y');

    return 0;
}
