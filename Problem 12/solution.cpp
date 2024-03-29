#include<iostream>
#include<deque>
using namespace std;
int main(){
    int n,k,a[1000][1000],i,j;
    cin>>n>>k;
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            cin>>a[i][j];

    for(i=0;i<n;i++)
    {
        deque<int> q;
        for(j=0;j<k-1;j++)
        {
        while(!q.empty() && q.back()>a[i][j])
            q.pop_back();
        q.push_back(a[i][j]);
        }
        for(j=k-1;j<n;j++)
        {
            while(!q.empty() && q.back()>a[i][j])
                q.pop_back();
            q.push_back(a[i][j]);
            int temp=a[i][j-k+1];
            a[i][j-k+1]=q.front();
            if(temp==q.front())
                q.pop_front();
        }
    }

    for(i=0;i<n;i++)
    {
        deque<int> q;
        for(j=0;j<k-1;j++)
        {
        while(!q.empty() && q.back()>a[j][i])
            q.pop_back();
        q.push_back(a[j][i]);
        }
        for(j=k-1;j<n;j++)
        {
            while(!q.empty() && q.back()>a[j][i])
                q.pop_back();
            q.push_back(a[j][i]);
            int temp=a[j-k+1][i];
            a[j-k+1][i]=q.front();
            if(temp==q.front())
                q.pop_front();
        }
    }

    for(i=0;i<n-k+1;i++)
    {
        for(j=0;j<n-k+1;j++){
            cout<<a[i][j];
            if(j<n-k) cout << " ";
        }
        cout<<"\n";
    }
    return 0;
}