/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_init_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyardimc <fyardimc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 15:22:55 by fyardimc          #+#    #+#             */
/*   Updated: 2022/10/17 15:22:55 by fyardimc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

static int	init_sem(t_arg *rules)
{
	sem_unlink("/sem_forks");
	sem_unlink("/sem_write");
	sem_unlink("/sem_mealcheck");
	sem_unlink("/sem_diedcheck");
	rules->forks = sem_open("/sem_forks", O_CREAT, S_IRWXU, rules->philo_count);
	rules->writing = sem_open("/sem_write", O_CREAT, S_IRWXU, 1);
	rules->meal_check = sem_open("/sem_mealcheck", O_CREAT, S_IRWXU, 1);
	rules->meal_check = sem_open("/sem_diedcheck", O_CREAT, S_IRWXU, 1);
	if (rules->forks == SEM_FAILED || rules->writing == SEM_FAILED
		|| rules->meal_check == SEM_FAILED || rules->died_check == SEM_FAILED)
		return (error_message("sem_open failed!"));
	return (0);
}

static int	init_philosophers(t_arg *rules)
{
	int	i;

	i = rules->philo_count;
	while (--i >= 0)
	{
		rules->philosophers[i].id = i;
		rules->philosophers[i].ate_count = 0;
		rules->philosophers[i].t_last_meal = 0;
		rules->philosophers[i].rules = rules;
	}
	return (0);
}

int	init_data(t_arg *rules, char **argv)
{
	rules->philo_count = ft_atoi(argv[1]);
	rules->time_to_die = ft_atoi(argv[2]);
	rules->time_to_eat = ft_atoi(argv[3]);
	rules->time_to_sleep = ft_atoi(argv[4]);
	rules->died = 0;
	rules->philosophers = malloc(sizeof(t_philosopher) * rules->philo_count);
	if ((rules->philo_count < 1 || rules->philo_count > MAX_INT)
		|| rules->time_to_die < 0
		|| rules->time_to_eat < 0 || rules->time_to_sleep < 0)
		return (error_message("Incorrect argument input detected!"));
	if (argv[5])
	{
		rules->number_must_eat = ft_atoi(argv[5]);
		if (rules->number_must_eat <= 0)
			return (error_message("Incorrect argument input detected!"));
	}
	else
		rules->number_must_eat = -1;
	if (init_sem(rules))
		return (error_message("Can't initilize semaphores!!!"));
	if (init_philosophers(rules))
		return (error_message("philo don't\
        want to eat spagetti :( they chose to die..."));
	return (0);
}
