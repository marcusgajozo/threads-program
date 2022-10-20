#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]){

    int n = atoi(argv[1]);
    int X[n][n];

    for(int j = 0; j < n; j++){
        for (int i = 0; i < n; i++){
            if (j == 0){
                X[i][j] = rand() % 10;
            }
            else{
                X[i][j] = X[rand()%n][rand()%j];
            }
        }
    }

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            printf("%d, ", X[i][j]);
        }
        printf("\n");
    }

    return 0;
}