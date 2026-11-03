
#include <stdio.h>

int main()
{
    int n, m;
    int alloc[10][10], max[10][10], need[10][10];
    int avail[10], finish[10] = {0}, safe[10];

    int i, j, k, count = 0, found;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resources: ");
    scanf("%d", &m);

    printf("Enter Allocation Matrix:\n");

    for(i = 0; i < n; i++)
    {
        for(j = 0; j < m; j++)
        {
            scanf("%d", &alloc[i][j]);
        }
    }

    printf("Enter Max Matrix:\n");

    for(i = 0; i < n; i++)
    {
        for(j = 0; j < m; j++)
        {
            scanf("%d", &max[i][j]);
        }
    }

    printf("Enter Available Resources:\n");

    for(j = 0; j < m; j++)
    {
        scanf("%d", &avail[j]);
    }

    // Calculate Need Matrix

    for(i = 0; i < n; i++)
    {
        for(j = 0; j < m; j++)
        {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    // Find Safe Sequence

    while(count < n)
    {
        found = 0;

        for(i = 0; i < n; i++)
        {
            if(finish[i] == 0)
            {
                for(j = 0; j < m; j++)
                {
                    if(need[i][j] > avail[j])
                        break;
                }

                if(j == m)
                {
                    for(k = 0; k < m; k++)
                    {
                        avail[k] += alloc[i][k];
                    }

                    safe[count] = i;
                    count++;

                    finish[i] = 1;
                    found = 1;
                }
            }
        }

        if(found == 0)
            break;
    }

    if(count == n)
    {
        printf("\nSystem is in a safe state.\n");

        printf("Safe Sequence: ");

        for(i = 0; i < n; i++)
        {
            printf("P%d ", safe[i]);
        }

        printf("\n");
    }
    else
    {
        printf("\nSystem is not in a safe state.\n");
    }

    return 0;
}
