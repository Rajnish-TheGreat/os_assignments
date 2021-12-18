#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define N 5
#define LEFT (i + 4) % N
#define RIGHT (i + 1) % N
#define THINKING 0
#define HUNGRY 1
#define EATING 2

int state[N], philosopher_num[N];
sem_t mutex, sem_phil[N];

void test(int i)
{
    if (state[i] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING)
    {
        state[i] = 2;
        printf("Philosopher %d is eating\n", i);
    }
}

void takechops(int i)
{
    sem_wait(&mutex);
    state[i] = HUNGRY;
    printf("Philosopher %d is hungry\n", i);
    test(i);
    sem_post(&mutex);
}

void putchops(int i)
{
    sem_wait(&mutex);
    state[i] = THINKING;
    printf("Philosopher %d is thinking\n", i);
    test(LEFT);
    test(RIGHT);
    sem_post(&mutex);
}

void *philosopher(void *param)
{
    int i = *((int *)param);

    while (1)
    {
        sleep(1);
        takechops(i);
        sleep(2);
        putchops(i);
    }
}

int main()
{
    int k;
    pthread_t tid[N];

    for (k = 0; k < N; k++)
    {
        philosopher_num[k] = k;
    }

    sem_init(&mutex, 0, 1);

    for (k = 0; k < N; k++)
    {
        sem_init(&sem_phil[k], 0, 0);
    }

    for (k = 0; k < N; k++)
    {
        pthread_create(&tid[k], NULL, philosopher, &philosopher_num[k]);
    }

    for (k = 0; k < N; k++)
    {
        pthread_join(tid[k], NULL);
    }

    return 0;
}
