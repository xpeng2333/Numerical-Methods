#include <math.h>
#include <stdio.h>

double norm(double x1[9], double x2[9]) {
    double x[9];
    double max = 0;
    for (int i = 0; i < 9; i++) {
        x[i] = fabs(x1[i] - x2[i]);
        if (x[i] > max) {
            max = x[i];
        }
    }
    return max;
}
void GaussSeidel(double A[][9], double Y[9]) {
    double b[9][9];
    double g[9];
    int count = 0;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            b[i][j] = -A[i][j] / A[i][i];
        }
        b[i][i] = 0.0;
        g[i] = Y[i] / A[i][i];
    }
    double x1[9], x2[9];
    for (int i = 0; i < 9; i++) {
        x1[i] = 0;
        x2[i] = 1;
    }
    while (norm(x1, x2) > 0.000001) {
        for (int u = 0; u < 9; u++) {
            x1[u] = x2[u];
        }
        for (int i = 0; i < 9; i++) {
            double s = g[i];
            for (int j = 0; j < 9; j++) {
                s += b[i][j] * x2[j];
            }
            x2[i] = s;
        }
        count++;
    }
    printf("根为：\n");
    for (int i = 0; i < 9; i++) {
        printf("%16.12e\n", x2[i]);
    }
    printf("Gauss-seidel迭代总迭代步数为:%d\n", count);
}

double SOR(double A[][9], double Y[9], double w) {
    double b[9][9];
    double g[9];
    int count = 0;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            b[i][j] = -A[i][j] / A[i][i];
        }
        b[i][i] = 0.0;
        g[i] = Y[i] / A[i][i];
    }
    double x1[9], x2[9];
    for (int i = 0; i < 9; i++) {
        x1[i] = 0;
        x2[i] = 1;
    }
    while (norm(x1, x2) > 0.000001) {
        for (int u = 0; u < 9; u++) {
            x1[u] = x2[u];
        }
        for (int i = 0; i < 9; i++) {
            double s = g[i];
            for (int j = 0; j < 9; j++) {
                s += b[i][j] * x2[j];
            }
            x2[i] = (1 - w) * x1[i] + w * s;
        }
        count++;
    }
    printf("松弛因子: %.2f , %d\n", w, count);
}
int main(int argc, char const *argv[]) {
    double A[9][9] = {
        {31, -13, 0, 0, 0, -10, 0, 0, 0}, {-13, 35, -9, 0, -11, 0, 0, 0, 0},
        {0, -9, 31, -10, 0, 0, 0, 0, 0},  {0, 0, -10, 79, -30, 0, 0, 0, -9},
        {0, 0, 0, -30, 57, -7, 0, -5, 0}, {0, 0, 0, 0, -7, 47, -30, 0, 0},
        {0, 0, 0, 0, 0, -30, 41, 0, 0},   {0, 0, 0, 0, -5, 0, 0, 27, -2},
        {0, 0, 0, -9, 0, 0, 0, -2, 29}};
    double Y[9] = {-15, 27, -23, 0, -20, 12, -7, 7, 10};
    GaussSeidel(A, Y);
    printf("\n");
    printf("SOR迭代步数为:\n");
    for (int i = 1; i < 100; i++) {
        double w = i / 50.0;
        SOR(A, Y, w);
    }
    return 0;
}
