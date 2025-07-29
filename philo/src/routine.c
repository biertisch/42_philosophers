/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beatde-a <beatde-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 21:20:20 by beatde-a          #+#    #+#             */
/*   Updated: 2025/07/24 21:20:20 by beatde-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	think_until_hungry(t_philo *philo)
{
	long	threshold;

	print_status(philo, "is thinking");
	threshold = philo->sim->time_to_die * 0.85;
	while (!stop_sim(philo->sim))
	{
		if (get_time_ms() - philo->last_meal > threshold)
			break ;
		sleep_ms(philo->sim, 1);
	}
}

static void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal = get_time_ms();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_lock);
	print_status(philo, "is eating");
	sleep_ms(philo->sim, philo->sim->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

static int	take_forks(t_philo *philo)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	if (philo->left_fork < philo->right_fork)
	{
		first = philo->left_fork;
		second = philo->right_fork;
	}
	else
	{
		first = philo->right_fork;
		second = philo->left_fork;
	}
	pthread_mutex_lock(first);
	print_status(philo, "has taken a fork");
	if (first == second)
	{
		pthread_mutex_unlock(first);
		return (0);
	}
	pthread_mutex_lock(second);
	print_status(philo, "has taken a fork");
	return (1);
}

static void	wait_to_be_served(t_philo *philo)
{
	if (philo->id % 2 == 0)
		sleep_ms(philo->sim, philo->sim->time_to_eat);
	else
		sleep_ms(philo->sim, philo->sim->time_to_eat / 2);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_to_be_served(philo);
	while (!stop_sim(philo->sim))
	{
		if (!take_forks(philo))
			break ;
		eat(philo);
		print_status(philo, "is sleeping");
		sleep_ms(philo->sim, philo->sim->time_to_sleep);
		think_until_hungry(philo);
	}
	return (NULL);
}
