#include<iostream>
#include<bits/stdc++.h>
using namespace std;


void build_tree(int *tree, vector<int> &v, int s, int e, int idx)
{
    if(s==e)
    {
        tree[idx]=v[s];
        return ;
    }
    int m=s+(e-s)/2;
    build_tree(tree,v, s,m,2*idx);
    build_tree(tree, v,m+1,e,2*idx+1);
    tree[idx]=min(tree[2*idx] , tree[2*idx+1]);
    return;
}

int query(int *tree, int ss, int se, int qs, int qe, int idx)
{
    if(ss>=qs  and qe>=se)
    {
        return tree[idx];
    }
    if(qs>se or ss>qe)
    {
        return INT_MAX;
    }
    int m=ss+(se-ss)/2;
    int left= query(tree, ss, m, qs, qe, 2*idx);
    int right=query(tree, m+1, se, qs, qe, 2*idx+1);
    return min(left,right);
}
void point_update(int *tree, int p, int s, int e, int val, int idx)
{
    if(p<s or p>e) return;
    int m=s +(e-s)/2;
    if(s==e and p==s)
    {
        tree[idx] =tree[idx]+val;
        return;
    }
    // if(p>s and p<e)
    // {

    // }
    point_update(tree,p,s,m, val,2*idx);
    point_update(tree,p,m+1, e, val, 2*idx+1);
    tree[idx]=min(tree[2*idx], tree[2*idx+1]);
    return;
}

int main()  
{
    int n;
    cin>>n;
    vector<int> v(n,0);
    for(int i=0;i<n;i++) cin>>v[i];
    int *tree=new int[4*n+1];
    build_tree(tree,v,0,n-1,1);
    int p;
    cin>>p;
    int val;
    cin>>val;
    point_update(tree,p,0,n-1,val,1);
    for(int i=1; i<=13; i++)
    {
        cout<<tree[i]<<" ";
    }
    cout<<endl;
    int q;
    cin>>q;          
    while(q--)
    {
        int l,r ;
        cin>>l>>r;
        cout<<query(tree,0,n-1, l,r,1)<<endl;
    }
    
    return 0;
}