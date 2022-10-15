#include "philo.h"

long long	timestamp(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

long long	time_diff(long long past, long long pres)
{
	return (pres - past);
}

void wait_sleep(long long wait_time,t_arg *rules)
{
	long long i;

	i = timestamp();
	while (rules->died)
	{
		if(wait_time <= time_diff(i,timestamp()))
			break;
	}
}
