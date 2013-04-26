#include<stdio.h>
#include<math.h>
int arr[100];
long gcd(long a,long b)
{
     if (b == 0)
       return a;
    else
       return gcd(b, a % b);
}
int main()
{
    int t,i=0;
    scanf("%d",&t);
    while(t-->0)
    {
        int n;
        scanf("%d",&n);

        for(i=0;i<n;i++)
        {
            scanf("%d",&arr[i]);
        }
        int div=arr[0];
        for(i=1;i<n;i++)
        {
            div = gcd(arr[i],div);
        }
        for(i=0;i<n;i++)
        {
            printf("%d ",arr[i]/div);
        }
        printf("\n");
    }
}