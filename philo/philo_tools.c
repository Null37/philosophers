/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssamadi <ssamadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/04 15:21:18 by ssamadi           #+#    #+#             */
/*   Updated: 2021/07/04 17:18:40 by ssamadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_to(char *str, int n)
{
	t_all			*all;
	struct timeval	time;
	long long		t;

	all = all_t();
	pthread_mutex_lock(&all->write_lock);
	gettimeofday(&time, NULL);
	t = (time.tv_usec / 1000) + (time.tv_sec * 1000);
	printf("%lld %d %s\n", t, n, str);
	pthread_mutex_unlock(&all->write_lock);
}

void	print_exit(char *str, int n)
{
	t_all			*all;
	struct timeval	time;
	long long		t;

	all = all_t();
	pthread_mutex_lock(&all->write_lock);
	gettimeofday(&time, NULL);
	t = (time.tv_usec / 1000) + (time.tv_sec * 1000);
	printf("%lld %d %s\n", t, n, str);
	return ;
	pthread_mutex_unlock(&all->write_lock);
}

long long	get_in_mic(void)
{
	struct timeval	time;
	long long		h;

	gettimeofday(&time, NULL);
	h = time.tv_usec + (time.tv_sec * 1000000);
	return (h);
}

void	my_sleep(long long time)
{
	long long	microb;
	long long	r;

	microb = get_in_mic();
	r = time - 60;
	usleep(r * 1000);
	while ((get_in_mic() - microb) < (time * 1000))
	{	
	}
}

void	*philos(void *arg)
{
	t_all			*all;
	t_philo_data	*p;

	all = all_t();
	p = (t_philo_data *)arg;
	while (1)
	{
		pthread_mutex_lock(&all->forks[p->id - 1]);
		print_to("has taken a fork", p->id);
		pthread_mutex_lock(&all->forks[(p->id) % all->number_philo]);
		print_to("has taken a fork", p->id);
		p->last_eat = get_in_mic();
		p->eat_time++;
		print_to("is eating", p->id);
		my_sleep(all->time_to_eat);
		pthread_mutex_unlock(&all->forks[(p->id) % all->number_philo]);
		pthread_mutex_unlock(&all->forks[p->id - 1]);
		print_to("is sleeping", p->id);
		my_sleep(all->time_to_sleep);
		print_to("is thinking", p->id);
	}
	return (NULL);
}
