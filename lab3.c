#include <math.h>
#include <stdio.h>

double f(double x) { return sin(x); }

double F(double x) { return -cos(x); }
int main() {
    double a, b, h, T;
    a = 1.0;
    b = 5.0;
    double T0 = F(b) - F(a);
    double e = 0.0;
    printf("复化梯形积分公式的误差和误差阶为：\n");
    for (int k = 0; k < 13; k++) {
        int N = pow(2, k);
        h = (b - a) / (double)N;
        double tmp = (f(a) + f(b)) / 2.0;
        for (int i = 1; i < N; i++) {
            tmp += f(a + i * h);
        }
        T = h * tmp;
        double tmpe = T0 - T;
        if (N == 1) {
            e = tmpe;
            printf("N=%5d , %16.12e\n", N, tmpe);
            continue;
        }
        printf("N=%5d , %16.12e , %16.12e\n", N, tmpe,
               -log(fabs(tmpe / e)) / log(2));
        e = tmpe;
    }
    printf("复化Simpson积分公式的误差和误差阶为：\n");
    for (int k = 1; k < 13; k++) {
        int N = pow(2, k);
        int m = N / 2;
        h = (b - a) / (double)N;
        double tmp0 = f(a) + f(b);
        double tmp1, tmp2;
        tmp1 = tmp2 = 0.0;
        for (int i = 0; i < m; i++) {
            tmp1 += f(a + (2 * i + 1) * h);
        }
        tmp1 *= 4;
        for (int i = 1; i < m; i++) {
            tmp2 += f(a + (2 * i) * h);
        }
        tmp2 *= 2;
        T = h * (tmp0 + tmp1 + tmp2) / 3.0;
        double tmpe = T0 - T;
        if (N == 2) {
            e = tmpe;
            printf("N=%5d , %16.12e\n", N, tmpe);
            continue;
        }
        printf("N=%5d , %16.12e , %16.12e\n", N, tmpe,
               -log(fabs(tmpe / e)) / log(2));
        e = tmpe;
    }
    return 0;
}