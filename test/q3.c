#include <stdio.h>

struct Leg {
    int id;
    int angle;
};

struct Leg *find_leg(struct Leg *arr, int n, int id)
{
    struct Leg *tmp;
    for (int i = 0; i < n; i++) {
        if (arr[i].id == id) {
            tmp = &arr[i];
            return tmp;
        }
    }
    return NULL;
}

int main(void)
{
    struct Leg legs[3] = {{0, 90}, {1, 45}, {2, 0}};

    struct Leg *p = find_leg(legs, 3, 1);
    if(p != NULL) p->angle = 60;
    printf("leg1 = %d\n", legs[1].angle);

    struct Leg *q = find_leg(legs, 3, 9);
    if(q != NULL)  q->angle = 60;
    printf("leg1 = %d\n", legs[1].angle);
    return 0;
}
