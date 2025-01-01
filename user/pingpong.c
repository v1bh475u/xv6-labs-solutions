#include "kernel/types.h"
#include "user/user.h"
#define MSGSIZE 4
int main(int argc, char *argv[])
{
    int p1[2], p2[2];
    pipe(p1);
    pipe(p2);
    char buf[MSGSIZE];
    int pid = fork();
    if (pid == 0)
    {
        close(p1[0]);
        close(p2[1]);
        if (read(p2[0], buf, 4) == 4)
            printf("%d: received %s\n", getpid(), buf);
        if (write(p1[1], "pong", 4) < 0)
            fprintf(2, "error: child write failed\n");
        close(p1[1]);
        close(p2[0]);
    }
    else
    {
        close(p1[1]);
        close(p2[0]);
        if (write(p2[1], "ping", 4) < 0)
            fprintf(2, "error: child write failed\n");
        if (read(p1[0], buf, 4) == 4)
            printf("%d: received %s\n", getpid(), buf);
        close(p1[0]);
        close(p2[1]);
    }

    exit(0);
}