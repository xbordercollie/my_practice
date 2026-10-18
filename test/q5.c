#include <stdio.h>
#include <stdlib.h>

/**
 * @brief 在样本数组尾部追加一个值
 * @param samples 原数组（由调用者 malloc）
 * @param n 原元素个数
 * @param v 要追加的值
 * @return 成功返回新数组指针；失败返回 NULL，原数组仍有效
 */
int *append_sample(int *samples, int n, int v)
{
    int *new_samples = realloc(samples, (n + 1) * sizeof(int));
    if (new_samples == NULL)
        return NULL;

    new_samples[n] = v;
    return new_samples;
}

int main(void)
{
    int n = 3;
    int *s = malloc(n * sizeof(int));
    if (s == NULL)
        return 1;

    for (int i = 0; i < n; i++)
        s[i] = i * 10;

    int *tmp = append_sample(s, n, 99);
    if (tmp == NULL) {
        printf("append failed\n");
        free(s);
        return 1;
    }

    s = tmp;
    n += 1;

    printf("%d\n", s[n - 1]);
    free(s);
    return 0;
}
