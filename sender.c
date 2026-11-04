#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main()
{
    int fd1, fd2;
    char str[100];
    char result[200];

    // Create FIFO files automatically
    if(mkfifo("fifo1", 0666) == -1 && errno != EEXIST)
    {
        perror("mkfifo fifo1");
        return 1;
    }

    if(mkfifo("fifo2", 0666) == -1 && errno != EEXIST)
    {
        perror("mkfifo fifo2");
        return 1;
    }

    printf("Waiting for receiver...\n");

    // Open first FIFO for writing
    fd1 = open("fifo1", O_WRONLY);

    if(fd1 == -1)
    {
        perror("open fifo1");
        return 1;
    }

    printf("Enter messages (type END to stop):\n");

    // Send messages to receiver
    while(1)
    {
        fgets(str, sizeof(str), stdin);

        if(strcmp(str, "END\n") == 0 ||
           strcmp(str, "END") == 0)
            break;

        write(fd1, str, strlen(str));
    }

    close(fd1);

    // Open second FIFO for reading
    fd2 = open("fifo2", O_RDONLY);

    if(fd2 == -1)
    {
        perror("open fifo2");
        return 1;
    }

    // Receive result from receiver
    int n = read(fd2, result, sizeof(result) - 1);

    if(n > 0)
    {
        result[n] = '\0';
        printf("\nResult from receiver:\n%s", result);
    }

    close(fd2);

    return 0;
}
