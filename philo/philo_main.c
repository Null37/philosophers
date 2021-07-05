/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssamadi <ssamadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 18:54:13 by ssamadi           #+#    #+#             */
/*   Updated: 2021/07/04 17:27:13 by ssamadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

t_philo_data	*set_philos(t_philo_data *ph_s)
{
	t_all	*all;
	int		j;

	all = all_t();
	j = -1;
	while (++j < all->number_philo)
		ph_s[j].id = j + 1;
	return (ph_s);
}

int	main(int ac, char *av[])
{
	t_all			*all;
	t_philo_data	*ph_s;
	pthread_t		*philo;

	if (check_erros(av, ac) == 1)
	{
		printf("Error\n");
		return (1);
	}
	all = all_t();
	philo = NULL;
	ph_s = NULL;
	set_arg(av);
	philo = alloc_philos(philo);
	ph_s = aloc_stuct(ph_s);
	pthread_mutex_init(&all->write_lock, NULL);
	ph_s = set_philos(ph_s);
	creat_philos(ph_s, philo);
	if (wait_philos(ph_s))
	{
		free(philo);
		return (1);
	}
	thread_join(philo);
	return (0);
}
