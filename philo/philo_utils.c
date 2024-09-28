/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasselma <aasselma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 06:45:39 by aasselma          #+#    #+#             */
/*   Updated: 2023/06/25 18:23:25 by aasselma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include    "philo.h"

long	t_now(void)
{
	struct timeval	tv;
	long			befor;

	gettimeofday(&tv, NULL);
	befor = ((tv.tv_sec) * 1000 + (tv.tv_usec) / 1000);
	return (befor);
}

int	ft_printf(char *str, t_philo *philo)
{
	long	tm;

	tm = philo->data->tm;
	pthread_mutex_lock(&philo->data->lock_death);
	if (philo->data->dead == 0)
	{
		printf("%ld %d %s\n", t_now() - tm, philo->id + 1, str);
		pthread_mutex_unlock(&philo->data->lock_death);
	}
	else
	{
		pthread_mutex_unlock(&philo->data->lock_death);
		return (1);
	}
	return (0);
}

void	fill_data(t_data *data, char **av, int ac)
{
	pthread_mutex_init(&data->counter, NULL);
	pthread_mutex_init(&data->lock_death, NULL);
	pthread_mutex_init(&data->lock_done, NULL);
	pthread_mutex_init(&data->lock_last, NULL);
	pthread_mutex_init(&data->lock_wait, NULL);
	data->ph_num = ft_atoi(av[1]);
	data->die_time = ft_atoi(av[2]);
	data->eat_time = ft_atoi(av[3]);
	data->sleep_time = ft_atoi(av[4]);
	data->dead = 0;
	data->done = 0;
	data->argc = ac;
	data->d_wait = 0;
	data->tm = t_now();
}

void	fill_data_of_threads(t_philo *th, t_data *dt, int _not)
{
	int				i;
	pthread_mutex_t	*mutex;

	i = 0;
	mutex = malloc(dt->ph_num * sizeof(pthread_mutex_t));
	while (i != dt->ph_num)
		pthread_mutex_init(&(mutex[i++]), NULL);
	i = 0;
	while (i < dt->ph_num)
	{
		th[i].n_o_t = _not;
		th[i].id = i;
		th[i].forks = mutex;
		th[i].data = dt;
		th[i].last_eat = 0;
		i++;
	}
}

void	free_and_destroy(t_philo *philo, t_data *data)
{
	pthread_mutex_destroy(&data->counter);
	pthread_mutex_destroy(&data->lock_death);
	pthread_mutex_destroy(&data->lock_done);
	pthread_mutex_destroy(&data->lock_last);
	free(philo->forks);
	free(data);
	free(philo);
}
