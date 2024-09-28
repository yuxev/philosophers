/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasselma <aasselma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 23:43:56 by aasselma          #+#    #+#             */
/*   Updated: 2023/07/04 19:48:14 by aasselma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>

typedef struct data
{
	int			dead;
	int			ph_num;
	int			argc;
	long		die_time;
	long		eat_time;
	long		sleep_time;
	long		tm;
	sem_t		*lock_death;
	sem_t		*lock_last;
	sem_t		*counter;
}				t_data;

typedef struct philo
{
	int			id;
	int			n_o_t;
	long		last_eat;
	sem_t		*forks;
	t_data		*data;
	pid_t		pid;
}				t_philo;

void			check_errors(char **argv, int argc);
void			fill_data(t_data *data, char **argv);
void			fill_data_of_threads(t_philo *th, t_data *dt, int n_o_e);
int				ft_printf(char *str, t_philo *philo);
int				ft_routin(t_philo *philo);
int				ft_sleep(t_philo *philo);
void			*check_death(void *thread);
long			ft_atoi(char *s);
long			t_now(void);

#endif