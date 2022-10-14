/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otokluog <otokluog@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 15:22:19 by otokluog          #+#    #+#             */
/*   Updated: 2022/10/04 15:22:19 by otokluog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

static int	init_sem(t_rules *rules)
{
	sem_unlink("/sem_forks");
	sem_unlink("/sem_write");
	sem_unlink("/sem_mealcheck");
	rules->forks = sem_open("/sem_forks", O_CREAT, S_IRWXU, rules->philo_count);
	rules->writing = sem_open("/sem_write", O_CREAT, S_IRWXU, 1);
	rules->meal_check = sem_open("/sem_mealcheck", O_CREAT, S_IRWXU, 1);
	if (rules->forks == SEM_FAILED || rules->writing == SEM_FAILED
		|| rules->meal_check == SEM_FAILED)
		return (write_error("sem_open failed!"));
	return (0);
}

static int	init_philosophers(t_rules *rules)
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

int	init_data(t_rules *rules, char **argv)
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
		return (write_error("Incorrect argument input detected!"));
	if (argv[5])
	{
		rules->number_must_eat = ft_atoi(argv[5]);
		if (rules->number_must_eat <= 0)
			return (write_error("Incorrect argument input detected!"));
	}
	else
		rules->number_must_eat = -1;
	if (init_sem(rules))
		return (1);
	init_philosophers(rules);
	return (0);
}
