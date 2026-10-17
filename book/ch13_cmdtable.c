#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct State {
	int x;
	int gait;
	int height;
};

struct Command {
	const char *name;                                    /* 命令名，不含 '!' */
	void (*handler)(struct State *st, const char *arg);  /* 处理函数 */
};

static void cmd_f(struct State *st, const char *arg)
{
	(void)arg;              /* 这条命令不用参数，消 unused 警告 */
	st->x = 60;
	printf("MOVE FORWARD\n");
}

static void cmd_g(struct State *st, const char *arg)
{
	int num = atoi(arg);
	if(arg[0]<'0' || arg[0]>'4' || arg[1] != '\0')
	{
		printf("INVALID G\n");
		return;
	}
	else st->gait = num;
	printf("GAIT\t%d\n", st->gait);
}

static void cmd_ht(struct State *st, const char *arg)
{
	int num = atoi(arg);
	if(num >90 ) num = 90;
	else if(num < -90) num = -90;
	st->height = num;
	printf("HEIGHT\t%d\n", st->height);
}

static void cmd_s(struct State *st, const char *arg)
{
	(void)arg;
	st->x = 0;
	printf("STOP\n");
}

int main(void)
{
	struct State st = {0, 0, 0};
	struct Command table[] = {
		{ "F", cmd_f },
		{ "G", cmd_g },
		{ "HT", cmd_ht },
		{ "S", cmd_s },
	};
	char line[64];

	while (scanf("%63s", line) == 1) {
		int found = 0;
		for (int i = 0; i < (int)(sizeof table / sizeof table[0]); i++) {
			size_t n = strlen(table[i].name);
			if (strncmp(line + 1, table[i].name, n) == 0) {
				table[i].handler(&st, line + 1 + n);
				found = 1;
				break;
			}
		}
		if(!found) printf("UNKNOWN:%s\n", line + 1);
		printf("state x=%d gait=%d height=%d\n", st.x, st.gait, st.height);
	}
	return 0;
}
