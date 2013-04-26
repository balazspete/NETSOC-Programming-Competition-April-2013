#include<stdio.h>
int main()
{
    int t;
    scanf("%d",&t);
    while(t--)
    {
        int n,x,i,min,sum = 0;
        int a[105]={0};
        scanf("%d%d",&n,&x);
        for(i = 0; i < n; i ++)
        scanf("%d",&a[i]);
        min = a[0];
        for(i = 0; i < n; i ++)
        {
            if(a[i]<min)
            min = a[i];
            sum+=a[i];
        }
        if(sum%x == 0 || sum%x < min)
        printf("%d\n",sum/x);
        else
        printf("-1\n");
    }
    return 0;
}