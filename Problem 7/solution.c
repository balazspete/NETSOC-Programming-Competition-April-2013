#include<stdio.h>
long long int dist(long long int n)
{
    long long int sol;
    if (n<0)
    {
        return 0;
    }
    else
sol=(((n+3)*(n+2)*(n+1))/6);
    return sol;   //for all solns such that a+b+c<=n
}
int main()
{
    long long int N,A,B,C,testcase,i;
    long long int soln;
    scanf("%lld",&testcase);
    for(i=0;i<testcase;i++)
    {
        scanf("%lld%lld%lld%lld",&N,&A,&B,&C);
        soln=dist(N)-dist(N-A-1)-dist(N-B-1)-dist(N-C-1)+dist(N-A-B-2)+dist(N-B-C-2)+dist(N-A-C-2)-dist(N-A-B-C-3);
        printf("%lld\n",soln);
    }
    return 0;
}