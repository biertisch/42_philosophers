/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beatde-a <beatde-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 16:48:18 by beatde-a          #+#    #+#             */
/*   Updated: 2025/07/24 16:48:18 by beatde-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	init_philos(t_sim *sim)
{
	int	i;

	sim->philos = malloc(sizeof(t_philo) * sim->total);
	if (!sim->philos)
		return (0);
	i = 0;
	while (i < sim->total)
	{
		sim->philos[i].id = i + 1;
		sim->philos[i].meals_eaten = 0;
		sim->philos[i].last_meal = sim->start_time;
		sim->philos[i].left_fork = &sim->forks[i];
		sim->philos[i].right_fork = &sim->forks[(i + 1) % sim->total];
		sim->philos[i].sim = sim;
		if (pthread_mutex_init(&sim->philos[i].meal_lock, NULL) != 0)
			return (0);
		if (pthread_create(&sim->philos[i].thread, NULL, &routine,
				&sim->philos[i]) != 0)
			return (0);
		i++;
	}
	return (1);
}

int	init_forks(t_sim *sim)
{
	int	i;

	sim->forks = malloc(sizeof(pthread_mutex_t) * sim->total);
	if (!sim->forks)
		return (0);
	i = 0;
	while (i < sim->total)
	{
		if (pthread_mutex_init(&sim->forks[i], NULL) != 0)
			return (0);
		i++;
	}
	return (1);
}

int	init_config(t_sim *sim, int argc, char **argv)
{
	sim->total = ft_atol(argv[1]);
	sim->time_to_die = ft_atol(argv[2]);
	sim->time_to_eat = ft_atol(argv[3]);
	sim->time_to_sleep = ft_atol(argv[4]);
	sim->required_meals = -1;
	if (argc == 6)
		sim->required_meals = ft_atol(argv[5]);
	if (pthread_mutex_init(&sim->print_lock, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&sim->sim_lock, NULL) != 0)
		return (0);
	sim->start_time = get_time_ms();
	if (sim->start_time < 0)
		return (0);
	pthread_mutex_lock(&sim->sim_lock);
	sim->sim_over = 1;
	pthread_mutex_unlock(&sim->sim_lock);
	return (1);
}
