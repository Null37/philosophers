#include "philo/philo.h"


int main(int ac, char *av[])
{
    int mymili  = atoi(av[1]);
    struct timeval a;
    long long ms;
    long long mu;
    long long to_time;
    gettimeofday(&a, NULL);

    ms = a.tv_sec * 1000000;
    mu = a.tv_usec / 1000;
    to_time = ms + mu;
    fprintf(stderr, "mili befor ==> %lld\n", to_time);
    usleep(mymili * 1000);
    gettimeofday(&a, NULL);
    ms = a.tv_sec * 1000000;
    mu = a.tv_usec / 1000;
    to_time = ms + mu;
    fprintf(stderr, "mili after ==> %lld", to_time);
}