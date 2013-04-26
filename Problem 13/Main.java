import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintStream;
import java.util.*;

/* UH++
 * Daniel Otero Baguer
 * Problem:
 */

public class Main
{
    BufferedReader in;
    PrintStream out;
    StringTokenizer tok;
    public Main() throws NumberFormatException, IOException
    {
        in = new BufferedReader(new InputStreamReader(System.in));
        //in = new BufferedReader(new FileReader("in.txt"));
        out = System.out;
        run();
    }
    //solves a^b modulo p
    long powmod(long a, long b, int p)
    {
        if(b==0) return 1;
        if(b%2==1) return (a*powmod(a,b-1,p))%p;
        long r = powmod(a,b/2,p);
        return (r*r)%p;
    }
    // computes inverse of a modulo p
    long inverse(long a,int p)
    {
        return powmod(a,p-2,p);
    }
    //solves a*x = b (mod p)
    long solve_linear(long a, long b, int p)
    {
        return (b*inverse(a,p))%p;
    }
    //returns true if a is quadratic residue modulo p (prime)
    boolean is_quadratic_residue(int a, int p)
    {
        if(a==0) return true;
        return powmod(a,(p-1)/2,p)==1;
    }
    //solves x^2=a (mod p)
    long solve_quadratic(long a, int p)
    {
        if(a==0) return 0;
        if(p==2) return a;
        if(powmod(a,(p-1)/2,p)!= 1) return -1;
        int phi = p-1;
        int n = 0,k = 0;
        while(phi%2==0)
        {
            phi/=2;
            n++;
        }
        k = phi;
        int q = 0;
        for(int j = 2; j < p; j++)
            if(powmod(j,(p-1)/2,p)==p-1)
            {
                q = j;
                break;
            }
        long t = powmod(a,(k+1)/2,p);
        long r = powmod(a,k,p);
        while(r!=1)
        {
            int i = 0;
            int v = 1;
            while(powmod(r,v,p)!=1){v*=2;i++;}
            long e = powmod(2,n-i-1,p);
            long u = powmod(q,k*e,p);
            t = (t*u)%p;
            r = (r*u*u)%p;
        }
        return (int)t;
    }
    //solves a*x^2 + b*x +c=0 (mod p)
    Set<Long> solve_quadratic(long a, long b, long c, int p)
    {
        Set<Long> ans = new TreeSet<Long>();
        if(c==0) ans.add(0L);
        if(a==0)
        {
            ans.add(solve_linear((p-b)%p,c,p));
        }
        else if(p==2)
        {
            if((a+b+c)%2==0) ans.add(1L);
        }
        else
        {
            long r = ((b*b)%p -(4*a*c)%p+ p)%p;
            long x = solve_quadratic(r,p);
            if(x==-1) return null;
            long w = solve_linear((2*a)%p,(x-b+p)%p,p);
            ans.add(w);
            w = solve_linear((2*a)%p,(p-x-b+p)%p,p);
            ans.add(w);
        }
        return ans;
    }
    void run() throws NumberFormatException, IOException
    {
        int t = nextInt();
        while(t-->0)
        {
            long a = nextInt();
            long b = nextInt();
            long c = nextInt();
            int p = nextInt();
            Set<Long> ans = solve_quadratic(a,b,c,p);
            if(ans==null) out.println(0);
            else
            {
                out.print(ans.size());
                for(long i: ans)
                    out.print(" "+i);
                out.println();
            }
        }
    }
    public static void main(String[] args) throws NumberFormatException, IOException
    {
        new Main();
    }
    String nextToken() throws IOException
    {
        if(tok ==null || !tok.hasMoreTokens()) tok = new StringTokenizer(in.readLine());
        return tok.nextToken();
    }
    int nextInt() throws NumberFormatException, IOException
    {
        return Integer.parseInt(nextToken());
    }
    long nextLong() throws NumberFormatException, IOException
    {
        return Long.parseLong(nextToken());
    }
    double nextDouble() throws NumberFormatException, IOException
    {
        return Double.parseDouble(nextToken());
    }
}