#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;
int i,n,ans,t,k,j;
int a[200000],u[200000],b[200000],op[200000],ed[200000],low[200000];
bool cmp(int i,int j)
{
  if (a[i]!=a[j]) return a[i]<a[j];
  return i<j;
}
int main()
{
  scanf("%d\n",&t);
  for (;t;t--) {
    scanf("%d",&n);
    for (i=1;i<=n;i++) scanf("%d",&a[i]),u[i]=i;
    sort(u+1,u+n+1,cmp);
    u[n+1]=0,a[0]=-1073741819;
    for (i=1,k=0;i<=n+1;i++)
      if (a[u[i-1]]!=a[u[i]]) b[i]=++k,op[k]=i,ed[k-1]=i-1;
    ans=1,low[1]=u[ed[1]];
    for (i=2;i<=k-1;i++) {
      for (j=op[i];j<=ed[i] && u[j]<low[i-1];j++) ;
      if (j==op[i]) low[i]=u[ed[i]];
      else ans++,low[i]=u[j-1];
    }
    for (k=0;(1<<k)<ans;k++) ;
    printf("%d\n",k);
  }
  return 0;
}