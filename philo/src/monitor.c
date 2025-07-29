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

void	print_status(t_philo *philo, char *msg)
{
	long	timestamp;

	pthread_mutex_lock(&philo->sim->print_lock);
	if (!stop_sim(philo->sim))
	{
		timestamp = get_time_ms() - philo->sim->start_time;
		printf("%ld %d %s\n", timestamp, philo->id, msg);
	}
	pthread_mutex_unlock(&philo->sim->print_lock);
}

static void	check_satisfied(t_sim *sim)
{
	int	i;
	int	satisfied;

	i = 0;
	satisfied = 0;
	while (i < sim->total)
	{
		pthread_mutex_lock(&sim->philos[i].meal_lock);
		if (sim->philos[i].meals_eaten >= sim->required_meals)
			satisfied++;
		pthread_mutex_unlock(&sim->philos[i].meal_lock);
		i++;
	}
	if (satisfied == sim->total)
	{
		printf("%ld The philosophers are all satisfied\n",
			get_time_ms() - sim->start_time);
		pthread_mutex_lock(&sim->sim_lock);
		sim->sim_over = 1;
		pthread_mutex_unlock(&sim->sim_lock);
	}
}

static void	check_deaths(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->total)
	{
		pthread_mutex_lock(&sim->philos[i].meal_lock);
		if (get_time_ms() - sim->philos[i].last_meal > sim->time_to_die)
		{
			print_status(&sim->philos[i], "died");
			pthread_mutex_lock(&sim->sim_lock);
			sim->sim_over = 1;
			pthread_mutex_unlock(&sim->sim_lock);
			pthread_mutex_unlock(&sim->philos[i].meal_lock);
			return ;
		}
		pthread_mutex_unlock(&sim->philos[i].meal_lock);
		i++;
	}
}

void	monitor(t_sim *sim)
{
	check_deaths(sim);
	if (sim->required_meals != -1)
		check_satisfied(sim);
}
