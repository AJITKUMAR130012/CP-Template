#include<iostream>
#include<bits/stdc++.h>
using namespace std;

void range_update(int *tree, int ss, int se, int qs, int qe, int idx, int val)
{
     if(qs>se or ss>qe)
     {
        return;
     }
     if(ss==se)
     {
        tree[idx] = tree[idx] + val;
        return;
     }
     int m= ss+(se-ss)/2;
     range_update(tree,ss, m,qs, qe, 2*idx,val);
     range_update(tree,m+1,se, qs, qe, 2*idx+1, val);
     tree[idx] = min(tree[2*idx], tree[2*idx +1]);
}


void build_tree(vector<int> &v, int *tree, int s, int e, int idx)
{
    if(s==e)
    {
        tree[idx]=v[s];
        return;
    }
    int mid=s+(e-s)/2;
    build_tree(v, tree, s, mid, 2*idx);
    build_tree(v,tree, mid+1, e, 2*idx+1);
    tree[idx]= min(tree[2*idx], tree[2*idx+1]);
}

int main()
{
    int n;
    cin>>n;
    vector<int> v(n,0);
    for(int i=0;i<n;i++) cin>>v[i];
    int *tree= new int[4*n+1];
    build_tree(v, tree,0, n-1, 1);
    int l,r;
    cin>>l>>r;
    int val;
    cin>>val;
    range_update(tree, 0,n-1, l,r,1,val);
    for(int i=1;i<=13; i++)
    {
        cout<<tree[i]<<" ";
    }
    return 0;
}