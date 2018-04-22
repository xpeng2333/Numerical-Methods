#include <stdio.h>

double f(double x) { return x * x * x / 3 - x; }

double df(double x) { return x * x - 1; }

//µü´ú¸ñÊ½
double X_k1_newton(double X_k) { return X_k - f(X_k) / df(X_k); }
double X_k1_secant(double X_k, double X_k_1) {
    return X_k - f(X_k) * (X_k - X_k_1) / (f(X_k) - f(X_k_1));
}
int main() { return 0; }