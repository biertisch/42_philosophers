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

static int	init_philos(t_monitor *monitor)
{
	int	i;

	monitor->philos = malloc(sizeof(t_philo) * monitor->total);
	if (!monitor->philos)
		return (0);
	i = 0;
	while (i < monitor->total)
	{
		monitor->philos[i].id = i + 1;
		monitor->philos[i].meals_eaten = 0;
		monitor->philos[i].last_meal = 0;
		monitor->philos[i].left_fork = &monitor->forks[i];
		monitor->philos[i].right_fork
			= &monitor->forks[(i + 1) % monitor->total];
		monitor->philos[i].monitor = monitor;
		if (pthread_mutex_init(&monitor->philos[i].meal_lock, NULL) != 0)
			return (0);
		if (pthread_create(&monitor->philos[i].thread), NULL, &routine,
			&monitor->philos[i] != 0)
			return (0);
		i++;
	}
	return (1);
}

static int	init_forks(t_monitor *monitor)
{
	int	i;

	monitor->forks = malloc(sizeof(pthread_mutex_t) * monitor->total);
	if (!monitor->forks)
		return (0);
	i = 0;
	while (i < monitor->total)
	{
		if (pthread_mutex_init(&monitor->forks[i], NULL) != 0)
			return (0);
		i++;
	}
	return (1);
}

static int	init_config(t_monitor *monitor, int argc, char **argv)
{
	monitor->total = ft_atol(argv[1]);
	monitor->time_to_die = ft_atol(argv[2]);
	monitor->time_to_eat = ft_atol(argv[3]);
	monitor->time_to_sleep = ft_atol(argv[4]);
	monitor->required_meals = -1;
	if (argc == 6)
		monitor->required_meals = ft_atol(argv[5]);
	if (pthread_mutex_init(&monitor->print_lock, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&monitor->sim_lock, NULL) != 0)
		return (0);
	monitor->start_time = 0;
	monitor->sim_over = 1;
	return (1);
}

int	init_sim(t_monitor *monitor, int argc, char **argv)
{
	if (!init_config(monitor, argc, argv))
		return (0);
	if (!init_forks(monitor))
		return (0);
	if (!init_philos(monitor))
		return (0);
	monitor->start_time = get_time_ms();
	monitor->sim_over = 0;
	return (1);
}
