/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyardimc <fyardimc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 15:22:15 by fyardimc          #+#    #+#             */
/*   Updated: 2022/10/17 15:22:15 by fyardimc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	ft_atoi(const char *str)
{
	long int	n;
	int			sign;

	n = 0;
	sign = 1;
	while ((*str <= 13 && *str >= 9) || *str == 32)
		str++;
	if (*str == '-')
		return (-1);
	else if (*str == '+')
		str++;
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
			n = n * 10 + (*str++ - '0');
		else
			return (-1);
	}
	return ((int)(n * sign));
}

void	action_philo(t_arg *rules, int id, char *string)
{
	sem_wait(rules->writing);
	if (!(rules->died))
	{
		printf("%s%lli%s", RED, timestamp() - rules->first_timestamp, END);
		printf("%s %i %s", YELLOW, id + 1, END);
		printf("%s", string);
	}
	sem_post(rules->writing);
	return ;
}

int	error_message(char *arg)
{
	printf("%s%s%s", RED, arg, END);
	return (-1);
}
