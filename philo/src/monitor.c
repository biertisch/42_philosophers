/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beatde-a <beatde-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 21:20:16 by beatde-a          #+#    #+#             */
/*   Updated: 2025/07/24 21:20:16 by beatde-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	monitor(t_sim *sim)
{
	int	i;
	int	satiety;

	satiety = 1;
	i = 0;
	while (i < sim->total)
	{
		pthread_mutex_lock(&sim->philos[i].meal_lock);
		if (get_time_ms() - sim->philos[i].last_meal > sim->time_to_die)
		{
			print_status(&sim->philos[i], "died");
			sim->sim_over = 1;
			pthread_mutex_unlock(&sim->philos[i].meal_lock);
			return;
		}
		if (sim->required_meals != -1
			&& sim->philos[i].meals_eaten < sim->required_meals)
			satiety = 0;
		pthread_mutex_unlock(&sim->philos[i].meal_lock);
		i++;
	}
	if (sim->required_meals != -1 && satiety)
	{
		sim->sim_over = 1;
		printf("%ld The philosophers are all satiated\n",
			get_time_ms() - sim->start_time);
	}
}
