#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/types.h>

int readers = 0, c;
pthread_mutex_t mutex;
sem_t write;

void *reader(void *r)
{
    pthread_mutex_lock(&mutex);

    if ((readers++) == 1)
    {
        sem_wait(&write);
    }

    printf("\nReader %d reads count as %d\n", (*(int *)r), c);

    if ((readers--) == 0)
    {
        sem_post(&write);
    }

    pthread_mutex_unlock(&mutex);
}

void *writer(void *w)
{
    sem_wait(&write);
    c *= 2;
    printf("\nWriter %d is edits count to %d\n", *((int *)w), c);
    sem_post(&write);
}

int main()
{
    int i, n1, n2;
    printf("\nEnter number of Readers\n");
    scanf("%d", &n1);
    printf("\nEnter number of Writers\n");
    scanf("%d", &n2);
    printf("\nEnter Initial Value for Count(natural no)\n");
    scanf("%d", &c);
    i = n1 <= n2 ? n2 : n1;
    int a[i];
    pthread_t reading[n1], writing[n2];
    if (pthread_mutex_init(&mutex, NULL) != 0)
    {
        printf("\nError in Initializing Mutex!\n");
    }

    if (sem_init(&write, 0, 1) != 0)
    {
        printf("\nError in Initializing Semaphore!\n");
    }

    for (i = 0; i < n1; i++)
    {
        a[i] = i;
        pthread_create(&reading[i], NULL, (void *)reader, (void *)&a[i]);
    }

    for (i = 0; i < n2; i++)
    {
        a[i] = i;
        pthread_create(&writing[i], NULL, (void *)writer, (void *)&a[i]);
    }

    for (i = 0; i < n1; i++)
    {
        pthread_join(reading[i], NULL);
    }

    for (i = 0; i < n2; i++)
    {
        pthread_join(writing[i], NULL);
    }

    return 0;
}
