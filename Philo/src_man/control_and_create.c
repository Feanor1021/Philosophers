#include "philo.h"

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
    if(argc == 6)
        rules->must_eat=ft_atoi(argv[5]);
    else
        rules->must_eat=-1;
    if(check_args(rules,argc))
        return error_message("Wrong argument format!!!");
    return 0;
}