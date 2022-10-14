/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otokluog <otokluog@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 10:49:12 by otokluog          #+#    #+#             */
/*   Updated: 2022/10/03 11:21:56 by otokluog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	init_mutex(t_rules *rules)
{
	int	i;

	i = -1;
	while (++i < rules->philo_count)
	{
		if (pthread_mutex_init(&rules->forks[i], NULL))
			return (write_error("Fatal error when intializing mutex"));
	}
	if (pthread_mutex_init(&rules->writing, NULL))
		return (write_error("Fatal error when intializing mutex"));
	if (pthread_mutex_init(&rules->meal_check, NULL))
		return (write_error("Fatal error when intializing mutex"));
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
		rules->philosophers[i].left_fork_id = i;
		rules->philosophers[i].right_fork_id = (i + 1) % rules->philo_count;
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
	rules->all_ate = 0;
	rules->forks = malloc(sizeof(pthread_mutex_t) * rules->philo_count);
	rules->philosophers = malloc(sizeof(t_philosopher) * rules->philo_count);
	if ((rules->philo_count < 1 || rules->philo_count > MAX_INT)
		|| (rules->time_to_die <= 0 || rules->time_to_die > MAX_INT)
		|| (rules->time_to_eat <= 0 || rules->time_to_eat > MAX_INT)
		|| (rules->time_to_sleep <= 0 || rules->time_to_sleep > MAX_INT))
		return (write_error("Incorrect argument input detected!"));
	if (argv[5])
	{
		rules->number_must_eat = ft_atoi(argv[5]);
		if (rules->number_must_eat <= 0 || rules->number_must_eat > MAX_INT)
			return (write_error("Incorrect argument input detected!"));
	}
	else
		rules->number_must_eat = -1;
	if (init_mutex(rules))
		return (1);
	init_philosophers(rules);
	return (0);
}
