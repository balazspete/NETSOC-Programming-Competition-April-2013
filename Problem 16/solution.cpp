#include <stdio.h>


    #define MAX 105
    #define OST 1337

    int s[MAX][7];
    int f[MAX][7];
    int ost[6]={1,3,2,6,4,5};
    char niz[MAX];

    int main()
    {
    int i,j,m,k,t,u,d,v;
    s[1][5]=s[1][6]=1;
    for(k=1;k<MAX-1;k++)
    for(m=0;m<7;m++)
    s[k+1][m]=s[k][m]^s[k][(m+3*ost[k%6])%7]^s[k][(m+4*ost[k%6])%7]^s[k][(m+5*ost[k%6])%7]^s[k][(m+6*ost[k%6])%7];
    for(m=0;m<7;m++)
    {
    u=0;
    t=1;
    for(i=0;i<10;i++)
    {
    if (i==7||(i+m)%7==0)
    t=-t;
    u+=t;
    //
    if (u<0)
    u+=OST;
    if (u>=OST)
    u-=OST;
    //
    }
    f[1][m]=u;
    }

    for(k=1;k<MAX-1;k++)
    for(m=0;m<7;m++)
    {
    u=0;
    for(i=0;i<10;i++)
    {
    if (i==7)
    continue;
    t=1;
    for(j=0;j<i;j++)
    if (j!=7)
    t^=s[k][(m+j*ost[k%6])%7];
    u+=(2*t-1)*f[k][(m+i*ost[k%6])%7];
    if (u>=OST)
    u-=OST;
    if (u<0)
    u+=OST;
    }
    f[k+1][m]=u;
    }


    scanf("%d",&v);

    while (v--)
    {
    scanf("%s",niz);
    for(d=0;niz[d];d++);
    if (d>MAX)
    for(;;);
    u=-1;
    t=-1;
    m=0;
    for(i=0;i<d;i++)
    {
    if (i==d-1)
    {
    for(j=0;j<niz[i]-'0';j++)
    {
    if (j==7||(j+m)%7==0)
    t=-t;
    u+=t;
    if (u<0)
    u+=OST;
    if (u>=OST)
    u-=OST;
    }
    continue;
    }
    for(j=0;j<niz[i]-'0';j++)
    {
    if (j==7)
    continue;
    u+=t*f[d-i-1][(m+j*ost[(d-i-1)%6])%7];
    t*=1-2*s[d-i-1][(m+j*ost[(d-i-1)%6])%7];
    if (u<0)
    u+=OST;
    if (u>=OST)
    u-=OST;
    }
    m+=j*ost[(d-i-1)%6];
    m%=7;
    if (niz[i]=='7')
    {
    if (((niz[d-1]-'0')&1))
    u-=t;

    if (u<0)
    u+=OST;
    if (u>=OST)
    u-=OST;

    break;
    }
    }
    printf("%d\n",u+1);
    }
    }