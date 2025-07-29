/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beatde-a <beatde-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 20:17:08 by beatde-a          #+#    #+#             */
/*   Updated: 2025/07/24 20:17:08 by beatde-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	error_exit(t_sim *sim, char *error_msg, int error_code)
{
	int	len;

	len = 0;
	while (error_msg[len])
		len++;
	write(2, "Error: ", 7);
	write(2, error_msg, len);
	write(2, "\n", 1);
	cleanup(sim);
	return (error_code);
}

int	stop_sim(t_sim *sim)
{
	int	over;

	pthread_mutex_lock(&sim->sim_lock);
	over = sim->sim_over;
	pthread_mutex_unlock(&sim->sim_lock);
	return (over);
}

void	cleanup(t_sim *sim)
{
	int	i;

	if (!sim)
		return ;
	i = 0;
	while (i < sim->total)
	{
		if (sim->philos)
		{
			pthread_join(sim->philos[i].thread, NULL);
			pthread_mutex_destroy(&sim->philos[i].meal_lock);
		}
		if (sim->forks)
			pthread_mutex_destroy(&sim->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&sim->print_lock);
	pthread_mutex_destroy(&sim->sim_lock);
	free(sim->philos);
	free(sim->forks);
}
