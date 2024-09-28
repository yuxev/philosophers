/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasselma <aasselma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 17:51:15 by aasselma          #+#    #+#             */
/*   Updated: 2023/07/04 16:18:38 by aasselma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atoi(char *s)
{
	long	r;
	long	sign;
	long	i;

	r = 0;
	sign = 1;
	i = 0;
	while ((s[i] >= 9 && s[i] <= 13) || s[i] == 32)
		i++;
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
			sign = -1;
		i++;
	}
	while (s[i] >= '0' && s[i] <= '9')
		r = r * 10 + s[i++] - '0';
	if ((r * sign) <= 0)
		return (-1);
	return (r * sign);
}

int	check_errors(char **argv, int argc)
{
	int	i;
	int	w;

	i = 0;
	w = 1;
	while (w != argc)
	{
		if (ft_atoi(argv[w]) == -1)
			return (-1);
		while (argv[w][i])
		{
			if (!(argv[w][i] >= '0' && argv[w][i] <= '9') && argv[w][0] != '+')
				return (-1);
			i++;
		}
		i = 0;
		w++;
	}
	return (0);
}

void	my_usleep(long sleep_time, t_philo *philo)
{
	long	now;

	now = t_now();
	while (1)
	{
		if ((t_now() - now) >= sleep_time)
			break ;
		pthread_mutex_lock(&philo->data->lock_death);
		if (philo->data->dead == 1)
		{
			pthread_mutex_unlock(&philo->data->lock_death);
			break ;
		}
		pthread_mutex_unlock(&philo->data->lock_death);
		usleep(50);
	}
}

void	wait_threads(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->lock_wait);
	philo->data->d_wait++;
	pthread_mutex_unlock(&philo->data->lock_wait);
	while (1)
	{
		pthread_mutex_lock(&philo->data->lock_death);
		if (philo->data->d_wait == philo->data->ph_num
			|| philo->data->dead == 1)
		{
			pthread_mutex_unlock(&philo->data->lock_death);
			break ;
		}
		pthread_mutex_unlock(&philo->data->lock_death);
		pthread_mutex_lock(&philo->data->lock_last);
		philo->last_eat = t_now();
		pthread_mutex_unlock(&philo->data->lock_last);
		usleep(100);
	}
}
