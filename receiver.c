#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int main()
{
    int fd1, fd2;
    FILE *fp;
    char str[500];
    char result[200];

    int characters = 0, words = 0, lines = 0;
    int inWord = 0;

    fd1 = open("fifo1", O_RDONLY);

    if (fd1 == -1)
    {
        perror("open");
        return 1;
    }

    fp = fopen("output.txt", "w");

    if (fp == NULL)
    {
        perror("fopen");
        close(fd1);
        return 1;
    }

    FILE *fifo = fdopen(fd1, "r");

    if (fifo == NULL)
    {
        perror("fdopen");
        fclose(fp);
        close(fd1);
        return 1;
    }

    while (fgets(str, sizeof(str), fifo) != NULL)
    {
        if (strcmp(str, "END\n") == 0 || strcmp(str, "END") == 0)
            break;

        fputs(str, fp);

        characters += strlen(str);
        lines++;

        for (int i = 0; str[i] != '\0'; i++)
        {
            if (str[i] == ' ' || str[i] == '\n' || str[i] == '\t')
                inWord = 0;
            else if (inWord == 0)
            {
                words++;
                inWord = 1;
            }
        }
    }

    fclose(fp);
    fclose(fifo);

    sprintf(result,
            "Characters = %d\nWords = %d\nLines = %d\n",
            characters, words, lines);

    fd2 = open("fifo2", O_WRONLY);

    if (fd2 == -1)
    {
        perror("open fifo2");
        return 1;
    }

    write(fd2, result, strlen(result));

    close(fd2);

    printf("Text saved in output.txt\n");

    return 0;
}
