/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beatde-a <beatde-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 17:23:25 by beatde-a          #+#    #+#             */
/*   Updated: 2025/07/24 17:23:25 by beatde-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long	ft_atol(const char *s)
{
	long	res;
	int		sign;

	if (!s)
		return (0);
	res = 0;
	sign = 1;
	while (*s == ' ' || (*s >= 9 && *s <= 13))
		s++;
	if (*s == '+' || *s == '-')
	{
		if (*s == '-')
			sign = -1;
		s++;
	}
	while (*s >= '0' && *s <= '9')
	{
		res = res * 10 + *s - '0';
		s++;
	}
	return (res * sign);
}

static int	is_numeric(const char *s)
{
	if (!*s)
		return (0);
	while (*s)
	{
		if (*s < '0' || *s > '9')
			return (0);
		s++;
	}
	return (1);
}

int	validate_input(int argc, char **argv)
{
	int		i;
	long	tmp;

	if (argc < 5 || argc > 6)
		return (0);
	i = 1;
	while (i < argc)
	{
		if (!is_numeric(argv[i]))
			return (0);
		tmp = ft_atol(argv[i]);
		if (i == 1 && (tmp < 1 || tmp > 200))
			return (0);
		if ((i >= 2 && i <= 4) && (tmp < 60 || tmp > INT_MAX))
			return (0);
		if (i == 5 && (tmp < 1 || tmp >= INT_MAX))
			return (0);
		i++;
	}
	return (1);
}
