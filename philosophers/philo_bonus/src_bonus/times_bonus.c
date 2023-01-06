/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   times_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyardimc <fyardimc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 15:22:38 by fyardimc          #+#    #+#             */
/*   Updated: 2022/10/17 16:14:44 by fyardimc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

long long	timestamp(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

long long	time_diff(long long past, long long pres)
{
	return (pres - past);
}

void	wsleep(long long time, t_arg *rules)
{
	long long	i;

	i = timestamp();
	while (!(rules->died))
	{
		if (time_diff(i, timestamp()) >= time)
			break ;
		usleep(50);
	}
}
