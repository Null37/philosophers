/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssamadi <ssamadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/04 15:21:29 by ssamadi           #+#    #+#             */
/*   Updated: 2021/07/04 17:38:20 by ssamadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_all	*all_t(void)
{
	static t_all	all;

	return (&all);
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
			if ((get_in_mic() - ph_s[j].last_eat) >= (all->time_to_die * 1000))
			{
				print_exit("died", ph_s[j].id);
				return (1);
			}
			if (all->number_philo_must_eat > 0 && ph_s[j].eat_time
				>= all->number_philo_must_eat)
				var++;
		}
		if (var == all->number_philo)
			return (1);
		usleep(15);
	}
	return (0);
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
