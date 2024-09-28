/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasselma <aasselma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 15:38:48 by aasselma          #+#    #+#             */
/*   Updated: 2023/07/04 16:53:00 by aasselma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_sleep(t_philo *philo)
{
	int	checker;

	checker = ft_printf("is sleeping", philo);
	my_usleep(philo->data->sleep_time, philo);
	return (checker);
}

int	kill_philo(t_philo *philo)
{
	my_usleep(philo->data->die_time, philo);
	ft_printf("died", philo);
	pthread_mutex_lock(&philo->data->lock_death);
	philo->data->dead = 1;
	pthread_mutex_unlock(&philo->data->lock_death);
	return (1);
}

int	ft_routin(t_philo *philo)
{
	int	right_fork;
	int	checker;

	right_fork = philo->id + 1;
	if (philo->id + 1 == philo->data->ph_num)
		right_fork = 0;
	checker = ft_printf("is thinking", philo);
	pthread_mutex_lock(&philo->forks[philo->id]);
	checker = ft_printf("has taken a fork", philo);
	if (philo->data->ph_num == 1)
		return (kill_philo(philo));
	pthread_mutex_lock(&philo->forks[right_fork]);
	checker = ft_printf("has taken a fork", philo);
	checker = ft_printf("is eating", philo);
	pthread_mutex_lock(&philo->data->lock_last);
	philo->last_eat = t_now();
	pthread_mutex_unlock(&philo->data->lock_last);
	my_usleep(philo->data->eat_time, philo);
	pthread_mutex_lock(&philo->data->counter);
	if (philo->data->argc == 6)
		philo->n_o_t--;
	pthread_mutex_unlock(&philo->data->counter);
	pthread_mutex_unlock(&philo->forks[philo->id]);
	pthread_mutex_unlock(&philo->forks[right_fork]);
	return (checker);
}

int	checking(t_philo *thread)
{
	pthread_mutex_lock(&thread->data->lock_done);
	if (thread->data->done == thread->data->ph_num)
		return (1);
	pthread_mutex_unlock(&thread->data->lock_done);
	pthread_mutex_lock(&thread->data->lock_last);
	pthread_mutex_lock(&thread->data->counter);
	if ((thread->last_eat != 0)
		&& (t_now() - thread->last_eat) >= thread->data->die_time)
	{
		pthread_mutex_unlock(&thread->data->counter);
		pthread_mutex_unlock(&thread->data->lock_last);
		pthread_mutex_lock(&thread->data->lock_death);
		printf("%ld %d died\n", t_now() - thread->data->tm, thread->id + 1);
		thread->data->dead = 1;
		pthread_mutex_unlock(&thread->data->lock_death);
		return (1);
	}
	pthread_mutex_unlock(&thread->data->counter);
	pthread_mutex_unlock(&thread->data->lock_last);
	return (0);
}

void	check_death(t_philo *thread)
{
	int	i;

	i = 0;
	while (1)
	{
		pthread_mutex_lock(&thread[i].data->lock_death);
		if (thread->data->dead == 0)
		{
			pthread_mutex_unlock(&thread[i].data->lock_death);
			if (checking(&thread[i]))
				break ;
		}
		else
		{
			pthread_mutex_unlock(&thread[i].data->lock_death);
			break ;
		}
		if ((i + 1) == thread[0].data->ph_num)
			i = -1;
		i++;
	}
}
