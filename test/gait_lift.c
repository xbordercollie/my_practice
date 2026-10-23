/* D2 抬腿轨迹：比例 = 4x(1-x)，只算一条腿（RR，offset=0，所以相位就是 step） */
#include <stdio.h>

int main(void)
{
    const int steps  = 12;   /* 周期总步数 */
    const int lift   = 4;    /* 抬腿步数 */
    const int lift_h = 20;   /* 抬腿总高度（mm），先随便定 */

    int N = lift * 100;      /* 抬腿段总细分数 = 400 */

    printf("步  比例   高度   图\n");
    for (int step = 0; step < steps; step++) {
        int pct = 0;
        if (step < lift) {
            int p   = step * 100;                   /* 抬腿段已走的细分数 */
            pct     = 400 * p * (N - p) / (N * N);  /* 4x(1-x)，转成百分比 */
        }
        int h = lift_h * pct / 100;                 /* 比例 × 真实抬腿高度 */

        printf("%2d  %3d%%  %3dmm  ", step, pct, h);
        for (int k = 0; k < pct / 5; k++) printf("#");
        printf("\n");
    }
    return 0;
}
