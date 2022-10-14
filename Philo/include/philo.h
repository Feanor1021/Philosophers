#ifndef PHILO_H
#define PHILO_H

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <../ft_printf/include/ft_printf.h>


typedef struct philo
{
    int id;
    int left_hand;
    int right_hand;
    int meal_count;
    long long last_meal_time;
    pthread_mutex_t *philos;
    struct rules *rules;
}t_philo;


typedef struct rules
{
    int philo_num;
    int die_time;
    int eat_time;
    int sleep_time;
    int must_eat;
    long long first_time;
    int	died;
	int	all_ate;
	pthread_mutex_t	*forks;
    t_philo *philosophers;
}t_arg;

//color
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define END "\033[0m"
# define BLUE "\e[0;34m"

//utils
int	ft_atoi(const char *str);
int set_rules(t_arg *rules,char** argv, int argc);
int check_args(t_arg* rules,int argc);

//screens
void start_screen(void);

//errors
int error_message(char *arg);

#endif