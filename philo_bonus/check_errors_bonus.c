/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasselma <aasselma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 10:42:25 by aasselma          #+#    #+#             */
/*   Updated: 2023/06/25 04:20:04 by aasselma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	check_errors(char **argv, int argc)
{
	int	i;
	int	w;

	i = 0;
	w = 1;
	while (w != argc)
	{
		while (argv[w][i])
		{
			if (!(argv[w][i] >= '0' && argv[w][i] <= '9'))
			{
				printf("Error: unacceptable input\n");
				exit(0);
			}
			i++;
		}
		i = 0;
		w++;
	}
}
