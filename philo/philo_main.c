/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssamadi <ssamadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 18:54:13 by ssamadi           #+#    #+#             */
/*   Updated: 2021/07/03 18:30:01 by ssamadi          ###   ########.fr       */
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

void	 print_to(char *str, int n)
{
	t_all *all;

	struct timeval time;
	long long t;
	all = all_t();
	pthread_mutex_lock(&all->write_lock);
	gettimeofday(&time, NULL);
	t = (time.tv_usec / 1000) + (time.tv_sec * 1000);
	printf("%lld  %d %s\n", t, n, str);
	pthread_mutex_unlock(&all->write_lock);
}
long long get_in_mic()
{
	struct timeval time;
	gettimeofday(&time, NULL);
	
	long long h = time.tv_usec  + (time.tv_sec * 1000000);
	return (h);	
}

void	my_sleep(long long time)
{
	long long	microb;

	microb = get_in_mic();
	usleep((time * 1000) - 1500);
	while ((get_in_mic() - microb) < (time * 1000));
}

void *philos(void *arg)
{
	t_all *all;

	all = all_t();
	struct timeval time;
	t_philo_data  *p = (t_philo_data*)arg;
	while(1)
	{
		pthread_mutex_lock(&all->forks[p->id - 1]);
		print_to("has taken a fork 1", p->id);
		pthread_mutex_lock(&all->forks[(p->id) % all->number_philo]);
		print_to("has taken a fork 2", p->id);
		p->last_eat = get_in_mic();
		print_to("is etaing", p->id);
		p->eat_time++;
		my_sleep(all->time_to_eat);
		pthread_mutex_unlock(&all->forks[(p->id) % all->number_philo]);
		pthread_mutex_unlock(&all->forks[p->id - 1]);
		print_to("is sleeping", p->id);
		my_sleep(all->time_to_sleep);
		print_to("is thinking", p->id);
	}
	return NULL;
}

t_philo_data *aloc_stuct(t_philo_data *philo)
{
	t_all *all;

	all = all_t();
	philo = malloc(all->number_philo * (sizeof(t_philo_data *)));
	return (philo);
}

int wait_(t_philo_data *ph_s)
{
	t_all *all;
	
	all = all_t();
	int var;
	while (1)
	{
		int j = 0;
		var = 0;
		while (j < all->number_philo)
		{
			if (get_in_mic() - ph_s[j].last_eat > all->time_to_die * 1000)
			{
				print_to("is dead", ph_s[j].id);
				return (1);
			}
			if (all->number_philo_must_eat > 0 && ph_s[j].eat_time >= all->number_philo_must_eat)
				var++;
			j++;
		}
		if (var == all->number_philo)
		 	return (1);
		usleep(100);
	}
	return (0);
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
	if (av[5])
		all->number_philo_must_eat = atoi(av[5]);
	else
		all->number_philo_must_eat = -1;
	all->forks = malloc(sizeof(pthread_mutex_t) * i);
	pthread_mutex_init(&all->write_lock, NULL);
	int j;
	j = 0;
	while (j < all->number_philo)
	{
		ph_s[j].id = j + 1;
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
		ph_s[j].eat_time = 0;
		ph_s[j].last_eat = get_in_mic();
		pthread_create(&philo[j], NULL, philos, &ph_s[j]);
		usleep(100);
		j++;
	}
	if (wait_(ph_s))
		return (1);
	j = 0;
	while(j < all->number_philo)
	{
		pthread_join(philo[j], NULL);
		//usleep(100);
		j++;
	}
	return (0);
}