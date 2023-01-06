/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resource_handler_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyardimc <fyardimc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 15:23:02 by fyardimc          #+#    #+#             */
/*   Updated: 2022/10/17 15:23:02 by fyardimc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	eat_spagetti(t_philosopher *philo)
{
	t_arg	*rules;

	rules = philo->rules;
	sem_wait(rules->forks);
	action_philo(rules, philo->id, "\e[0;34mhas taken a fork🍴🤤\n\033[0m");
	sem_wait(rules->forks);
	action_philo(rules, philo->id, "\e[0;34mhas taken a fork🤤🍴\n\033[0m");
	sem_wait(rules->meal_check);
	action_philo(rules, philo->id, "\033[0;32mis eating 🍝\n\033[0m");
	philo->t_last_meal = timestamp();
	sem_post(rules->meal_check);
	wsleep(rules->time_to_eat, rules);
	philo->ate_count++;
	sem_post(rules->forks);
	sem_post(rules->forks);
}

void	resources(void *void_philosopher)
{
	t_philosopher	*philo;
	t_arg			*rules;

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
		eat_spagetti(philo);
		action_philo(rules, philo->id, "\033[0;33mis sleeping 😴\n\033[0m");
		wsleep(rules->time_to_sleep, rules);
		action_philo(rules, philo->id, "\033[0;33mis tkinking 🤔\n\033[0m");
	}
	pthread_join(philo->died, NULL);
	if (rules->died)
		exit(1);
	exit(0);
}

void	*death_checker(void *p)
{
	t_philosopher	*philo;
	t_arg			*r;

	philo = (t_philosopher *)p;
	r = philo->rules;
	while (1)
	{
		sem_wait(r->meal_check);
		if (time_diff(philo->t_last_meal, timestamp()) > r->time_to_die)
		{
			action_philo(r, philo->id, "\033[0;31mdied💀\033[0m\n");
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

void	exit_launcher(t_arg *rules)
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
	sem_unlink("/sem_diedcheck");
}

int	handle_resources(t_arg *rules)
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
			resources(&(phi[i]));
		usleep(100);
	}
	exit_launcher(rules);
	return (0);
}
