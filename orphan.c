#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    int n, a[20], i, j, temp;
    pid_t pid;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter elements:\n");
    for(i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }

    pid = fork();

    if(pid == 0)
    {
        // Child Process - Selection Sort
        printf("\nChild Process\n");
        printf("Child PID = %d\n", getpid());

        for(i = 0; i < n-1; i++)
        {
            int min = i;

            for(j = i+1; j < n; j++)
            {
                if(a[j] < a[min])
                    min = j;
            }

            temp = a[i];
            a[i] = a[min];
            a[min] = temp;
        }

        printf("Sorted Array by Child (Selection Sort): ");
        for(i = 0; i < n; i++)
            printf("%d ", a[i]);

        printf("\n");
    }
    else if(pid > 0)
    {
        // Parent Process - Bubble Sort
        wait(NULL);

        printf("\nParent Process\n");
        printf("Parent PID = %d\n", getpid());

        for(i = 0; i < n-1; i++)
        {
            for(j = 0; j < n-i-1; j++)
            {
                if(a[j] > a[j+1])
                {
                    temp = a[j];
                    a[j] = a[j+1];
                    a[j+1] = temp;
                }
            }
        }

        printf("Sorted Array by Parent (Bubble Sort): ");
        for(i = 0; i < n; i++)
            printf("%d ", a[i]);

        printf("\n");
    }
    else
    {
        printf("Fork failed");
    }

    return 0;
}


//orphan
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int main()
{
    pid_t pid;

    pid = fork();

    if(pid == 0)
    {
        // Child Process
        sleep(2);

        printf("\nChild Process ID: %d\n", getpid());
        printf("Original Parent ID: %d\n", getppid());

        printf("Child is running after parent terminates...\n");

        sleep(3);

        printf("New Parent Process ID: %d\n", getppid());
    }
    else if(pid > 0)
    {
        // Parent Process
        printf("Original Parent Process ID: %d\n", getpid());
        printf("Child Process ID: %d\n", pid);

        printf("\nParent process is terminating...\n");
        exit(0);
    }
    else
    {
        printf("Fork failed");
    }

    return 0;
}

//zombie

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
    pid_t pid;

    pid = fork();

    if(pid == 0)
    {
        // Child Process
        printf("Child Process ID: %d\n", getpid());
        printf("Child Process is exiting...\n");
        exit(0);
    }
    else if(pid > 0)
    {
        // Parent Process
        printf("Parent Process ID: %d\n", getpid());
        printf("Child Process ID: %d\n", pid);

        printf("\nParent is sleeping for 30 seconds...\n");
        printf("Check the child process using another terminal.\n");

        sleep(30);

        wait(NULL);

        printf("\nParent process is exiting...\n");
    }
    else
    {
        printf("Fork failed");
    }

    return 0;
}



command: gcc orphan.c -o orphan
./orphan