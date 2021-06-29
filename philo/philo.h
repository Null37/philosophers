/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssamadi <ssamadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 15:29:53 by ssamadi           #+#    #+#             */
/*   Updated: 2021/06/29 12:50:27 by ssamadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

typedef struct s_all
{
	int time_to_eat;
	int time_to_sleep;
	int time_to_die;
	int number_philo;
	int	number_philo_must_eat;
	pthread_mutex_t *forks;
	pthread_mutex_t write_lock;
}   t_all;

typedef struct s_philo
{
	int id;
    int number_philo;
}	t_philo_data;


#endif