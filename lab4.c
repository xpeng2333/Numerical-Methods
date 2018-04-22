#include <math.h>
#include <stdio.h>

double f(double x) { return x * x * x / 3 - x; }

double df(double x) { return x * x - 1; }

//迭代格式
double X_kadd1_newton(double X_k) { return X_k - f(X_k) / df(X_k); }
double X_kadd1_secant(double X_kminus1, double X_k) {
    return X_k - f(X_k) * (X_k - X_kminus1) / (f(X_k) - f(X_kminus1));
}
int main() {
    double x_list[4] = {0.1, 0.2, 0.9, 9.0};
    printf("Newton迭代,初值、根和迭代步数为:\n");
    for (int i = 0; i < 4; i++) {
        double x0 = x_list[i];
        double x_kadd1, x_k = x0;
        int count = 0;
        while (1) {
            x_kadd1 = X_kadd1_newton(x_k);
            if (fabs(x_kadd1 - x_k) < 0.0000000001)
                break;
            x_k = x_kadd1;
            count++;
        }
        printf("%3.1lf,%16.12e,%d\n", x0, x_k, count);
    }

    printf("\n弦截法,初值、根和迭代步数为:\n");
    for (int i = 0; i < 3; i++) {
        double x0 = x_list[i];
        double x1 = x_list[i + 1];
        double x_kadd1, x_kminus1 = x0, x_k = x1;
        int count = 0;
        while (1) {
            x_kadd1 = X_kadd1_secant(x_kminus1, x_k);
            if (fabs(x_kadd1 - x_k) < 0.0000000001)
                break;
            x_kminus1 = x_k;
            x_k = x_kadd1;
            count++;
        }
        printf("%3.1lf,%3.1lf,%16.12e,%d\n", x0, x1, x_k, count);
    }
    return 0;
}