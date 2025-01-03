#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
    printf("memfo: %ld pages free\n", memfo());
    exit(0);
}