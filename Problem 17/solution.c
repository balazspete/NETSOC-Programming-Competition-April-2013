#include <stdio.h>
#define R(i,n) for(i=0;i<(n);i++)
#define MAXNODES 7700000
typedef struct node_s
{
    int d;
    struct node_s *next;
} NODE_T;
#define T 200000
NODE_T g_nodes[MAXNODES];
NODE_T *g_divisors[T];
NODE_T *F[T];
#define BCDDIGITS 40
typedef struct bcd_s
{
    int d[BCDDIGITS];
} BCD_T;

void bcd_set(BCD_T *b,long long n)
{
    int i;
    for (i=0;i<BCDDIGITS;i++)
    {
        b->d[i]=n%10;
        n/=10;
    }
}

void bcd_mult(BCD_T *dest,BCD_T *a,BCD_T *b)
{
    int i,j;
    bcd_set(dest,0);
    for (i=0;i<BCDDIGITS;i++)
    {
        int carry=0;
        for (j=0;j<BCDDIGITS-i;j++)
        {
            carry=a->d[i]*b->d[j]+dest->d[i+j]+carry;
            dest->d[i+j]=carry%10;
            carry/=10;
        }
    }
}

void bcd_print(BCD_T *a)
{
    int i;
    int seen=0;
    for (i=BCDDIGITS-1;i>=0;i--)
    {
        if (seen || i==0 || a->d[i])
        {
            printf("%d",a->d[i]);
            seen=1;
        }
    }
}

int gcd(int a,int b)
{
   if (a == 0)
      return b;
   return gcd(b % a, a);
}
#define MAXD 500
int n_alt_divisors[MAXD][MAXD];  // lists of n/divisors
int *div_divisors[T]; // Pointer to list of divisors for n1
int *alt_divisors[T]; // Pointer to list of n/divisors for n1
int num_div_divisors[T];  // number in each divisor list
int div_count=0;  // How many divisor lists used

int main(int argc,char *argv[])
{
    int a;
    long long k;
    int n;
    int numtests;
    int numnodes=0;
    int n_divisors[4000];
    int num_n=0;
    int i,d;
    int debug;

    R(d,T) {
        g_divisors[d]=(void*)0;
        F[d]=(void*)0;
        }
    for(d=1;d<T;d++){
        int d2=d;
        while (d2<T)
        {
            NODE_T *h=&g_nodes[numnodes];
            h->d=d;
            h->next=g_divisors[d2];
            g_divisors[d2]=h;
            numnodes++;
            d2+=d;
        }
    }
    //printf("%d\n",numnodes);

    scanf("%d\n",&numtests);
    R(a,numtests) {
        int stop,stopa;
        long long K2;
        int t=0;
        int y;
        int n0;
        scanf("%d %lld\n",&n,&k);
        K2=k-n;
        if (n==0)
        {
            BCD_T bcd_k,bcd_out;
            bcd_set(&bcd_k,k-1);
            bcd_mult(&bcd_out,&bcd_k,&bcd_k);
            bcd_print(&bcd_out);
            printf("\n",(k-1)*(k-1));
            continue;
        }
        n0=n;

        num_n=0;
        for(d=1;d<=n;d++)
        {
            if (n%d==0)
            {
                n_divisors[num_n++]=d;
            }
        }
        div_count=0;
        for(y=0;y<num_n;y++)
        {
            int n2=n_divisors[y];
            alt_divisors[n2]=n_alt_divisors[div_count++];

            num_div_divisors[n2]=0;
            for(d=n2;d>=1;d--)
            {
                if (n2%d==0)
                {
                alt_divisors[n2][num_div_divisors[n2]++]=n2/d;

                }
            }
        }

        stop=25*n0/10;
    if (stop>=K2) stop=K2-1;
    stopa=n0/10;
    //stopa=1;
        if (stopa+n0-1>=T) stopa=T-n0-1;
        if (stop<stopa) stopa=stop;
        for(y=1;y<=stopa;y++)
        {
            NODE_T *h;
            long long rhs=n0;
            long long S[4000];
            int num_s=0;
            int n1,n2,y2;
            NODE_T **clear_nodes[4000];
            int num_clear=0;
            int old_num=numnodes;
            int n2opt;
            int num_div_divisors_n2;
            int *np;
            rhs=(y+n0-1); // factors of n are accounted for in n1 and in alt_divisors=n2/p
            n1=gcd(n,y);
            n2=n/n1;
            y2=y/n1;
            num_div_divisors_n2=num_div_divisors[n2];
            np=alt_divisors[n2];
            //rhs/=n1;
            //rhs/=n2;
            // Set up values in F,
            // Store n2/p in here
            h=&g_nodes[numnodes];
            R(i,num_div_divisors_n2){
                int n3;
                int key;
                n3=*np++;
                key=(-n3)%y2;
                if (key<0) key+=y2;
                h->d=n3;
                h->next=F[key];
                if (!h->next)
                {
        clear_nodes[num_clear++]=&F[key];
                }
                F[key]=h;

                h++;
            }
            for(h=g_divisors[y+n0-1];h;h=h->next)
            {
                int power2;
                long long q=h->d;
                int key=(int)q%y2;
                if (key<0) key+=y2;
                {
                    NODE_T *h2;
                    //printf("Key=%d\n",key);
                    for(h2=F[key];h2;h2=h2->next)
                    {
                        long long rhs2=rhs/q;
                        long long p_inv=h2->d;
                        //long long v=(p*q+n);
                        long long x;
                        int s;
                        int seen=0;
                    //printf("rhs=%lld,q=%lld,p=%lld\n",rhs,q,p);
                        //if (v%y) continue; //
                        x=rhs2*p_inv;
                        if (x<y) break;
                        if (x>=K2) continue;
                        for (s=0;s<num_s;s++)
                        {
                            if (x==S[s])
                            {
                                seen=1;
                                break;
                            }
                        }
                        if (seen) continue;
                        S[num_s++]=x;
                        //printf("%d %d\n",y,x);
                        if (x==y) t+=1;
                        if (x>y) t+=2;
                        //printf("%d %lld %lld %lld\n",y,x,p,q);
                    }
                }
            }
            R(i,num_clear)
            {
                *clear_nodes[i]=(void*)0;
            }

        }
    for(;y<=stop;y++)
        {
            long long rhs=n;
      int Fstart=(-n)%y;
      long long Fc;
      rhs*=(y+n0-1);
      if (Fstart<=0) Fstart+=y;
      for(Fc=Fstart;;Fc+=y)
      {
        long long x=rhs/Fc;
        long long rem=rhs%Fc;
        if (x<y) break;
        if (rem) continue;
        if (x>=K2) continue;
        if (x==y) t+=1;
                if (x>y) t+=2;
      }
        }
        printf("%d\n",t);
    }

    return 0;
}