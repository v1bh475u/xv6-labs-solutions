#include "kernel/types.h"
#include "user/user.h"
#include "kernel/param.h"

int main(int argc, char *argv[])
{
    int index = 0;
    int n_argc = 1;
    char *n_argv[MAXARG];
    if (strcmp(argv[1], "-n") == 0)
        index = 3;
    else
        index = 1;
    n_argv[0] = malloc(strlen(argv[index]) + 1);
    strcpy(n_argv[0], argv[index]);
    for (int i = index + 1; i < argc; i++)
    {
        n_argv[n_argc] = malloc(strlen(argv[i]) + 1);
        strcpy(n_argv[n_argc], argv[i]);
        n_argc++;
    }
    n_argv[n_argc] = malloc(128);
    char buf;
    int i = 0;
    while (read(0, &buf, 1))
    {
        if (buf == '\n')
        {
            n_argv[n_argc][i++] = '\0';
            if (fork() == 0)
            {
                exec(n_argv[0], n_argv);
            }
            else
            {
                i = 0;
                wait(0);
            }
        }
        else
        {
            n_argv[n_argc][i++] = buf;
        }
    }
    exit(0);
}