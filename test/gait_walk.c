#include <stdio.h>

int main(void)
{
    const double L = 40.0;	/* 步长 mm */
    const double H = 20.0;	/* 抬腿高度 mm */
    const int walk = 4;		/* 行走步数 */
    const int step_s = 12;	/* 总步数 */

    int step, s;

    printf("x: ");
    for(step=0; step<step_s; step++) {
	double x;
	if(step<walk) {
	    x = L * (step - 2) / 4;
	    printf("%.1f\t", x);
	}
	else {
	    s = step - 4;
	    x = L * (4 - s) / 8;
	    printf("%.1f\t", x);
	}
    }
    printf("\n");

    printf("y: ");
    for(step=0; step<step_s; step++) {
	double y;
	if(step<walk) {
	    y = H * step * (4 - step) / 4;
	    printf("%.1f\t", y);
	}
	else {
	    y = 0;
	    printf("%.1f\t", y);
	}
    }
    printf("\n");

    return 0;
}
