#include<iostream>
using namespace std;
#define INT_MAX 100
int sum(int freq[], int i, int j);
int optCost(int freq[], int i, int j)
{
if (j < i)
return 0;
if (j == i)
return freq[i];

int fsum = sum(freq, i, j);

int min = INT_MAX;
for (int r = i; r <= j; ++r)
{
int cost = optCost(freq, i, r-1) +
optCost(freq, r+1, j);
if (cost < min)
min = cost;
}
return min + fsum;
}
int optimalSearchTree(int keys[], int freq[], int n)
{
return optCost(freq, 0, n-1);
}
Given sequence k = k1 <k2 < ... <kn of n sorted keys, with a search probability pi for each key ki . Build
the Binary search tree that has the least search cost given the access probability for each key
int sum(int freq[], int i, int j)
{
int s = 0;
for (int k = i; k <=j; k++)
s += freq[k];
return s;
}

int main()

{
int keys[] = {10, 12, 20};
int freq[] = {34, 8, 50};
int n = sizeof(keys)/sizeof(keys[0]);
cout<<"Cost of Optimal BST is "<<
optimalSearchTree(keys, freq, n);
return 0;
}
/*Output:
Cost of optimal BST is:142*/
