#include <vector>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <queue>
using namespace std;

const int maxn = 557, maxnum = 0x3f3f3f3f;

long long mul(long long x,long long y,long long n)
{
    long long ans=0, t=y%n;
    if ( x==0 ) return 0;
    while ( x>0 )
    {
        if ( x&1 ) {
            ans += t;
            if (ans >= n) ans -= n;
        }
        t += t;
        if (t >= n) t-= n;
        x>>=1;
    }
    return ans;
}

long long pow(long long a,long long x,long long n)
{
    if ( x==0 ) return 1;
    long long mid = pow(a,x/2,n);
    if ( mid==0 ) return 0;

    long long ans=mul(mid,mid,n);
    if ( ans==1 && mid != 1 && mid!=n-1 ) return 0;

    if ( x&1 ) ans = mul(ans,a,n);
    return ans;
}

bool millar_rabin(long long n)
{
    if (n <= 1) return false;
    if (n == 2) return true;
    for (int i=0;i<5;i++)
    {
        long long a = rand() % (n-2) + 2;
        if ( pow(a,n-1,n) != 1) return false;
    }
    return true;
}

bool gao(long long v, long long u)
{
    if(v > u) return v % u == 0 && millar_rabin(v/u);
    if(u > v) return u % v == 0 && millar_rabin(u/v);
    return false;
}

namespace MaxFlow
{
    const int N = maxn;
    const int M = 1000007;

    int n, m, x[N], y[N];

    int edgeCount, firstEdge[N], to[M], capacity[M], nextEdge[M], currentEdge[N];
    int source, target, flow, pre[N], sign;

    void addEdge(int u, int v, int w) {
        to[edgeCount] = v;
        capacity[edgeCount] = w;
        nextEdge[edgeCount] = firstEdge[u];
        firstEdge[u] = edgeCount ++;
    }

    void insert(int u, int v, int w)
    {
        addEdge(u, v, w);
        addEdge(v, u, 0);
    }

    int level[N], queue[N];

    bool bfs(int s, int t) {
        memset(level, -1, sizeof(level));
        sign=t;
        level[t] = 0;
        int tail = 0;
        queue[tail ++] = t;
        int head = 0;
        while (head != tail && level[s] == -1) {
            int v = queue[head ++];
            for (int iter = firstEdge[v]; iter != -1; iter = nextEdge[iter]) {
                if (capacity[iter ^ 1] > 0 && level[to[iter]] == -1) {
                    level[to[iter]] = level[v] + 1;
                    queue[tail ++] = to[iter];
                }
            }
        }
        return level[s] != -1;
    }

    inline void push()
    {
        int delta=maxnum,u,p;
        for (u=target;u!=source;u=to[p]){
            p=pre[u];
            delta=min(delta,capacity[p]);
            p^=1;
        }

        for (u=target;u!=source;u=to[p]){
            p=pre[u];
            capacity[p]-=delta;
            if (!capacity[p]){
                sign=to[p^1];
            }
            capacity[p^=1]+=delta;
        }
        flow+=delta;
    }

    void dfs(int u) {
        if (u == target) {
            push();
            return;
        }
        for (int &iter = currentEdge[u]; iter != -1; iter = nextEdge[iter]) {
            if (capacity[iter] > 0 && level[u] == level[to[iter]] + 1) {
                pre[to[iter]]=iter;
                dfs(to[iter]);
                if (level[sign]>level[u]) return;
                sign=target;
            }
        }
        level[u]=-1;
    }

    void initNetwork(int nodes)
    {
        n = nodes;
        edgeCount = 0;
        for (int i = 0; i <= n; ++i)
            firstEdge[i] = -1;
    }

    int maxFlow(int s, int t)
    {
        source = s;
        target = t;

        flow=0;
        while (bfs(source, target)) {
            for (int i = 0; i < n; ++ i) {
                currentEdge[i] = firstEdge[i];
            }
            dfs(source);
        }

        return flow;
    }
}

int N;
bool cnt[maxn][maxn], use[maxn], ODD[maxn];
struct NODE
{
    long long a;
    int c;
    bool operator < (const NODE &p) const
    {
        return a < p.a;
    }
} p[maxn];

void Fill(int x, int order)
{
    use[x] = true;
    if (order) ODD[x] = false;
    else       ODD[x] = true;
    for (int xx = 1; xx <= N; xx++)
        if (cnt[x][xx] && !use[xx]) Fill(xx, order^1);
}

int main()
{
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) scanf("%lld%d", &p[i].a, &p[i].c);
    sort(p+1, p+1+N);
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= N; j++) cnt[i][j] = false;
    for (int i = 1; i <= N; i++)
        for (int j = i+1; j <= N; j++)
            if (gao(p[i].a, p[j].a)) cnt[i][j] = cnt[j][i] = true;
    for (int i = 1; i <= N; i++) use[i] = false;
    for (int i = 1; i <= N; i++)
        if (!use[i]) Fill(i, 0);
    int first = N+1, last = first+1;
    MaxFlow::initNetwork(last+1);
    for (int i = 1; i <= N; i++)
        if (ODD[i]) MaxFlow::insert(first, i, p[i].c);
        else        MaxFlow::insert(i, last, p[i].c);
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= N; j++)
            if (ODD[i] && !ODD[j] && cnt[i][j]) MaxFlow::insert(i, j, maxnum);
    MaxFlow::maxFlow(first, last);
    long long res = -1;
    for (int i = 1; i <= N; i++)
    {
        if (ODD[i]) MaxFlow::insert(i, last, 1);
        else        MaxFlow::insert(first, i, 1);
        if (MaxFlow::bfs(first, last))
        {
            res = p[i].a;
            break;
        }
        if (ODD[i]) MaxFlow::insert(first, i, 1);
        else        MaxFlow::insert(i, last, 1);
        MaxFlow::maxFlow(first, last);
    }
    if (res == -1) puts("Tyrion");
    else           printf("Bran %lld\n", res);
    return 0;
}
