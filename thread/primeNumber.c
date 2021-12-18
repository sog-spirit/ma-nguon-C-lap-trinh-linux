#include <pthread.h>
#include <stdio.h>

void computePrime(void* arg) {
    int pri = 2;
    int n = *((int*) arg);
    while(1) {
        int i;
        int nguyento = 1;
        for(i = 2; i < pri; ++i)
            if(pri % i == 0) {
                nguyento = 0;
                break;
            }
        if(nguyento) {
            if(--n == 0)
                return (void*) pri;
        }
        ++pri;
    }
    return NULL;
}

int main() {
    pthread_t thread;
    int n;
    int prime;
    printf("\nNhap n: ");
    scanf("%d", &n);

    pthread_create(&thread, NULL, &computePrime, &n);

    pthread_join(thread, (void*) &prime);
    printf("So nguyen to thu %d la %d.\n", n, prime);
}
