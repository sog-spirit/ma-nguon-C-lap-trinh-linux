#include <pthread.h>
#include <stdio.h>

void* compute_prime (void* arg) {
    int pri = 2;
    int n = *((int*) arg);
    while (1) {
        int i;
        int nguyento = 1;
        for ( i= 2; i < pri; ++i)
            if (pri % i == 0) {
                nguyento = 0;
                break;
            }
            if (nguyento) {
                if (--n == 0)
                    return (void*) pri;
            }
        ++pri;
    }
    return NULL;
}
int main() {
    pthread_t thread[6];
    int n = 5;
    int prime[6];
    for(int i = 1; i <= n; i++) {
        pthread_create(&thread[i], NULL, &compute_prime, &i);
        pthread_join(thread[i], (void**) &prime[i]);
        printf("So nguyen to thu %d la: %d\n", i+1, prime[i]);
    }
    pthread_exit(NULL);
    return 0;
}
