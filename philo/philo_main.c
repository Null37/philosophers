/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssamadi <ssamadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 18:54:13 by ssamadi           #+#    #+#             */
/*   Updated: 2021/07/04 15:07:05 by ssamadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_all	*all_t(void)
{
	static t_all	all;

	return (&all);
}

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
		print_to("is sleeping", p->id);
		pthread_mutex_unlock(&all->forks[(p->id) % all->number_philo]);
		pthread_mutex_unlock(&all->forks[p->id - 1]);
		my_sleep(all->time_to_sleep);
		print_to("is thinking", p->id);
	}
	return (NULL);
}

t_philo_data	*aloc_stuct(t_philo_data *philo)
{
	t_all	*all;

	all = all_t();
	philo = malloc(all->number_philo * (sizeof(t_philo_data)));
	return (philo);
}

int	wait_philos(t_philo_data *ph_s)
{
	t_all	*all;
	int		var;
	int		j;

	all = all_t();
	while (1)
	{
		j = -1;
		var = 0;
		while (++j < all->number_philo)
		{
			if (get_in_mic() - ph_s[j].last_eat >= all->time_to_die * 1000)
			{
				print_exit("is dead", ph_s[j].id);
				return (1);
			}
			if (all->number_philo_must_eat > 0 && ph_s[j].eat_time
				>= all->number_philo_must_eat)
				var++;
		}
		if (var == all->number_philo)
			return (1);
		usleep(100);
	}
	return (0);
}

pthread_t	*alloc_philos(pthread_t *philo)
{
	t_all	*all;

	all = all_t();
	philo = malloc(all->number_philo * (sizeof(pthread_t)));
	return (philo);
}

void	set_arg(char *av[])
{
	t_all	*all;

	all = all_t();
	all->number_philo = ft_my_atoi(av[1]);
	all->time_to_die = ft_my_atoi(av[2]);
	all->time_to_eat = ft_my_atoi(av[3]);
	all->time_to_sleep = ft_my_atoi(av[4]);
	if (av[5])
		all->number_philo_must_eat = ft_my_atoi(av[5]);
	else
		all->number_philo_must_eat = -1;
	all->forks = malloc(sizeof(pthread_mutex_t) * all->number_philo);
}

void	creat_philos(t_philo_data *ph_s, pthread_t *philo)
{
	int		j;
	t_all	*all;

	all = all_t();
	j = 0;
	while (j < all->number_philo)
	{
		pthread_mutex_init(&all->forks[j], NULL);
		j++;
	}
	j = 0;
	while (j < all->number_philo)
	{
		ph_s[j].eat_time = 0;
		ph_s[j].last_eat = get_in_mic();
		pthread_create(&philo[j], NULL, philos, &ph_s[j]);
		usleep(100);
		j++;
	}
}

void	thread_join(pthread_t *philo)
{
	int				j;
	t_all			*all;

	all = all_t();
	j = 0;
	while (j < all->number_philo)
	{
		pthread_join(philo[j], NULL);
		j++;
	}
}

int	main(int ac, char *av[])
{
	t_all			*all;
	t_philo_data	*ph_s;
	pthread_t		*philo;
	int				j;

	if (ac >= 4)
	{
		all = all_t();
		philo = NULL;
		ph_s = NULL;
		set_arg(av);
		philo = alloc_philos(philo);
		ph_s = aloc_stuct(ph_s);
		pthread_mutex_init(&all->write_lock, NULL);
		j = -1;
		while (++j < all->number_philo)
			ph_s[j].id = j + 1;
		creat_philos(ph_s, philo);
		if (wait_philos(ph_s))
			return (1);
		thread_join(philo);
	}
	return (0);
}
