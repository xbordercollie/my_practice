#include <stdio.h>
#include <stdlib.h>

struct Session {
    char *rx;
    char *tx;
    int ready;
};

/**
 * @brief 创建一个收发会话；rx 与 tx 共用同一块缓冲
 * @return 成功返回会话指针，失败返回 NULL
 */
struct Session *session_new(void)
{
    struct Session *s = malloc(sizeof(struct Session));
    if (s == NULL)
        return NULL;

    s->rx = malloc(64);
    if (s->rx == NULL) {
        free(s);
        return NULL;
    }

    s->tx = s->rx;
    s->ready = 1;
    return s;
}

/**
 * @brief 关闭会话；rx 与 tx 是同一块内存，只释放一次
 * @param s 会话指针
 */
void session_close(struct Session *s)
{
    free(s->tx);
    free(s);
}

int main(void)
{
    struct Session *s = session_new();
    if (s == NULL) {
        printf("session_new failed\n");
        return 1;
    }

    session_close(s);
    printf("closed\n");
    return 0;
}
