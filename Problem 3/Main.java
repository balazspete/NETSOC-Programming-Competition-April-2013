import java.math.BigInteger;
import java.math.BigDecimal;
import java.math.MathContext;
import java.util.*;

class Main {

    private static int fav[][];
    private static int n;
    private static boolean cycle;
    private static MathContext mc;

    public static BigInteger determinant (BigDecimal[][] A)
    {
        // compute determinant by LU decomposition
        // it is O(n^3) : finally better than n! :)
        // det(A) = product of diagonal elements of U
        BigDecimal result = BigDecimal.ONE;

        BigDecimal[][] L = new BigDecimal[A.length][A.length];
        BigDecimal[][] U = new BigDecimal[A.length][A.length];
        int i,j,k;

        for (k = 0; k < A.length; k++)
        {
            U[k][k] = A[k][k];
            for (i = k+1; i < A.length; i++)
            {
                if (U[k][k].compareTo(BigDecimal.ZERO) == 0) L[i][k] = BigDecimal.ZERO;
                else L[i][k] = A[i][k].divide(U[k][k],mc);

                U[k][i] = A[k][i];
            }
            for (i = k+1; i < A.length; i++)
            {
                for (j = k+1; j < A.length; j++)
                {
                    A[i][j] = A[i][j].subtract(L[i][k].multiply(U[k][j])) ;
                }
            }
        }

        for (i = 0; i < A.length; i++)
        {
            result = result.multiply(U[i][i]);
        }
        // round up the result
        result = result.setScale(1,BigDecimal.ROUND_HALF_UP);
        return result.toBigInteger();
    }

    public static void main (String[] args)
    {
        int t,p,x,y;
        Scanner in = new Scanner(System.in);
        t = in.nextInt();

        for (int T = 1; T <= t; T++)
        {
            n = in.nextInt();

            String graph[] = new String[n];
            fav = new int[n][n];
            int [][] vis = new int[n][n];

            String tmp = in.nextLine();
            for (int i = 0; i < n; i++)
            {
                graph[i] = in.nextLine();
                for (int j = 0; j < n; j++)
                {
                    fav[i][j] = 0;
                    vis[i][j] = 0;
                }
            }

            p = in.nextInt();
            for (int i = 0; i < p; i++)
            {
                x = in.nextInt();
                y = in.nextInt();
                fav[x-1][y-1] = 1;
                fav[y-1][x-1] = 1;
            }

            cycle = false;

            // modify the graph by merging the vertices connected by favourite bridges
            ArrayList < ArrayList <Integer> > R = new ArrayList < ArrayList <Integer> > ();
            for (int i = 0; i < n; i++)
            {
                ArrayList <Integer> v = new ArrayList <Integer> ();
                v.add((Integer)i);
                R.add(v);
            }
            ArrayList <Integer> emp;
            for (int i = 0; i < n; i++)
            {
                for (int j = i+1; j < n; j++)
                {
                    if (fav[i][j] == 1)
                    {
                        int r1 = -1, r2 = -1;
                        for (int k = 0; k < n; k++)
                        {
                            if (r1 != -1 && r2 != -1) break;
                            for (int l = 0; l < R.get(k).size(); l++)
                            {
                                if (R.get(k).get(l) == i)
                                {
                                    r1 = k;
                                }
                                if (R.get(k).get(l) == j)
                                {
                                    r2 = k;
                                }
                            }
                        }
                        if (r1 == r2)
                        {
                            // cyclic
                            cycle = true;
                            break;
                        }
                        for (int k = 0; k < R.get(r1).size(); k++) R.get(r2).add(R.get(r1).get(k));
                        R.get(r1).clear();
                    }
                }
                if (cycle == true) break;
            }

            if (cycle == true)
            {
                System.out.println(0);
                continue;
            } else
            {
                // find the new no. of nodes in graph
                // prepare Laplacian matrix
                ArrayList < ArrayList <Integer> > nodes = new ArrayList < ArrayList <Integer> > ();
                for (int i = 0; i < R.size(); i++) if (R.get(i).size() > 0) nodes.add(R.get(i));
                if (nodes.size() == 1)
                {
                    System.out.println(1);
                    continue;
                }
                int Laplacian[][] = new int[nodes.size()][nodes.size()];

                int degree[] = new int[nodes.size()];
                for (int i = 0; i < nodes.size(); i++)
                {
                    int c = 0;
                    for (int j = 0; j < nodes.get(i).size(); j++)
                    {
                        int u = nodes.get(i).get(j);
                        for (int k = 0; k < nodes.size(); k++)
                        {
                            if (i == k) continue;
                            for (int l = 0; l < nodes.get(k).size(); l++)
                            {
                                int v = nodes.get(k).get(l);
                                c += graph[u].charAt(v)-'0';
                            }
                        }
                    }

                    degree[i] = c;
                }
                for (int i = 0; i < nodes.size(); i++)
                {
                    for (int j = 0; j < nodes.size(); j++)
                    {
                        Laplacian[i][j] = 0;
                        if (i != j)
                        {
                            for (int k = 0; k < nodes.get(i).size(); k++)
                            {
                                for (int l = 0; l < nodes.get(j).size(); l++)
                                {
                                    if (graph[nodes.get(i).get(k)].charAt(nodes.get(j).get(l)) == '1') Laplacian[i][j] -= 1;
                                }
                            }
                        }
                        else
                        {
                            Laplacian[i][j] = degree[i];
                        }
                        //System.out.print(Laplacian[i][j] + " ");
                    }
                    //System.out.println();
                }
                int N = nodes.size();
                BigDecimal cofactor[][] = new BigDecimal[N-1][N-1];
                for (int i = 1; i < N; i++)
                {
                    for (int j = 1; j < N; j++)
                    {
                        cofactor[i-1][j-1] = BigDecimal.valueOf(Laplacian[i][j]);
                    }
                }
                mc = new MathContext(45);
                System.out.println(determinant(cofactor));
            }
        }
    }
}