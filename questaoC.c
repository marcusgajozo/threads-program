#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int n;
int **X;

pthread_barrier_t bar;
pthread_barrier_t bar2;

void *funcao(void *line)
{
    int aux = (int)line;
    for (int column = 0; column < n; column++)
    {
        if (column == 0)
        {
            X[aux][column] = rand() % 10;
        }
        else
        {
            X[aux][column] = X[rand() % n][rand() % column];
        }
        pthread_barrier_wait(&bar);
    }
    pthread_barrier_wait(&bar2);
    pthread_exit(NULL);
}

int main(int argc, char const *argv[])
{

    n = atoi(argv[1]);

    X = malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++)
    {
        X[i] = malloc(n * sizeof(int));
    }

    pthread_t threads[n];

    pthread_barrier_init(&bar, NULL, n);
    pthread_barrier_init(&bar2, NULL, n + 1);

    for (int line = 0; line < n; line++)
    {
        threads[line] = pthread_create(&threads[line], NULL, funcao, (void *)line);
    }

    pthread_barrier_wait(&bar2);

    for (int line = 0; line < n; line++)
    {
        for (int column = 0; column < n; column++)
        {
            int *aux = X[line];
            printf("%d, ", aux[column]);
        }
        printf("\n");
    }

    for (int i = 0; i < n; i++)
    {
        free(X[i]);
    }
    free(X);

    return 0;
}
