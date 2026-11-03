
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>
#include <ctype.h>

#define FIFO1 "/tmp/fifo1"
#define FIFO2 "/tmp/fifo2"

int main()
{
    int fd1, fd2;
    char str[500], result[200], ch;
    int characters = 0, words = 0, lines = 0;
    int inword = 0;
    pid_t pid;

    mkfifo(FIFO1, 0666);
    mkfifo(FIFO2, 0666);

    pid = fork();

    if(pid > 0)
    {
        // FIRST PROCESS (SENDER)

        printf("Enter sentences (# to stop):\n");

        int i = 0;

        while(i < 499)
        {
            ch = getchar();

            if(ch == '#')
                break;

            str[i++] = ch;
        }

        str[i] = '\0';

        fd1 = open(FIFO1, O_WRONLY);
        write(fd1, str, strlen(str) + 1);
        close(fd1);

        // Read result from second pipe
        fd2 = open(FIFO2, O_RDONLY);

        int n = read(fd2, result, sizeof(result) - 1);
        if(n > 0)
        {
            result[n] = '\0';
            printf("\nResult received from second process:\n%s\n", result);
        }

        close(fd2);

        wait(NULL);

        unlink(FIFO1);
        unlink(FIFO2);
    }
    else if(pid == 0)
    {
        // SECOND PROCESS (RECEIVER)

        fd1 = open(FIFO1, O_RDONLY);
        read(fd1, str, sizeof(str) - 1);
        close(fd1);

        str[499] = '\0';

        for(int i = 0; str[i] != '\0'; i++)
        {
            characters++;

            if(isspace((unsigned char)str[i]))
                inword = 0;
            else if(inword == 0)
            {
                words++;
                inword = 1;
            }

            if(str[i] == '\n')
                lines++;
        }

        if(characters > 0 && str[characters - 1] != '\n')
            lines++;

        // Write result into file
        FILE *fp = fopen("output.txt", "w");

        fprintf(fp, "Characters: %d\n", characters);
        fprintf(fp, "Words: %d\n", words);
        fprintf(fp, "Lines: %d\n", lines);

        fclose(fp);

        // Read file and send contents through second pipe
        fp = fopen("output.txt", "r");

        fd2 = open(FIFO2, O_WRONLY);

        while(fgets(result, sizeof(result), fp) != NULL)
        {
            write(fd2, result, strlen(result));
        }

        close(fd2);
        fclose(fp);

        exit(0);
    }

    return 0;
}


command: gcc FIFO.c -o FIFO
./FIFO
