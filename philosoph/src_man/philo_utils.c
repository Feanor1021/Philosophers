#include "philo.h"

int error_message(char *arg)
{
    printf("%s%s%s",RED,arg,END);
    return -1;
}

int	ft_atoi(const char *str)
{
	long	num;

	num = 0;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
    if(*str=='+')
        str++;
    if(*str=='-')
       return -1;
	while (*str)
	{
        if(*str <= '9' && *str >= '0')
        {
		num = (num * 10) + (*str - 48);
		str++;
        }
        else
            return -1;
	}
    if (num >= 0 && num <= 2147483647)
	    return num;
    return -1;
}

void action_philo(char *message, t_arg* rules, int phid)
{
    pthread_mutex_lock(&rules->writing);
    if(rules->died)
    {
        printf("%s%lli%s",RED,time_diff(rules->first_time,timestamp()),END);
        printf("%s %i %s",YELLOW,phid+1,END);
        printf("%s",message);
    }
    pthread_mutex_unlock(&rules->writing);
}