#include <iostream>
#include <bits/stdc++.h>
using namespace std;
#define INFINITY __builtin_inf()

class segmentT{
    public:
    void buildTree(int ,int ,int);
    int queries(int,int,int,int,int);
    void update();

};

int segTree[400001],arr[100001];

void buildTree(int str,int end,int idx)
{
    if(str == end)
    {
        segTree[idx] = arr[str];
        return;
    }
    int mid = (str+end)/2;
    buildTree(str,mid,2*idx);
    buildTree(mid+1,end,2*idx+1);

    segTree[idx] = min(segTree[2*idx],segTree[2*idx+1]);
}
int queries(int str,int end,int qstr,int qend,int idx)
{
    if(str>qend || end <qstr)
    {
        return INT_MAX;
    }
    if(str>=qstr && end<=qend)
    {
        return segTree[idx];
    }
    int mid = (str + end)/2;
    int left = queries(str,mid,qstr,qend,2*idx);
    int right = queries(mid+1,end,qstr,qend,2*idx+1);

    return min(left,right);
}
void update(int str,int end,int idx,int queI,int val)
{
    if(str == end)
    {
        segTree[idx] = val;
    }
    int mid = (str+end)/2;
    update(str,end,2*idx,queI,val);
    update(str,end,2*idx+1,queI,val);

    segTree[idx] = min(segTree[2*idx],segTree[2*idx+1]);
}
int main()
{
    int n,q,l,r;
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>arr[i];
    }
    buildTree(1,n,1);
    cin>>q;
    while(q--)
    {
        cin>>l>>r;
        cout<<queries(1,n,l+1,r+1,1)<<endl;
    }
    return 0;
}