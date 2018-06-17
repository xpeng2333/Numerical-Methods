#include <math.h>
#include <stdio.h>
double f(double x, double y) { return -x * x * y * y; }

double yx(double x) { return 3 / (1 + x * x * x); }
int main(int argc, char const *argv[]) {
    double hList[4] = {0.1, 0.1 / 2, 0.1 / 4, 0.1 / 8};
    int count[4] = {15, 30, 60, 120};
    double yh1[15];
    double yh2[30];
    double yh3[60];
    double yh4[120];
    double *yhList[4] = {yh1, yh2, yh3, yh4};
    printf("Runge-Kutta 法的误差和误差阶：\n");
    double k1, k2, k3, k4;
    double eh, ehk, ok;
    for (int i = 0; i < 4; i++) {
        double h = hList[i];
        double xi, yi;
        double *yh = yhList[i];
        int index;
        for (index = 0, xi = 0, yi = 3; index < count[i]; index++, xi += h) {
            k1 = f(xi, yi);
            k2 = f(xi + h / 2, yi + h * k1 / 2);
            k3 = f(xi + h / 2, yi + h * k2 / 2);
            k4 = f(xi + h, yi + h * k3);
            yi = yi + h * (k1 + 2 * k2 + 2 * k3 + k4) / 6;
            yh[index] = yi;
        }
        if (i == 0) {
            eh = fabs(yi - yx(1.5));
            printf("步长: %6.4f ,%16.12e\n", h, eh);
        } else {
            ehk = fabs(yi - yx(1.5));
            ok = log2(eh / ehk) / log2(2);
            printf("步长: %6.4f ,%16.12e ,%16.12e\n", h, ehk, ok);
            eh = ehk;
        }
    }
    printf("Adams隐格式，误差和误差阶为：\n");
    for (int i = 0; i < 4; i++) {
        double h = hList[i];
        double xim1, yim1, xi, yi, xia1, yia1, xim2, yim2;
        double *yh = yhList[i];
        int index;
        xi = 2 * h;
        yi = yh[1];
        xim1 = h;
        yim1 = yh[0];
        xim2 = 0;
        yim2 = 3;
        double tmpYia1;
        for (index = 1; index < count[i] - 1; index++, xi += h) {
            xia1 = xi + h;
            xim1 = xi - h;
            xim2 = xi - 2 * h;
            tmpYia1 =
                yi +
                h * (23 * f(xi, yi) - 16 * f(xim1, yim1) + 5 * f(xim2, yim2)) /
                    12;
            yia1 =
                yi +
                h * (5 * f(xia1, tmpYia1) + 8 * f(xi, yi) - f(xim1, yim1)) / 12;
            yim2 = yim1;
            yim1 = yi;
            yi = yia1;
        }
        if (i == 0) {
            eh = fabs(yi - yx(1.5));
            printf("步长: %6.4f ,%16.12e\n", h, eh);
        } else {
            ehk = fabs(yi - yx(1.5));
            ok = log2(eh / ehk) / log2(2);
            printf("步长: %6.4f ,%16.12e ,%16.12e\n", h, ehk, ok);
            eh = ehk;
        }
    }
    return 0;
}
