#include "philo/philo.h"


void	my_sleep(int sleep)
{
	size_t	ms;
	size_t	mu;
	size_t old_time;
	size_t new_time;
    size_t new_slep;
	struct timeval time;
    ms = 0;
    mu = 0;
    old_time = 0;
    new_time = 0;
	gettimeofday(&time, NULL);
	ms = time.tv_sec * 1000;
	mu = time.tv_usec / 1000;
	old_time = mu + ms;
    if (sleep > 10)
        new_slep = sleep - 10;
    else if (sleep == 5)
        new_slep = sleep - 3;
    else if (sleep < 5)
        new_slep = 0;
	usleep(new_slep * 1000);
	while (new_time != sleep)
	{
		gettimeofday(&time, NULL);
    	new_time = ((time.tv_usec / 1000) + (time.tv_sec * 1000)) - old_time;
	}
}

int main(int ac, char *av[])
{
    int mymili  = atoi(av[1]);
    struct timeval a;
    long long ms;
    long long mu;
    long long to_time;
    gettimeofday(&a, NULL);

    ms = a.tv_sec * 1000;
    mu = a.tv_usec / 1000;
    to_time = mu + ms;
    fprintf(stderr, "mili befor ==> %lld\n", to_time);
    my_sleep(mymili);
    gettimeofday(&a, NULL);
    ms = a.tv_sec * 1000;
    mu = a.tv_usec / 1000;
    to_time = mu + ms;
    fprintf(stderr, "mili after ==> %lld", to_time);
}