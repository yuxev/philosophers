/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasselma <aasselma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 16:19:15 by aasselma          #+#    #+#             */
/*   Updated: 2023/07/04 19:35:52 by aasselma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	start_routin(t_philo *philo)
{
	ft_printf("is thinking\n", philo);
	if (ft_routin(philo) == 1)
		return (1);
	if (ft_sleep(philo) == 1)
		return (1);
	return (0);
}

void	*ph_managment(t_philo *philo)
{
	pthread_t	checker;

	pthread_create(&checker, NULL, check_death, philo);
	while (1)
	{
		sem_wait(philo->data->counter);
		if ((philo->n_o_t != 0))
		{
			sem_post(philo->data->counter);
			start_routin(philo);
		}
		else
		{
			sem_post(philo->data->counter);
			exit(0);
		}
	}
	return (NULL);
}

void	ft_contune(t_philo *thread, t_data *data, int num_oft_eat)
{
	int	i;
	int	status;
	int	*arr;

	i = 0;
	arr = malloc(data->ph_num * sizeof(int));
	fill_data_of_threads(thread, data, num_oft_eat);
	while (i < data->ph_num)
	{
		thread[i].data = data;
		thread[i].pid = fork();
		if (thread[i].pid == 0)
			ph_managment(&thread[i]);
		else
			arr[i] = thread[i].pid;
		usleep(10);
		i++;
	}
	waitpid(-1, &status, 0);
	i = 0;
	while (i != data->ph_num)
		kill(arr[i++], SIGKILL);
	free(arr);
}

void	free_and_unlink(t_philo *threads, t_data *data)
{
	sem_close(data->counter);
	sem_close(data->lock_death);
	sem_close(data->lock_last);
	sem_close(threads->forks);
	sem_unlink("/forks");
	sem_unlink("/death_lock");
	sem_unlink("/last_eat_lock");
	sem_unlink("/counter");
	free(data);
	free(threads);
}

int	main(int argc, char **argv)
{
	t_philo			*prc;
	t_data			*data;
	int				i;

	i = 0;
	if (argc == 5 || argc == 6)
	{
		check_errors(argv, argc);
		data = malloc(sizeof(t_data));
		fill_data(data, argv);
		data->argc = argc;
		prc = malloc(data->ph_num * sizeof(t_philo));
		if (argc == 6)
			i = ft_atoi(argv[5]);
		else
			i = -1;
		ft_contune(prc, data, i);
		free_and_unlink(prc, data);
	}
	return (0);
}
