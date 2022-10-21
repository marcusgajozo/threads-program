#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define n 10

typedef struct
{
    int line, column;
} Pos;

int X[n][n];
sem_t S[n][n];

pthread_barrier_t bar;

void *funcao(void *args)
{
    Pos posicao = *((Pos *)args);
    int i = posicao.line;
    int j = posicao.column;

    if (j == 0)
    {
        X[i][j] = rand() % 10;
        sem_post(&S[i][j]);
    }
    else
    {
        int line = rand() % n;
        int column = rand() % j;
        sem_wait(&S[line][column]);
        X[i][j] = X[line][column];
        sem_post(&S[i][j]);
        sem_post(&S[line][column]);
    }

    pthread_barrier_wait(&bar);
}

int main(int argc, char const *argv[])
{

    pthread_t threads[n][n];

    pthread_barrier_init(&bar, NULL, n * n + 1);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            sem_init(&S[i][j], 0, 0);
        }
    }

    Pos pos[n][n];

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            pos[i][j].line = i;
            pos[i][j].column = j;
            threads[i][j] = pthread_create(&threads[i][j], NULL, funcao, (void *)&pos[i][j]);
        }
    }

    pthread_barrier_wait(&bar);

    for (int line = 0; line < n; line++)
    {
        for (int column = 0; column < n; column++)
        {
            printf("%d, ", X[line][column]);
        }
        printf("\n");
    }

    return 0;
}
