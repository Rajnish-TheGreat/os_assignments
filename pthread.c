#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

int mat1[10][10], mat2[10][10], mat3[10][10], r1, c1, r2, c2;

void disp(int m1[10][10], int m11, int m12)
{
    for (int i = 0; i < m11; i++)
    {
        for (int j = 0; j < m12; j++)
        {
            if (j == 0)
            {
                printf("\n[  %d  ", m1[i][j]);
                if (j == m12 - 1)
                {
                    printf("]");
                }
            }
            else if (j == m12 - 1)
            {
                printf("  %d  ]", m1[i][j]);
            }
            else
            {
                printf("  %d  ", m1[i][j]);
            }
        }
    }
}

void *mult(void *arg)
{
    int *argu = (int *)arg;
    int i = argu[0], j = argu[1], k = argu[2];
    int *p = malloc(sizeof(int));
    *p = mat1[i][k] * mat2[k][j];
    pthread_exit((void *)p);
}

int main()
{
    int a, k, i, j, data[3];
    printf(" \nEnter the Matrices\n");
    printf(" \nEnter the Number of Rows in the first Matrix\n");
    scanf("%d", &r1);
    printf(" \nEnter the Number of Columns in the first Matrix\n");
    scanf("%d", &c1);
    printf(" \nEnter %d Elements of first Matrix\n", r1 * c1);
    for (i = 0; i < r1; i++)
    {
        for (j = 0; j < c1; j++)
        {
            scanf(" %d", &mat1[i][j]);
        }
    }
    printf(" \nEnter the Number of Rows in the second Matrix\n");
    scanf("%d", &r2);
    printf(" \nEnter the Number of Columns in the second Matrix\n");
    scanf("%d", &c2);
    printf(" \nEnter %d Elements of second Matrix\n", r2 * c2);
    for (i = 0; i < r2; i++)
    {
        for (j = 0; j < c2; j++)
        {
            scanf(" %d", &mat2[i][j]);
        }
    }
    printf(" \nMatrix 1 is\n");
    disp(mat1, r1, c1);
    printf(" \n");
    printf(" \nMatrix 2 is\n");
    disp(mat2, r2, c2);
    printf(" \n");
    if (c1 != r2)
    {
        printf(" \nThe Number of Rows or Columns isn't Same\n");
    }
    else
    {
        void *p;
        for (i = 0; i < r1; i++)
        {
            for (j = 0; j < c2; j++)
            {
                for (k = 0; k < c1; k++)
                {
                    data[0] = i;
                    data[1] = j;
                    data[2] = k;
                    pthread_t th;
                    if (pthread_create(&th, NULL, mult, (void *)data))
                    {
                        printf("\nError in Thread Creation\n");
                    }
                    else
                    {
                        pthread_join(th, &p);
                        mat3[i][j] += *((int *)p);
                    }
                }
            }
        }
        printf("\nThe Multiplication is\n");
        disp(mat3, r1, c2);
        printf("\n");
    }
    return 0;
}
