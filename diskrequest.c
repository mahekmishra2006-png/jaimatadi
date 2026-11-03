
#include <stdio.h>
#include <stdlib.h>

#define MAX 100

void sort(int a[], int n)
{
    int i, j, temp;

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
}

// SSTF Algorithm
void sstf(int a[], int n, int head)
{
    int visited[MAX] = {0};
    int total = 0, i, j, min, pos;

    printf("\nSSTF Order: %d", head);

    for(i = 0; i < n; i++)
    {
        min = 9999;
        pos = -1;

        for(j = 0; j < n; j++)
        {
            if(!visited[j] && abs(a[j] - head) < min)
            {
                min = abs(a[j] - head);
                pos = j;
            }
        }

        visited[pos] = 1;
        total += abs(a[pos] - head);
        head = a[pos];

        printf(" -> %d", head);
    }

    printf("\nTotal Head Movement = %d\n", total);
}

// SCAN Algorithm
void scan(int a[], int n, int head, int diskSize)
{
    int i, total = 0;
    int b[MAX];

    for(i = 0; i < n; i++)
        b[i] = a[i];

    b[n] = head;
    sort(b, n+1);

    int pos = 0;

    for(i = 0; i <= n; i++)
    {
        if(b[i] == head)
        {
            pos = i;
            break;
        }
    }

    printf("\nSCAN Order: %d", head);

    // Moving towards higher cylinder numbers
    for(i = pos+1; i <= n; i++)
    {
        total += abs(b[i] - head);
        head = b[i];
        printf(" -> %d", head);
    }

    // Go to the end of the disk
    total += abs((diskSize-1) - head);
    head = diskSize-1;
    printf(" -> %d", head);

    // Reverse direction
    for(i = pos-1; i >= 0; i--)
    {
        total += abs(b[i] - head);
        head = b[i];
        printf(" -> %d", head);
    }

    printf("\nTotal Head Movement = %d\n", total);
}

// C-LOOK Algorithm
void clook(int a[], int n, int head)
{
    int i, total = 0;
    int b[MAX];

    for(i = 0; i < n; i++)
        b[i] = a[i];

    b[n] = head;
    sort(b, n+1);

    int pos = 0;

    for(i = 0; i <= n; i++)
    {
        if(b[i] == head)
        {
            pos = i;
            break;
        }
    }

    printf("\nC-LOOK Order: %d", head);

    // Move towards higher cylinders
    for(i = pos+1; i <= n; i++)
    {
        total += abs(b[i] - head);
        head = b[i];
        printf(" -> %d", head);
    }

    // Jump to the lowest request
    if(pos > 0)
    {
        total += abs(head - b[0]);
        head = b[0];
        printf(" -> %d", head);
    }

    // Continue towards higher cylinders
    for(i = 1; i < pos; i++)
    {
        total += abs(b[i] - head);
        head = b[i];
        printf(" -> %d", head);
    }

    printf("\nTotal Head Movement = %d\n", total);
}

int main()
{
    int a[MAX], n, head, diskSize, i;

    printf("Enter number of requests: ");
    scanf("%d", &n);

    printf("Enter disk requests: ");
    for(i = 0; i < n; i++)
        scanf("%d", &a[i]);

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("Enter disk size: ");
    scanf("%d", &diskSize);

    sstf(a, n, head);
    scan(a, n, head, diskSize);
    clook(a, n, head);

    return 0;
}
command: gcc diskrequest.c -o diskrequest
./diskrequest
