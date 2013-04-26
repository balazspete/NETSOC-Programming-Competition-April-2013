#define N     1000
#define LEFT  0.5
#define RIGHT 0.4
#define NIL   0.1

#include <stdio.h>
int main() {
    static double buffer[2][N*2+1][N+1];
    double (*src)[N+1] = buffer[0], (*dst)[N+1] = buffer[1];
    src[N][0] = 1;
    for (int n = 0; n < N; ++n) {
        for (int i = N-n; i <= N+n; ++i) {
            for (int j = i<N ? N-i : 0; j <= n; ++j) {
                double x = src[i][j];
                if (x != 0) {
                    dst[i-1][j+1] += x * LEFT;
                    dst[i+1][j>0 ? j-1 : 0] += x * RIGHT;
                    dst[i][j] += x * NIL;
                    src[i][j] = 0;
                }
            }
        }
        double (*tmp)[N+1] = src;
        src = dst; dst = tmp;
    }
    double e = 0;
    for (int i = 0; i < N*2+1; ++i)
        for (int j = 0; j < N+1; ++j)
            e += src[i][j] * (i + j - N);
    printf("%f\n", e);
}