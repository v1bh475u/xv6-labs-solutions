#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    printf("uptime: %d\n", uptime());
    exit(0);
}