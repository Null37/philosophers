/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssamadi <ssamadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/04 15:18:30 by ssamadi           #+#    #+#             */
/*   Updated: 2021/07/04 15:18:35 by ssamadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	ft_my_atoi(const char *str)
{
	long long		i;
	long long		number;
	int				sign;
	int				l_counter;

	l_counter = 0;
	sign = 1;
	i = 0;
	number = 0;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == 32))
		i++;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			sign = -1;
	while (str[i] != '\0')
	{
		if (!(str[i] >= 48 && str[i] <= 57))
			return (number * sign);
		number = number * 10 + (str[i++] - 48);
	}
	return (number * sign);
}
