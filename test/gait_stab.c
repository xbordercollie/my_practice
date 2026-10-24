/* D6 稳定裕度：重心到"着地脚围成的多边形最近一条边"的距离 */
#include <stdio.h>
#include <math.h>

#define N_LEG 6

/* 重心(0,0) 到 两点(x1,z1)-(x2,z2) 连线的垂直距离 = 三角形的高 */
static double edge_dist(double x1, double z1, double x2, double z2)
{
    double cross = x1 * z2 - x2 * z1;        /* = 2 × 三角形面积 */
    double dx = x2 - x1;
    double dz = z2 - z1;
    double len = sqrt(dx * dx + dz * dz);
    if (len == 0.0) return 0.0;
    return fabs(cross) / len;                /* 面积×2 ÷ 底 = 高 */
}

/* 按极角排序后，只连相邻的两个点，取最小边距 */
static double min_margin(const double *X, const double *Z, int n)
{
    if (n < 3) return 0.0;

    double ang[N_LEG];
    int    idx[N_LEG];

    for (int i = 0; i < n; i++) {
        ang[i] = atan2(Z[i], X[i]);
        idx[i] = i;
    }

    /* 按极角升序（插入排序，n 最多 6） */
    for (int i = 1; i < n; i++) {
        double ka = ang[i];
        int    ki = idx[i];
        int    j  = i - 1;
        while (j >= 0 && ang[j] > ka) {
            ang[j + 1] = ang[j];
            idx[j + 1] = idx[j];
            j--;
        }
        ang[j + 1] = ka;
        idx[j + 1] = ki;
    }

    double min = 1e9;
    for (int k = 0; k < n; k++) {
        int a = idx[k];
        int b = idx[(k + 1) % n];             /* 最后一个连回第一个 */
        double d = edge_dist(X[a], Z[a], X[b], Z[b]);
        if (d < min) min = d;
    }
    return min;
}

int main(void)
{
    const double R = 160.0;
    const double theta[N_LEG] = {135, 90, 45, -135, -90, -45};  /* RR RM RF LR LM LF */
    const int    offset[N_LEG] = {0, 6, 0, 6, 0, 6};            /* TRIPOD_6 */
    const int    steps = 12;
    const int    lift  = 4;
    const double L     = 40.0;

    /* ---- ① 站姿：六条腿全着地 ---- */
    double X0[N_LEG], Z0[N_LEG];
    for (int i = 0; i < N_LEG; i++) {
        X0[i] = R * cos(theta[i] * M_PI / 180.0);
        Z0[i] = R * sin(theta[i] * M_PI / 180.0);
    }
    printf("站姿裕度 = %.1f mm   （腿在 ±45/+90/±135，前后各留 90 缺口，不是正六边形）\n\n", min_margin(X0, Z0, N_LEG));

    /* ---- ② 走 12 步，每步只取着地的腿 ---- */
    printf("step  着地  裕度(mm)\n");
    for (int step = 0; step < steps; step++) {
        double X[N_LEG], Z[N_LEG];
        int n = 0;

        for (int i = 0; i < N_LEG; i++) {
            int phase = (step + offset[i]) % steps;
            if (phase < lift) continue;               /* 这条腿在空中，不参与 */

            int    s  = phase - lift;                 /* 支撑段第几步 */
            double v  = (double)s / (steps - lift);
            double dx = L * (0.5 - v);                /* 脚相对机身往后退 */

            X[n] = X0[i] + dx;
            Z[n] = Z0[i];
            n++;
        }
        printf("%4d  %4d  %8.1f\n", step, n, min_margin(X, Z, n));
    }
    return 0;
}
