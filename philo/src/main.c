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
	t_sim	sim;

	memset(&sim, 0, sizeof(sim));
	if (!validate_input(argc, argv))
		return (error_exit(&sim, "invalid input", 1));
	if (!init_config(&sim, argc, argv))
		return (error_exit(&sim, "failure to initialize configuration", 2));
	if (!init_forks(&sim))
		return (error_exit(&sim, "failure to initialize forks", 3));
	if (!init_philos(&sim))
		return (error_exit(&sim, "failure to initialize philosophers", 4));
	sim.sim_over = 0;
	while (!sim.sim_over)
	{
		monitor(&sim);
		sleep_ms(1);
	}
	cleanup(&sim);
	return (0);
}
