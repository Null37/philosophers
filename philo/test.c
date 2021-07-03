#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <signal.h>


typedef struct s_all
{

    int k;

}   t_all;

t_all	*all_t(void)
{
	static t_all	all;

	return (&all);
}
void  hello(int k)
{
    t_all *all;
	all = all_t();
    all->k = 100;
    fprintf(stderr, "%d ==> hello", all->k);
    sleep(1);
}


int main()
{
    t_all *all;
	all = all_t();
    all->k = 1;
    signal(SIGINT, hello);
    while(1)
    {
        usleep(5000);
        all->k= 500;
        printf("%d", all->k);
    }
}