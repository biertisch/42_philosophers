/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beatde-a <beatde-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 20:17:08 by beatde-a          #+#    #+#             */
/*   Updated: 2025/07/24 20:17:08 by beatde-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	ft_strlen(const char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	error_exit(t_monitor *monitor, char *error_msg)
{
	if (msg)
	{
		write(2, "Error: ", 7);
		write(2, error_msg, ft_strlen(error_msg));
		write(2, "\n", 1);
	}
	else
		write(2, "Error\n", 6);
	cleanup(&monitor);
}

void	cleanup(t_monitor *monitor)
{
	int	i;

	if (!monitor)
		return ;
	i = 0;
	while (i < monitor->total)
	{
		if (monitor->philos)
		{
			pthread_join(monitor->philos[i].thread, NULL);
			pthread_mutex_destroy(&monitor->philos[i].meal_lock);
		}
		if (monitor->forks)
			pthread_mutex_destroy(&monitor->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&monitor->print_lock);
	pthread_mutex_destroy(&monitor->sim_lock);
	free(monitor->philos);
	free(monitor->forks);
}
