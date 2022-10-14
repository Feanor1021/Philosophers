/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otokluog <otokluog@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 10:49:07 by otokluog          #+#    #+#             */
/*   Updated: 2022/10/09 13:17:39 by otokluog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_eats(t_philosopher *philo)
{
	t_rules	*rules;

	rules = philo->rules;
	pthread_mutex_lock(&(rules->forks[philo->left_fork_id]));
	action_print(rules, philo->id, "has taken a fork");
	if (rules->philo_count == 1)
		exit_launcher(rules, philo);
	pthread_mutex_lock(&(rules->forks[philo->right_fork_id]));
	action_print(rules, philo->id, "has taken a fork");
	pthread_mutex_lock(&(rules->meal_check));
	action_print(rules, philo->id, "is eating");
	philo->t_last_meal = timestamp();
	pthread_mutex_unlock(&(rules->meal_check));
	smart_sleep(rules->time_to_eat, rules);
	(philo->ate_count)++;
	pthread_mutex_unlock(&(rules->forks[philo->right_fork_id]));
	pthread_mutex_unlock(&(rules->forks[philo->left_fork_id]));
}

void	*p_thread(void *void_philosopher)
{
	int				i;
	t_philosopher	*philo;
	t_rules			*rules;

	i = 0;
	philo = (t_philosopher *)void_philosopher;
	rules = philo->rules;
	if (philo->id % 2)
		usleep(15000);
	while (!(rules->died))
	{
		if (rules->all_ate)
			break ;
		philo_eats(philo);
		action_print(rules, philo->id, "is sleeping");
		smart_sleep(rules->time_to_sleep, rules);
		action_print(rules, philo->id, "is thinking");
		i++;
	}
	return (NULL);
}

void	exit_launcher(t_rules *rules, t_philosopher *philos)
{
	int	i;

	i = -1;
	if (time_diff(philos[++i].t_last_meal, timestamp()) > rules->time_to_die
		&& rules->philo_count == 1)
		action_print(rules, i, "died");
	while (++i < rules->philo_count)
		pthread_join(philos[i].thread_id, NULL);
	i = -1;
	while (++i < rules->philo_count)
		pthread_mutex_destroy(&(rules->forks[i]));
	pthread_mutex_destroy(&(rules->writing));
	pthread_mutex_destroy(&rules->meal_check);
	i = -1;
	while (++i < rules->philo_count)
		pthread_detach(philos[i].thread_id);
}

void	death_checker(t_rules *r, t_philosopher *p)
{
	int	i;

	while (!(r->all_ate))
	{
		i = -1;
		while (++i < r->philo_count && !(r->died))
		{
			pthread_mutex_lock(&(r->meal_check));
			if (time_diff(p[i].t_last_meal, timestamp()) > r->time_to_die)
			{
				action_print(r, i, "died");
				r->died = 1;
			}
			pthread_mutex_unlock(&(r->meal_check));
			usleep(100);
		}
		if (r->died)
			break ;
		i = 0;
		while (r->number_must_eat != -1 && i <= r->philo_count
			&& p[i].ate_count >= r->number_must_eat)
			i++;
		if (i == r->philo_count)
			r->all_ate = 1;
	}
}

int	launcher(t_rules *rules)
{
	int				i;
	t_philosopher	*phi;

	i = 0;
	phi = rules->philosophers;
	rules->first_timestamp = timestamp();
	while (i < rules->philo_count)
	{
		if (pthread_create(&(phi[i].thread_id), NULL, p_thread, &(phi[i])))
			return (1);
		phi[i].t_last_meal = timestamp();
		i++;
	}
	death_checker(rules, rules->philosophers);
	exit_launcher(rules, phi);
	return (0);
}
