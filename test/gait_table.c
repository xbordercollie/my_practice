#include <stdio.h>

#define LEG_NUM 6
#define WALK 4

/* 一个函数输出一整块：标题 + 相位表 + 统计 */
static void print_phase(const char *name, int steps, const int offsets[LEG_NUM])
{
    int total = 0;      /* 全周期 ^^^ 的总数 */
    int max_lift = 0;   /* 任意一步同时抬腿的最大条数 */

    printf("=== %s (%d steps) ===\n", name, steps);
    printf("步   RR   RM   RF   LR   LM   LF  抬腿\n");

    for (int step = 0; step < steps; step++) {
        int lift = 0;
        printf("%2d", step);
        for (int leg = 0; leg < LEG_NUM; leg++) {
            int phase = (step + offsets[leg]) % steps;
            if (phase < WALK) {
                printf("  ^^^");
                lift++;
            } else {
                printf("  ---");
            }
        }
        printf("   %d\n", lift);
        total += lift;
        if (lift > max_lift) {
            max_lift = lift;
        }
    }

    printf("%s: 每步最多同时抬 %d 腿, ^^^ 总数 = %d\n\n", name, max_lift, total);
}

int main(void)
{
    static const int ripple_12[LEG_NUM] = {1, 3, 5, 7, 9, 11};
    static const int tripod_6[LEG_NUM]  = {0, 6, 0, 6, 0, 6};
    static const int tripod_8[LEG_NUM]  = {0, 8, 0, 8, 0, 8};
    static const int wave_24[LEG_NUM]   = {0, 4, 8, 12, 16, 20};
    static const int tripod_4[LEG_NUM]  = {0, 6, 0, 6, 0, 6};

    print_phase("RIPPLE_12", 12, ripple_12);
    print_phase("TRIPOD_6",  12, tripod_6);
    print_phase("TRIPOD_8",  16, tripod_8);
    print_phase("WAVE_24",   24, wave_24);
    print_phase("TRIPOD_4",  12, tripod_4);

    return 0;
}
