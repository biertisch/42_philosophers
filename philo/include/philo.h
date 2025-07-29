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

struct	s_sim;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	int				meals_eaten;
	long			last_meal;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct s_sim	*sim;
}					t_philo;

typedef struct s_sim
{
	int				total;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				required_meals;
	pthread_mutex_t	print_lock;
	long			start_time;
	int				sim_over;
	pthread_mutex_t	sim_lock;
	pthread_mutex_t	*forks;
	t_philo			*philos;
}					t_sim;

int		validate_input(int argc, char **argv);
long	ft_atol(const char *s);
int		init_config(t_sim *sim, int argc, char **argv);
int		init_forks(t_sim *sim);
int		init_philos(t_sim *sim);
void	*routine(void *arg);
void	monitor(t_sim *sim);
void	print_status(t_philo *philo, char *msg);
long	get_time_ms(void);
void	sleep_ms(t_sim *sim, long msec);
int		error_exit(t_sim *sim, char *error_msg, int error_code);
int		stop_sim(t_sim *sim);
void	cleanup(t_sim *sim);

#endif