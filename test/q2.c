#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Config {
    char *ssid;
    int baud;
};

int config_load(struct Config *c, const char *ssid)
{
    char *new_ssid = malloc(strlen(ssid) + 1);
    if (new_ssid == NULL)
        return -1;
    strcpy(new_ssid, ssid);
    free(c->ssid);
    c->ssid = new_ssid;
    c->baud = 115200;
    return 0;
}

int main(void)
{
    struct Config c = { 0 };
    int panduan = config_load(&c, "hexapod");
    if(panduan == -1) return -1;
    panduan = config_load(&c, "hexapod-2");
    if(panduan == -1) return -1;

    printf("ssid=%s baud=%d\n", c.ssid, c.baud);
    free(c.ssid);
    return 0;
}
