/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasselma <aasselma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 17:40:13 by aasselma          #+#    #+#             */
/*   Updated: 2023/06/25 18:26:39 by aasselma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	start_routin(t_philo *philo)
{
	int	checker;

	if (philo->data->dead == 0)
	{
		checker = ft_routin(philo);
		checker = ft_sleep(philo);
	}
	else
		return (1);
	return (checker);
}

void	edit_data(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->lock_done);
	philo->data->done++;
	pthread_mutex_unlock(&philo->data->lock_done);
}

void	*ph_managment(void	*thread)
{
	t_philo		*philo;

	philo = thread;
	while (1)
	{
		pthread_mutex_lock(&philo->data->counter);
		if (philo->n_o_t != 0)
		{
			pthread_mutex_unlock(&philo->data->counter);
			if (start_routin(philo))
				break ;
		}
		else
		{
			pthread_mutex_unlock(&philo->data->counter);
			edit_data(philo);
			break ;
		}
	}
	wait_threads(philo);
	return (NULL);
}

void	create_threads(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos->data->ph_num)
	{
		pthread_create(&philos[i].philo, NULL, ph_managment, &philos[i]);
		usleep(50);
		i += 2;
	}
	i = 1;
	while (i < philos->data->ph_num)
	{
		pthread_create(&philos[i].philo, NULL, ph_managment, &philos[i]);
		usleep(50);
		i += 2;
	}
	i = 0;
	check_death(philos);
	while (i < philos[0].data->ph_num)
		pthread_join(philos[i++].philo, NULL);
}

int	main(int ac, char **av)
{
	int		i;
	t_philo	*philos;
	t_data	*data;

	if (ac == 5 || ac == 6)
	{
		i = 0;
		if (check_errors(av, ac) == -1)
			printf("Error: unacceptable input\n");
		else
		{
			data = malloc(sizeof(t_data));
			fill_data(data, av, ac);
			philos = malloc(data->ph_num * sizeof(t_philo));
			if (ac == 6)
				ac = ft_atoi(av[5]);
			else
				ac = 1;
			fill_data_of_threads(philos, data, ac);
			create_threads(philos);
			free_and_destroy(philos, data);
		}
	}
	return (0);
}
