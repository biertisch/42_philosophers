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

int	main(int argc, char **argv)
{
	t_monitor	monitor;

	memset(&monitor, 0, sizeof(monitor));
	if (!validate_input(argc, argv))
	{
		error_exit(&monitor, "invalid input");
		return (1);
	}
	if (!init_sim(&monitor, argc, argv))
	{
		error_exit(&monitor, "failure to initiate simulation");
		return (2);
	}
	while (!monitor.sim_over)
	{
		//monitor
		//sleep_ms(1);
	}
	cleanup(&monitor);
	return (0);
}

/* Plan
Add proper time handling
Basic routine: eat/sleep/think
Add monitor thread
Test, optimize */

//time.c
//get_time_ms (using gettimeofday)
//sleep_ms (using usleep)

//routine.c
//take forks
//eat
//sleep
//think
//repeat

//monitor.c
//check death (current_time - last_meal)
//check satiety (if applicable)
//manage priorities?
//print message
