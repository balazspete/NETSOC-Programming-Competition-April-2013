#include<iostream>
#include<stack>
#include<stdio.h>
using namespace std;
int t;
string s;
int a[26];
int cnt,l;
char b[16];
bool ch[26];
bool bk,tmp;

inline bool fC(bool x,bool y)
{
     return x&y;
}
inline bool fD(bool x,bool y)
{
       return x|y;
}
inline bool fI(bool x,bool y)
{
       if((x && y) || !x)
       return true;
       return false;
}
inline bool fE(bool x,bool y)
{
       if((x && y) || (!x && !y))
       return true;
       return false;
}
inline bool fN(bool x)
{
       return !x;
}
inline bool checknot(stack<char> &st)
{

      // char x;
       if(st.top()=='Z')
       {
              st.pop();
              if(st.empty())
              {st.push('Z');return false;}
               if(st.top()=='N')
               {st.push('Z');return true;}
               st.push('Z');
       }
       return false;
}
inline bool checkoth(stack<char> &st)
{
      if(st.top()=='Z')
      {
                       st.pop();
                        if(st.empty())
              {st.push('Z');return false;}
                       if(st.top()=='Z')
                       {
                          st.push('Z');
                         return true;
                       }
                       st.push('Z');
      }
      return false;
}
inline bool calc()
{
     stack<char> st1;
     stack<bool> st2;
     bool x,x1,x2,h;
     bool not1,other;
   //  x=false;
     for(int i=0;i<l;i++)
     {
           // cout<<i<<endl;
             if(s[i]-'a'>=0 && s[i]-'z'<=0)
             {
                     //cout<<i<<endl;
                 // if(st1.top()=='N')
                 // {st2.push(!ch[s[i]-'a']);st1.pop();}
                  //else
                  st2.push(ch[s[i]-'a']);
                  st1.push('Z');
                  not1=checknot(st1);
                  other=checkoth(st1);
                  //cout<<ch[s[i]-'a']<<endl;
                   while(other || not1)
                   {
                  if(other)
                  {
                        st1.pop();
                        st1.pop();
                        x1=st2.top();
                        st2.pop();
                        x2=st2.top();
                        st2.pop();
                        if(st1.top()=='C')
                        st2.push(fC(x1,x2));
                        else if(st1.top()=='D')
                        {st2.push(fD(x1,x2));/*cout<<"D "<<st2.top()<<endl;*/}
                        else if(st1.top()=='I')
                        {st2.push(fI(x2,x1));/*cout<<"I "<<st2.top()<<endl;*/}
                        else
                        st2.push(fE(x1,x2));
                        st1.pop();
                        st1.push('Z');
                      /*  while(!st1.empty() && st1.top()=='N')
                        {
                                st1.pop();
                                h=st2.top();
                                st2.pop();
                                st2.push(!h);
                        }*/
                  }
                  else if(not1)
                  {
                        x1=st2.top();
                        st2.pop();
                        st2.push(!x1);
                       // cout<<"N "<<st2.top()<<endl;
                        st1.pop();
                        st1.pop();
                        st1.push('Z');
                  }
                    not1=checknot(st1);
                  other=checkoth(st1);
             //   cout<<other<<not1<<endl;
                 }
                  /*else
                  x=true;*/
             }
             else
             {
                 //cout<<i<<endl;
                 st1.push(s[i]);
                // if(s[i]!='N')
                // x=false;
             }
     }
    // cout<<st2.top()<<endl;
     return st2.top();
}


void f(int i,bool &ans)
{
     if(bk)
     return;
     if(i==-1)
     {

             if(!calc())
             {ans=false;bk=true;}
             return;
     }
     ch[b[i]-'a']=true;
     f(i-1,ans);
     ch[b[i]-'a']=false;
     f(i-1,ans);
}
int main()
{
    scanf("%d",&t);
    char j;
    for(int i=0;i<t;i++)
    {
          cin>>s;
            l=s.length();
           // if(l==1)
           // {cout<<"NO"<<endl;continue;}
            for(int i=0;i<26;i++)
            {
                    a[i]=0;
            }
            for(int i=0;i<l;i++)
            {
                    if(s[i]-'a'>=0 && s[i]-'z'<=0)
                    a[s[i]-'a']++;
            }
            cnt=0;
            for(int i=0;i<26;i++)
            {
                    if(a[i]>0)
                    {b[cnt]='a'+i;cnt++;}
            }
            tmp=true;
            bk=false;
            f(cnt-1,tmp);
            if(tmp)
            printf("YES\n");
            else
            printf("NO\n");
    }
    return 0;
}
/*
8
DNDCppCppNp
IIpqDpNp
NCNpp
Iaz
NNNNNNNp
IIqrIIpqIpr
Ipp
Ezz
*/