#include "philo.h"

int error_message(char *arg)
{
    ft_printf("%s%s%s",RED,arg,END);
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
    if (res >= 0 && res <= 2147483647)
	    return max_min_cntrl(num);
    return -1;
}