#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
# include <sys/time.h>

#define THREAD_NUM 8

pthread_mutex_t mutexFuel;
int fuel = 50;

long long	timestamp(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
    printf("\n*%ld*\n",t.tv_sec);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

long long	time_diff(long long past, long long pres)
{
	return (pres - past);
}

int main(int argc, char *argv[])
{
    time_t now=time(NULL);    printf("%ld",now);
    time_t i;
    printf("%lld",i=timestamp());
    usleep(5000);

    printf("%f",difftime(i,(time_t)timestamp));

    return 0;
}