/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssamadi <ssamadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 15:29:53 by ssamadi           #+#    #+#             */
/*   Updated: 2021/07/01 11:46:47 by ssamadi          ###   ########.fr       */
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
	long long time_to_eat;
	long long time_to_sleep;
	long long time_to_die;
	long long number_philo;
	long long	number_philo_must_eat;
	long long last_eat;
	pthread_mutex_t *forks;
	pthread_mutex_t write_lock;
}   t_all;

typedef struct s_philo
{
	int id;
    int number_philo;
	long long last_eat;
	int eat_time;
}	t_philo_data;


#endif