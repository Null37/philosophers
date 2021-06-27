/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssamadi <ssamadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 18:54:13 by ssamadi           #+#    #+#             */
/*   Updated: 2021/06/27 13:21:17 by ssamadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_mutex_t lock;


t_all	*all_t(void)
{
	static t_all	all;

	return (&all);
}
void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	unsigned int	i;

	i = 0;
	if (s)
	{
		while (s[i] != '\0')
		{
			write(fd, &s[i], 1);
			i++;
		}
	}
}

void	ft_putnbr_fd(int nbr, int fd)
{
	unsigned int	num;

	num = nbr;
	if (nbr < 0)
	{
		ft_putchar_fd('-', fd);
		num = num * -1;
	}
	if (num < 10)
	{
		ft_putchar_fd(num + 48, fd);
	}
	if (num >= 10)
	{
		ft_putnbr_fd(num / 10, fd);
		ft_putchar_fd(num % 10 + 48, fd);
	}
}

void	print_to(char *str, int n)
{
	t_all *all;

	all = all_t();
	pthread_mutex_lock(&all->write_lock);
	ft_putstr_fd("Philo ", 1);
	ft_putnbr_fd(n, 1);
	ft_putstr_fd(" ", 1);
	ft_putstr_fd(str, 1);
	ft_putstr_fd("\n", 1);
	pthread_mutex_unlock(&all->write_lock);
}

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


void *phil_test(void *arg)
{
	t_all *all;

	all = all_t();
	pthread_mutex_t die;
	pthread_mutex_init(&die, NULL);
	struct timeval time;
	gettimeofday(&time, NULL);
	t_philo_data  *p = (t_philo_data*)arg;
	// pthread_mutex_lock(&die);
	int r = 0;
	// while(crr - last <  all->time_to_die && ar5 < a)
	// {
	// pthread_mutex_unlock(&die);
		pthread_mutex_lock(&all->forks[p->id - 1]);
		print_to("has taken a fork 1 ", p->id);
		pthread_mutex_lock(&all->forks[(p->id) % all->number_philo]);
		print_to("has taken a fork 2 ", p->id);
		print_to("is etaing", p->id);
		// lst-timeeat = urrent;
		// a++;
		my_sleep(all->time_to_eat);
		pthread_mutex_unlock(&all->forks[p->id - 1]);
		pthread_mutex_unlock(&all->forks[(p->id) % all->number_philo]);
		print_to("is sleeping", p->id);
		my_sleep(all->time_to_sleep);
		print_to("is thinking", p->id);
	// }
	return NULL;
}

t_philo_data *aloc_stuct(t_philo_data *philo)
{
	t_all *all;

	all = all_t();
	philo = malloc(all->number_philo * (sizeof(t_philo_data *)));
	return (philo);
}

int main(int ac, char *av[])
{
	int i = atoi(av[1]);
	pthread_t philo[i];
	t_all *all;
	all = all_t();
	t_philo_data *ph_s;
	all->number_philo = i;
	ph_s = aloc_stuct(ph_s);
	all->time_to_die = atoi(av[2]);
	all->time_to_eat = atoi(av[3]);
	all->time_to_sleep = atoi(av[4]);
	all->forks = malloc(sizeof(pthread_mutex_t) * i);
	pthread_mutex_init(&all->write_lock, NULL);
	int j;
	j = 0;
	while (j < all->number_philo )
	{
		ph_s[j].id = j + 1;
		ph_s[j].number_philo = all->number_philo;
		j++;
	}
	j = 0;
	while (j < all->number_philo)
	{
		pthread_mutex_init(&all->forks[j], NULL);
		j++;
	}
	j = 0;
	while(j < all->number_philo)
	{
		pthread_create(&philo[j], NULL, phil_test, &ph_s[j]);
		usleep(100);
		j++;
	}
	j = 0;
	while(j < all->number_philo)
	{
		pthread_join(philo[j], NULL);
		//usleep(100);
		j++;
	}
}