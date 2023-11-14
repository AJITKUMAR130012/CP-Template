#include<bits/stdc++.h>
#include<iostream>
using namespace std;

void build_tree(int *tree, vector<int> &v, int s, int e, int idx)
{
    if(s==e)
    {
        tree[idx]=v[s];
        return ;
    }
    int m= s+(e-s)/2;
    build_tree(tree, v, s, m, 2*idx);
    build_tree(tree, v, m+1, e, 2*idx+1);
    tree[idx]=min(tree[2*idx], tree[2*idx+1]);
    return ;
}


int query(int *tree, int ss, int se, int qs, int qe,int idx)
{
    if(qs<=ss and qe>=se)
    {
        return tree[idx];
    }
    if(qs>se or ss>qe)
    {
        return INT_MAX;
    }
    int m=ss+(se-ss)/2;
    int left=query(tree, ss, m, qs, qe, 2*idx);
    int right=query(tree, m+1,se, qs, qe, 2*idx+1);
    return min(left, right);
}


int main()
{
    int n;
    cin>>n;
    vector<int> v(n,0);
    int *tree= new int[4*n+1];
    for(int i=0;i<n;i++)
    {
        cin>>v[i];
    }
    build_tree(tree, v,0,n-1,1);
    int q;
    cin>>q;
    while(q--)
    {
        int l,r;
        cin>>l>>r;
        cout<<query(tree,0,n-1,l,r,1)<<endl;
    }

}