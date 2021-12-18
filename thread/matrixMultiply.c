#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX 4

void* multiplyMatrix(void* arg) {
    int* data = (int*) arg;
    int k = 0, i = 0;

    int x = data[0];
    for(i = 1; i <= x; i++)
        k += data[i]*data[i+x];

    int* p = (int*) malloc(sizeof(int));
    *p = k;
    pthread_exit(p);
}
int main() {
    int matrixA[MAX][MAX];
    int matrixB[MAX][MAX];

    int noRowA, noColA, noRowB, noColB;

    printf("So hang ma tran A: ");
    scanf("%d", &noRowA);
    printf("So cot ma tran A: ");
    scanf("%d", &noColA);

    printf("So hang ma tran B: ");
    scanf("%d", &noRowB);
    printf("So cot ma tran A: ");
    scanf("%d", &noColB);

    if(noRowA != noColB) {
        printf("Loi! So hang ma tran A phai bang so cot ma tran B.");
        return 0;
    }

    printf("\nNhap ma tran A:\n");
    for(int i = 0; i < noRowA; i++) {
        for(int j = 0; j < noColA; j++) {
            printf("A[%d][%d] = ", i+1, j+1);
            scanf("%d", &matrixA[i][j]);
        }
    }

    printf("\nNhap ma tran B:\n");
    for(int i = 0; i < noRowB; i++) {
        for(int j = 0; j < noColB; j++) {
            printf("A[%d][%d] = ", i+1, j+1);
            scanf("%d", &matrixB[i][j]);
        }
    }

    int numberOfThread = noRowA * noColB;

    pthread_t* threads;
    threads = (pthread_t*) malloc(numberOfThread * sizeof(pthread_t));

    int count = 0;
    int* data = NULL;
    
    for(int i = 0; i < noRowA; i++) {
        for(int j = 0; j < noColB; j++) {
            data = (int*) malloc((20) * sizeof(int));
            data[0] = noColA;

            for(int k = 0; k < noColA; k++)
                data[k+1] = matrixA[i][k];

            for(int k = 0; k < noRowB; k++)
                data[k + noColA + 1] = matrixB[k][j];

            pthread_create(&threads[count++], NULL, multiplyMatrix, (void*) (data));
        }
    }

    printf("\nKet qua nhan ma tran:\n");
    for(int i = 0; i < numberOfThread; i++) {
        void* k;

        pthread_join(threads[i], &k);

        int* p = (int*) k;
        printf("%d ", *p);

        if((i + 1) % noColB == 0)
            printf("\n");
    }
    return 0;
}
