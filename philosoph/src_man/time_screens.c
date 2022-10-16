/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_screens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyardimc <fyardimc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 20:35:24 by fyardimc          #+#    #+#             */
/*   Updated: 2022/10/16 00:51:36 by fyardimc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	wait_sleep(long long wait_time, t_arg *rules)
{
	long long	i;

	i = timestamp();
	while (rules->died)
	{
		if (wait_time <= time_diff(i, timestamp()))
			break ;
	}
}
void start_screen(void)
{
    printf("%s██████╗ ██╗  ██╗██╗██╗      ██████╗ ███████╗ ██████╗ ██████╗ ██╗  ██╗███████╗██████╗ ███████╗%s\n",BLUE,END);
    printf("%s██╔══██╗██║  ██║██║██║     ██╔═══██╗██╔════╝██╔═══██╗██╔══██╗██║  ██║██╔════╝██╔══██╗██╔════╝%s\n",BLUE,END);
    printf("%s██████╔╝███████║██║██║     ██║   ██║███████╗██║   ██║██████╔╝███████║█████╗  ██████╔╝███████╗%s\n",BLUE,END);
    printf("%s██╔═══╝ ██╔══██║██║██║     ██║   ██║╚════██║██║   ██║██╔═══╝ ██╔══██║██╔══╝  ██╔══██╗╚════██║%s\n",BLUE,END);
    printf("%s██║     ██║  ██║██║███████╗╚██████╔╝███████║╚██████╔╝██║     ██║  ██║███████╗██║  ██║███████║%s\n",BLUE,END);
    printf("%s╚═╝     ╚═╝  ╚═╝╚═╝╚══════╝ ╚═════╝ ╚══════╝ ╚═════╝ ╚═╝     ╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝╚══════╝%s\n",BLUE,END);
}

void die_screen()
{
printf("%s██████╗ ██╗███████╗██████╗%s\n",RED,END);
printf("%s██╔══██╗██║██╔════╝██╔══██╗%s\n",RED,END);
printf("%s██║  ██║██║█████╗  ██║  ██║%s\n",RED,END);
printf("%s██║  ██║██║██╔══╝  ██║  ██║%s\n",RED,END);
printf("%s██████╔╝██║███████╗██████╔╝%s\n",RED,END);
printf("%s╚═════╝ ╚═╝╚══════╝╚═════╝%s\n",RED,END);
}