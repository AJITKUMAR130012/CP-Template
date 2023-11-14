#include<iostream>
#include<bits/stdc++.h>
using namespace std;

int lazy[1000]={0};


void build_tree(vector<int> &v, int *tree, int s, int e, int idx)
{
    if(s==e)
    {
        tree[idx]=v[s];
        return;
    }
    int m=s+(e-s)/2;
    build_tree(v,tree,s,m,2*idx);
    build_tree(v,tree,m+1,e,2*idx+1);
    tree[idx]= min(tree[2*idx], tree[2*idx+1]);

}
void lazy_update(int *tree, int qs, int qe, int ss, int se, int val, int idx)
{ 

    //Update the lazy value
    if(lazy[idx]!=0)
    {
        tree[idx]+=lazy[idx];
        if(ss!=se)
        {
            lazy[2*idx]+=lazy[idx];
            lazy[2*idx +1]+=lazy[idx];
        }
        lazy[idx]=0;
    }
    // No overlap
    if(qs> se or ss >qe)
    {
        return;
    }
    // fully overlap
    if(ss>=qs and qe>=se)
    {
        tree[idx]+=val;
        if(ss!=se)
        {
            lazy[2*idx]+=val;
            lazy[2*idx+1]+=val;
        }
        return;
    }
    // partial overlap
    int m=ss+ (se-ss)/2;
    lazy_update(tree,qs,qe, ss, m, val, 2*idx);
    lazy_update(tree, qs, qe, m+1, se, val, 2*idx+1);
    tree[idx] = min(tree[2*idx], tree[2*idx+1]);
    return;

}


int lazy_range(int *tree, int qs, int qe, int ss, int se, int idx)
{
    if(lazy[idx]!=0)
    {
        tree[idx]+=lazy[idx];
        if(ss!=se)
        {
            lazy[2*idx]+=lazy[idx];
            lazy[2*idx+1]=lazy[idx];
        }
        lazy[idx]=0;
    }
    // No overlap
     if(qs> se or ss >qe)
    {
        return INT_MAX;
    }

      // fully overlap
    if(ss>=qs and qe>=se)
    {
        
        return tree[idx];
    }
    int m=ss+(se-ss)/2;
    int left=lazy_range(tree,qs, qe, ss, m, 2*idx);
    int right=lazy_range(tree, qs, qe, m+1,se,2*idx+1);
    return min(left,right);

}

int main()
{
    int n;
    cin>>n;
    vector<int> v(n,0);

    for(int i=0;i<n;i++) cin>>v[i];
    int *tree=new int[4*n+1];
    build_tree(v,tree,0, n-1,1);
    int q;
    cin>>q;
    while(q--)
    {
                int l,r;
        cin>>l>>r;
        cout<<lazy_range(tree,l,r,0,n-1,1)<<endl;
        int qs,qe;
        cin>>qs>>qe;
        int val;
        cin>>val;
        lazy_update(tree,qs, qe, 0, n-1,val,1);

    }
    for(int i=1; i<=13; i++)
    {
        cout<<tree[i]<<" ";  
    }
    return 0;

}
