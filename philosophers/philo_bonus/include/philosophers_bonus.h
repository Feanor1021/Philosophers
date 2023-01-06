/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyardimc <fyardimc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 15:22:22 by fyardimc          #+#    #+#             */
/*   Updated: 2022/10/17 15:22:22 by fyardimc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H
# define MAX_INT 2147483647

# include <sys/time.h>
# include <sys/wait.h>
# include <signal.h>
# include <semaphore.h>
# include <pthread.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_philosopher
{
	int				id;
	int				ate_count;
	long long		t_last_meal;
	struct s_rules	*rules;
	pthread_t		died;
	pid_t			pid;
}	t_philosopher;

typedef struct s_rules
{
	int				philo_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_must_eat;
	int				died;
	long long		first_timestamp;
	sem_t			*died_check;
	sem_t			*forks;
	sem_t			*writing;
	sem_t			*meal_check;
	t_philosopher	*philosophers;
}	t_arg;

//color
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define END "\033[0m"
# define BLUE "\e[0;34m"

// ERROR_MANAGER.C
int						error_message(char *str);

// INIT.C
int						init_data(t_arg *rules, char **argv);

// UTILS.C
int						ft_atoi(const char *str);
void					action_philo(t_arg *rules, int id, char *string);

// time functions
long long				timestamp(void);
long long				time_diff(long long past, long long pres);
void					wsleep(long long time, t_arg *rules);

// Resource handlers
void					eat_spagetti(t_philosopher *philo);
void					resources(void *void_philosopher);
void					*death_checker(void *p);
int						handle_resources(t_arg *rules);
void					exit_launcher(t_arg *rules);
#endif
