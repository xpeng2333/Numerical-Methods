#include <math.h>
#include <stdio.h>

#define PI 3.1415926535897932384626

int main() {
    int N[4] = {5, 10, 20, 40};                //储存不同的插值规模
    for (int count = 1; count <= 2; count++) { //分别计算两种情况
        printf("第%d组节点误差：\n", count);
        for (int m = 0; m < 4; m++) { //对不同的插值规模进行计算
            int n = N[m];
            double x[n + 1];
            double max = 0.0; //最大误差
            if (count == 1) { //第一种情况的插值点
                for (int i = 0; i <= n; i++)
                    x[i] = -5 + 10 * i / (double)n;
            } else { //第二种情况的插值点
                for (int i = 0; i <= n; i++)
                    x[i] = -5 * cos((2 * i + 1) * PI / (2 * n + 2));
            }
            for (int r = 0; r <= 500; r++) { // 对501个检测点求误差
                double yr = -5 + 1 / (double)50 * r;
                double Ln = 0.0;
                double Fn = 1 / (1 + yr * yr);
                for (int i = 0; i <= n; i++) { //计算检测点代入插值公式的值
                    double tmp = 1.0;
                    for (int j = 0; j < i; j++)
                        tmp *= (yr - x[j]) / (x[i] - x[j]);
                    for (int j = i + 1; j <= n; j++)
                        tmp *= (yr - x[j]) / (x[i] - x[j]);
                    Ln += tmp / (1 + x[i] * x[i]);
                }
                if (max < fabs(Ln - Fn))
                    max = fabs(Ln - Fn);
            }
            printf("N=%2d,%16.12e\n", n, max);
        }
    }
    return 0;
}
