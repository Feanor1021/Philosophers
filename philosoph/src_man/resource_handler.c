#include "philo.h"

int eat_spagetti(t_philo *ph)
{
    pthread_mutex_lock(&(ph->rules->forks[ph->left_hand]));
    action_philo("\e[0;34mhas taken a fork🍴🤤\n\033[0m",ph->rules,ph->id);
    if (ph->rules->philo_num == 1)
        return 1;
    pthread_mutex_lock(&(ph->rules->forks[ph->right_hand]));
    action_philo("\e[0;34mhas taken a fork🤤🍴\n\033[0m",ph->rules,ph->id);
    action_philo("\033[0;32mis eating 🍝\n\033[0m",ph->rules,ph->id);
    ph->last_meal_time=timestamp();
    wait_sleep(ph->rules->eat_time,ph->rules);
    ph->meal_count++;
    pthread_mutex_unlock(&(ph->rules->forks[ph->right_hand]));
    pthread_mutex_unlock(&(ph->rules->forks[ph->left_hand]));
    return 0;
}

void *resources(void *philosophers)
{
    t_philo     *ph;
    ph=(t_philo*)philosophers;

    if (ph->id%2==1)
        usleep(2000);
    while(ph->rules->died)
    {   
        if (ph->rules->all_ate==0)
			break ;
        if(eat_spagetti(ph))
            return NULL;
        action_philo("\033[0;33mis sleeping 😴\n\033[0m",ph->rules,ph->id);
        wait_sleep(ph->rules->sleep_time,ph->rules);
        action_philo("\033[0;33mis tkinking 🤔\n\033[0m",ph->rules,ph->id); 
    }
    return NULL;
}

void destroy_all(t_arg *rules)
{
    int i;

    i = 0;
    while(rules->philo_num>i)
    {
        pthread_join((rules->philosophers+i)->philos,NULL);
        i++;
    }
    i = 0;
    while (rules->philo_num > i)
    {
        pthread_mutex_destroy(&rules->forks[i]);
        i++;
    }
    pthread_mutex_destroy(&rules->writing);
    pthread_mutex_destroy(&rules->meal_d);
    free(rules->forks);
    free(rules->philosophers);
}

void dead_checker(t_arg *rules)
{
    int i;

    while(rules->all_ate)
    {
        i = 0;
        while (i < rules->philo_num && rules->died)
        {
            if(time_diff((rules->philosophers+i)->last_meal_time,timestamp())>rules->die_time)
            {
                action_philo("\033[0;31mdied💀\n",rules,rules->philosophers->id);
                rules->died=0;
            }
            i++;
        }
        if(rules->died==0)
            break;
        i=0;
		while (rules->must_eat != -1 && i < rules->philo_num
			&& rules->philosophers[i].meal_count >= rules->must_eat)
            i++;
        if(i==rules->philo_num)
            rules->all_ate=0;
    }
}

int handle_resources(t_arg *rules)
{
    int i;

    i = 0;
    rules->first_time=timestamp();
    while (i < rules->philo_num)
    {
        if(pthread_create(&((rules->philosophers+i)->philos),NULL,resources,rules->philosophers+i))
            return -1;
        (rules->philosophers+i)->last_meal_time=timestamp();
        i++;
    }
    dead_checker(rules);
    destroy_all(rules);
    return 0;
}