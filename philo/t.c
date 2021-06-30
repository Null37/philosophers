#include "philo.h"
 pthread_mutex_t l;
void *h1(void *a)
{
    int k  = -1;
    int *b = (int *)a;
    pthread_mutex_lock(&l);
    while(++k < 1000000)
    {
        (*b)++;
       //. printf("k = %d\n", k);
    }
    pthread_mutex_unlock(&l);
    return NULL;
}

int main()
{
    // int *b;
    pthread_t t;
    pthread_t t1;
   
    pthread_mutex_init(&l, NULL);
    int *c;
    int b = 0;
    pthread_create(&t, NULL, h1, &b);
    pthread_create(&t1, NULL, h1, &b);
    pthread_join(t, NULL);
    pthread_join(t1, NULL);
   printf("c = %d", b);
}