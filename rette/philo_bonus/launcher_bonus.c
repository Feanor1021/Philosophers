/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otokluog <otokluog@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 15:22:24 by otokluog          #+#    #+#             */
/*   Updated: 2022/10/04 15:22:24 by otokluog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	philo_eats(t_philosopher *philo)
{
	t_rules	*rules;

	rules = philo->rules;
	sem_wait(rules->forks);
	action_print(rules, philo->id, "has taken a fork");
	sem_wait(rules->forks);
	action_print(rules, philo->id, "has taken a fork");
	sem_wait(rules->meal_check);
	action_print(rules, philo->id, "is eating");
	philo->t_last_meal = timestamp();
	sem_post(rules->meal_check);
	smart_sleep(rules->time_to_eat, rules);
	philo->ate_count++;
	sem_post(rules->forks);
	sem_post(rules->forks);
}

void	*death_checker(void *p)
{
	t_philosopher	*philo;
	t_rules			*r;

	philo = (t_philosopher *)p;
	r = philo->rules;
	while (1)
	{
		sem_wait(r->meal_check);
		if (time_diff(philo->t_last_meal, timestamp()) > r->time_to_die)
		{
			action_print(r, philo->id, "died");
			r->died = 1;
			sem_wait(r->writing);
			exit(1);
		}
		sem_post(r->meal_check);
		if (r->died)
			break ;
		usleep(100);
		if (philo->ate_count >= r->number_must_eat && r->number_must_eat != -1)
			break ;
	}
	return (NULL);
}

void	p_process(void *void_philosopher)
{
	t_philosopher	*philo;
	t_rules			*rules;

	philo = (t_philosopher *)void_philosopher;
	rules = philo->rules;
	philo->t_last_meal = timestamp();
	pthread_create(&(philo->died), NULL, death_checker, void_philosopher);
	if (philo->id % 2)
		usleep(15000);
	while (!(rules->died))
	{
		if (philo->ate_count >= rules->number_must_eat
			&& rules->number_must_eat != -1)
			break ;
		philo_eats(philo);
		action_print(rules, philo->id, "is sleeping");
		smart_sleep(rules->time_to_sleep, rules);
		action_print(rules, philo->id, "is thinking");
	}
	pthread_join(philo->died, NULL);
	if (rules->died)
		exit(1);
	exit(0);
}

void	exit_launcher(t_rules *rules)
{
	int	i;
	int	ret;

	i = 0;
	while (i < rules->philo_count)
	{
		waitpid(-1, &ret, 0);
		if (ret != 0)
		{
			i = -1;
			while (++i < rules->philo_count)
				kill(rules->philosophers[i].pid, 15);
			break ;
		}
		i++;
	}
	sem_close(rules->forks);
	sem_close(rules->writing);
	sem_close(rules->meal_check);
	sem_unlink("/sem_forks");
	sem_unlink("/sem_write");
	sem_unlink("/sem_mealcheck");
}

int	launcher(t_rules *rules)
{
	int				i;
	t_philosopher	*phi;

	i = -1;
	phi = rules->philosophers;
	rules->first_timestamp = timestamp();
	while (++i < rules->philo_count)
	{
		phi[i].pid = fork();
		if (phi[i].pid < 0)
			return (1);
		if (phi[i].pid == 0)
			p_process(&(phi[i]));
		usleep(100);
	}
	exit_launcher(rules);
	return (0);
}
