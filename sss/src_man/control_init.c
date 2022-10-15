#include "philo.h"

int init_mutexes(t_arg *rules)
{
    int i;

    i = 0;
    rules->philosophers=malloc(sizeof(t_philo)*rules->philo_num);
    rules->forks=malloc(sizeof(pthread_mutex_t)*rules->philo_num);
    while(i<rules->philo_num)
    {
        if(pthread_mutex_init(&(rules->forks[i]),NULL))
            return -1;
        i++;
    }
    if(pthread_mutex_init(&rules->writing,NULL))
        return -1;
    if(pthread_mutex_init(&rules->meal_d,NULL))
        return -1;
    return 0;
}

int teach_ph(t_arg *rules)
{
    int i;

    i = 0;
    while(i<rules->philo_num)
    {
        rules->philosophers[i].id=i;
        rules->philosophers[i].right_hand=(i+1)%rules->philo_num;
        rules->philosophers[i].left_hand=i;
        rules->philosophers[i].last_meal_time=0;
        rules->philosophers[i].meal_count=0;
        rules->philosophers[i].rules=rules;
        i++;
    }
    return 0;
}

int check_args(t_arg* rules,int argc)
{
    if(argc == 5){
    if((rules->philo_num < 1) || rules->die_time <0 ||
    rules->eat_time <0 || rules->sleep_time<0)
        return 1;
    }
    if(argc == 6)
        if(rules->must_eat <0 )
        return 1;
    return 0;
}

int set_rules(t_arg *rules,char** argv,int argc)
{
    rules->philo_num=ft_atoi(argv[1]);
    rules->die_time=ft_atoi(argv[2]);
    rules->eat_time=ft_atoi(argv[3]);
    rules->sleep_time=ft_atoi(argv[4]);
    rules->died=1;
    rules->all_ate=1;
    if(argc == 6)
        rules->must_eat=ft_atoi(argv[5]);
    else
        rules->must_eat=-1;
    if(check_args(rules,argc))
        return error_message("Wrong argument format!!!");
    if(init_mutexes(rules))
        return error_message("Can't initilize mutexes!!!");
    if(teach_ph(rules))
        return error_message("Philosophers don't want to eat spagetti :( they chose to die...");
    return 0;
}