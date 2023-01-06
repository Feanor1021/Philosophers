/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyardimc <fyardimc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 18:07:08 by fyardimc          #+#    #+#             */
/*   Updated: 2022/10/16 18:11:14 by fyardimc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct philo
{
	int				id;
	int				left_hand;
	int				right_hand;
	int				meal_count;
	long long		last_eat;
	pthread_t		philos;
	struct rules	*rules;
}					t_philo;

typedef struct rules
{
	int				philo_num;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				must_eat;
	long long		first_time;
	int				died;
	int				all_ate;
	int				i;
	pthread_mutex_t	*forks;
	pthread_mutex_t	writing;
	pthread_mutex_t	die_check;
	t_philo			*philo;
}					t_arg;

//color
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define END "\033[0m"
# define BLUE "\e[0;34m"

//Resource handler functions
int					handle_resources(t_arg *rules);
void				*resources(void *philo);
int					eat_spagetti(t_philo *ph);
void				*resources(void *philo);
void				destroy_all(t_arg *rules);
void				dead_checker(t_arg *rules);

//initilaziation
int					teach_ph(t_arg *rules);
int					init_mutexes(t_arg *rules);
int					set_rules(t_arg *rules, char **argv, int argc);
int					check_args(t_arg *rules, int argc);

//utils
int					ft_atoi(const char *str);
void				action_philo(char *message, t_arg *rules, int phid);

//time functions
long long			time_diff(long long past, long long pres);
long long			timestamp(void);
void				wait_sleep(long long wait_time, t_arg *rules);

//errors
int					error_message(char *arg);

#endif