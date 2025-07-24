/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beatde-a <beatde-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 15:46:07 by beatde-a          #+#    #+#             */
/*   Updated: 2025/07/24 15:46:07 by beatde-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

struct	s_monitor;

typedef struct s_philo
{
	int					id;
	int					meals_eaten;
	long				last_meal;
	pthread_t			thread;
	pthread_mutex_t		meal_lock;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		*left_fork;
	struct s_monitor	*monitor;
}						t_philo;

typedef struct s_monitor
{
	int				total;
	int				time_to_die;
	int				time_to_eat;
	int 			time_to_sleep;
	int				required_meals;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_lock;
	long			start_time;
	int				sim_over;
	pthread_mutex_t	sim_lock;
}					t_monitor;

int	validate_input(int argc, char **argv);

#endif