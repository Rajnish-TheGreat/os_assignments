#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/types.h>

pthread_t tid;
pthread_mutex_t mutex;
sem_t empty, full;

int buffer[20], counter, n1, n2;

void insert_item(int item)
{
    buffer[counter++] = item;
}

int remove_item()
{
    return buffer[--counter];
}

void *producer()
{
    int item;
    sleep((n1 / 2));
    item = rand() % 100;

    if (sem_wait(&empty) != 0)
    {
        printf("\nSemaphore Wait Error!\n");
    }

    pthread_mutex_lock(&mutex);
    printf("\nProducer Produced %d\n", item);
    insert_item(item);
    pthread_mutex_unlock(&mutex);

    if (sem_post(&full) != 0)
    {
        printf("\nSemaphore Post Error!\n");
    }
}

void *consumer()
{
    int item;
    sleep((n2 / 2));

    if (sem_wait(&full) != 0)
    {
        printf("\nSemaphore Wait Error!\n");
    }

    pthread_mutex_lock(&mutex);
    item = remove_item();
    printf("\nConsumer Consumed %d\n", item);
    pthread_mutex_unlock(&mutex);

    if (sem_post(&empty) != 0)
    {
        printf("\nSemaphore Post Error!\n");
    }
}

int main()
{
    int i;
    printf("\nEnter number of Producers\n");
    scanf("%d", &n1);
    printf("\nEnter number of Consumers\n");
    scanf("%d", &n2);

    if (pthread_mutex_init(&mutex, NULL) != 0)
    {
        printf("\nError in Initializing Mutex\n");
    }

    if (sem_init(&full, 0, 0) != 0)
    {
        printf("\nError in Initializing Semaphore(Full)\n");
    }

    if (sem_init(&empty, 0, 20) != 0)
    {
        printf("\nError in Initializing Semaphore(Empty)\n");
    }

    for (i = 0; i < n1; i++)
    {
        pthread_create(&tid, NULL, producer, NULL);
    }

    for (i = 0; i < n2; i++)
    {
        pthread_create(&tid, NULL, consumer, NULL);
    }

    sleep(((n1 + n2) / 2));
    return 0;
}
