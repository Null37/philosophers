/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssamadi <ssamadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 15:29:53 by ssamadi           #+#    #+#             */
/*   Updated: 2021/07/04 17:27:28 by ssamadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_all
{
	long long			time_to_eat;
	long long			time_to_sleep;
	long long			time_to_die;
	long long			number_philo;
	long long			number_philo_must_eat;
	long long			last_eat;
	pthread_mutex_t		*forks;
	pthread_mutex_t		write_lock;
}					t_all;

typedef struct s_philo
{
	int					id;
	int					number_philo;
	long long			last_eat;
	int					eat_time;
}			t_philo_data;

long long		ft_my_atoi(const char *str);
t_all			*all_t(void);
void			print_to(char *str, int n);
void			print_exit(char *str, int n);
long long		get_in_mic(void);
void			my_sleep(long long time);
void			*philos(void *arg);
t_all			*all_t(void);
t_philo_data	*aloc_stuct(t_philo_data *philo);
int				wait_philos(t_philo_data *ph_s);
void			creat_philos(t_philo_data *ph_s, pthread_t *philo);
int				check_erros(char *av[], int ac);
int				t_isdigit(char number);

#endif