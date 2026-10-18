#include <stdio.h>
#include <stdlib.h>

int *make_angle_table(int n)
{
    int *t = malloc(n * sizeof(int));
    if(t == NULL)
    {
	printf("wrong");
	return NULL;
    }

    for (int i = 0; i < n; i++)
        t[i] = 90;
    return t;
}

int main(void)
{
    int *angles = make_angle_table(6);
    if(angles == NULL) return -1;

    for (int i = 0; i < 6; i++)
        printf("leg%d: %d\n", i, angles[i]);
    free(angles);
    return 0;
}
