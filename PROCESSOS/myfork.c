#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    pid_t pid;
    pid = fork();

    if (pid == 0)
    {

        pid = fork();
        if (pid == 0)
        {
            pid = fork(); // Criando p6
            if (pid == 0)
            {
                printf("\nProcesso p6");
                // return 0;
            }
            if (pid != 0)
            {
                // wait(NULL);
                printf("\nProcesso P5");
                // return 0;
            }
        }
        else if (pid != 0)
        {
            // wait(NULL);

            pid = fork();
            if (pid == 0)
            {
                printf("\nProcesso p7");
                // return 0;
            }
            else if (pid != 0)
            {
                // wait(NULL);
                printf("\nProcesso filho P2");
                printf("\nProcesso p5 e p7 acabou");
            }
            // return 0;
        }
    }
    else if (pid != 0)
    {
        // wait(NULL);
        pid = fork();
        if (pid == 0)
        {
            pid = fork();
            if (pid == 0)
            {
                printf("\nProcesso p4");
                // return 0;
            }
            else if (pid != 0)
            {
                // wait(NULL);
                printf("\nProcesso p3");
            }
            // return 0;
        }
        else if (pid != 0)
        {
            // wait(NULL);
            printf("\nProcesso Pai");
            printf("\nProcesso p3 e p4 acabou");
        }
    }
    sleep(2000);
    return 0;
}