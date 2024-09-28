/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasselma <aasselma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 23:43:56 by aasselma          #+#    #+#             */
/*   Updated: 2023/07/04 16:17:15 by aasselma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct data
{
	int				dead;
	int				done;
	int				d_wait;
	int				ph_num;
	int				argc;
	long			die_time;
	long			eat_time;
	long			sleep_time;
	long			tm;
	pthread_mutex_t	lock_death;
	pthread_mutex_t	counter;
	pthread_mutex_t	lock_done;
	pthread_mutex_t	lock_last;
	pthread_mutex_t	lock_wait;
}					t_data;

typedef struct s_philo
{
	int				id;
	int				n_o_t;
	long			last_eat;
	pthread_mutex_t	*forks;
	t_data			*data;
	pthread_t		philo;
}					t_philo;

int					check_errors(char **argv, int argc);
void				fill_data(t_data *data, char **av, int ac);
void				fill_data_of_threads(t_philo *th, t_data *dt, int _not);
int					ft_printf(char *str, t_philo *philo);
int					ft_routin(t_philo *philo);
int					ft_sleep(t_philo *philo);
void				wait_threads(t_philo *philo);
void				check_death(t_philo *thread);
long				ft_atoi(char *s);
long				t_now(void);
void				my_usleep(long sleep_time, t_philo *philo);
void				free_and_destroy(t_philo *philo, t_data *data);

#endif