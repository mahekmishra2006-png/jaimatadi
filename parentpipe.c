
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int main()
{
    int p1[2], p2[2];
    pid_t pid;

    char filename[100];
    char buffer[500];

    pipe(p1);
    pipe(p2);

    pid = fork();

    if(pid < 0)
    {
        printf("Fork failed.\n");
        return 1;
    }

    else if(pid > 0)
    {
        // Parent process

        close(p1[0]);
        close(p2[1]);

        printf("Enter file name: ");
        scanf("%99s", filename);

        write(p1[1], filename, strlen(filename) + 1);

        close(p1[1]);

        printf("\nFile contents received from child:\n");

        int n;
        while((n = read(p2[0], buffer, sizeof(buffer))) > 0)
        {
            write(1, buffer, n);
        }

        close(p2[0]);

        wait(NULL);
    }

    else
    {
        // Child process

        FILE *fp;

        close(p1[1]);
        close(p2[0]);

        read(p1[0], filename, sizeof(filename));

        close(p1[0]);

        fp = fopen(filename, "r");

        if(fp == NULL)
        {
            char msg[] = "File not found.\n";
            write(p2[1], msg, strlen(msg));
        }
        else
        {
            int n;

            while((n = fread(buffer, 1, sizeof(buffer), fp)) > 0)
            {
                write(p2[1], buffer, n);
            }

            fclose(fp);
        }

        close(p2[1]);
        exit(0);
    }

    return 0;
}
command:gcc parentpipe.c -o parentpipe
./parentpipe
