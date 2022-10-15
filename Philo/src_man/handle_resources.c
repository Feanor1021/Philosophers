#include "philo.h"

int eat_spagetti(t_philo *ph)
{
    pthread_mutex_lock(&ph->rules->forks[ph->left_hand]);
    action_philo("has taken a fork🍴\n",ph->rules,ph->id);
    pthread_mutex_lock(&ph->rules->forks[ph->right_hand]);
    action_philo("has taken a fork🍴\n",ph->rules,ph->id);
    action_philo("is eating 🍝\n",ph->rules,ph->id);

    wait_sleep(ph->rules->eat_time,ph->rules);
    pthread_mutex_unlock(&ph->rules->forks[ph->left_hand]);
    pthread_mutex_unlock(&ph->rules->forks[ph->right_hand]);
    return 0;
}

void *resources(void *philosophers)
{
    t_philo *ph;
    ph=(t_philo*)philosophers;

    if (ph->id%2==0)
        usleep(2000);
    while(ph->rules->died)
    {
            eat_spagetti(ph);
            action_philo("is sleeping 💤\n",ph->rules,ph->id);
            wait_sleep(ph->rules->sleep_time,ph->rules);
            action_philo("is tkinking 🤔\n",ph->rules,ph->id); 
    }
    return NULL;
}

void dead_checker()
{

}

int handle_resources(t_arg *rules)
{
    int i;

    i = 0;
    rules->first_time=timestamp();
    printf("w");
    while (i < rules->philo_num)
    {
        if(pthread_create(&((rules->philosophers+i)->philos),NULL,resources,rules->philosophers+i)!=0)
            return -1;
        rules->philosophers->last_meal_time=timestamp();
        i++;
    }
    return 0;
}