/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beatde-a <beatde-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 16:24:59 by beatde-a          #+#    #+#             */
/*   Updated: 2025/07/24 16:24:59 by beatde-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/* void	error_exit(t_monitor *monitor, char *error_msg)
{
	if (msg)
		printf("Error: %s\n", msg);
	//clean_up
} */

int	main(int argc, char **argv)
{
	t_monitor	monitor;

	if (!validate_input(argc, argv))
	{
		//error_exit(&monitor, "invalid input");
		return (1);
	}
	
}


//main.c
//error

//parser.c
//validate input

//init.c
//init config
//init philosophers & threads
//init forks

//routine.c
//take forks
//eat
//sleep
//think
//repeat

//time.c
//get_time_ms (using gettimeofday)
//sleep_ms (using usleep)

//monitor.c
//check death (current_time - last_meal)
//check satiety (if applicable)
//manage priorities?
//print message

//cleanup.c
//pthread_join all thread
//destroy all mutexes
//free all memory

//utils.c
//ft_strlen
//ft_atol
