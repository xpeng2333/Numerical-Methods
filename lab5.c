#include <limits.h>
#include <stdio.h>
int main() {
    double A[9][9] = {
        {31, -31, 0, 0, 0, -10, 0, 0, 0}, {-13, 35, -9, 0, -11, 0, 0, 0, 0},
        {0, -9, 31, -10, 0, 0, 0, 0, 0},  {0, 0, -10, 79, -30, 0, 0, 0, -9},
        {0, 0, 0, -30, 57, -7, 0, -5, 0}, {0, 0, 0, 0, -7, 47, -30, 0, 0},
        {0, 0, 0, 0, 0, -30, 41, 0, 0},   {0, 0, 0, 0, -5, 0, 0, 27, -2},
        {0, 0, 0, -9, 0, 0, 0, -2, 29}};
    double Ax[9] = {-15, 27, -23, 0, -20, 12, -7, 7, 10};
    double x[9] = {0.0};
    double a_ik;
    int row_flag;

    for (int k = 0; k < 8; k++) {
        //找最大
        a_ik = A[k][k];
        row_flag = k;
        for (int i = k + 1; i < 9; i++) {
            if (a_ik < A[i][k]) {
                row_flag = i;
                a_ik = A[i][k];
            }
        }
        //交换
        if (row_flag != k) {
            double tmp;
            for (int j = 0; j < 9; j++) {
                tmp = A[k][j];
                A[k][j] = A[row_flag][j];
                A[row_flag][j] = tmp;
            }
            tmp = Ax[k];
            Ax[k] = Ax[row_flag];
            Ax[row_flag] = tmp;
        }
        //消元法
        for (int i = k + 1; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                A[i][j] -= A[k][j] * A[i][k] / A[k][k];
            }
            Ax[i] -= Ax[i] * A[i][k] / A[k][k];
        }
    }
    //求解
    for (int i = 8; i >= 0; i--) {
        for (int j = 8; j > i; j--) {
            Ax[i] -= A[i][j] * x[j];
        }
        x[i] = Ax[i] / A[i][i];
    }
    for (int i = 0; i < 9; i++) {
        printf("x%d = %16.12e\n", i, x[i]);
    }
    return 0;
}