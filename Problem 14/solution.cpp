#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<map>
#include<vector>
#include<list>
#include<set>
#include<queue>
#include<numeric>
#include<sstream>
#include<string>
#include<cmath>
#include<algorithm>
#include<stack>
using namespace std;

//#define inf 1001001010010010100ll
#define pb      push_back
#define mp      make_pair
#define EPS     1e-9
#define ll long long
#define vi vector<int>
#define pii pair<int,int>
#define fi first
#define se second
#define inf 1000000001
#define mod 1000000007
#define N 1000005
int b[N*8],ans[N],c[N],n;
void solve(int n)
{
 int pow=1,i,l,j;
 while(pow<n)pow<<=1;
 pow<<=3;
 b[0]=0;
 for(i=1;i<pow;i++)
 b[i]=(b[i>>1]+i&1)%2;
 int start=0;
 for(l=1;l<=n;l++)
 {
    if(l>=2&&ans[l-2]==-1){ans[l-1]=-1;continue;}
    for(i=start;i<(pow>>1);i++)
    {
     for(j=0;j<l;j++)
     {
      if(c[j]!=b[i+j])break;
      if(j==l-1)
      {
       ans[l-1]=i;
       start=i+1;
       l++;
      }
      if(l>n)break;
     }
     if(l>n)break;
    }
    if(i==(pow>>1))ans[l-1]=-1;
    if(start==3*(pow>>3))start=5*(pow>>3);
 }
 for(i=0;i<n;i++)printf("%d ",ans[i]);
 puts("");
}
int main()
{
    //freopen("in.txt","r",stdin);
    int T,i,j,q,k,m;
    scanf("%d",&T);
    while(T--)
    {
     scanf("%d",&n);
     for(i=0;i<n;i++)scanf("%d",&c[i]);
     solve(n);
    }
    return 0;
}