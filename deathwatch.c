#include "philo.h"

long	get_time_stamp(void)
{
	struct timeval	tv;
	long			now;

	gettimeofday(&tv, NULL);
	now = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (now);
}

int	get_time(struct timeval born)
{
	int				time;
	struct timeval	now;

	gettimeofday(&now, NULL);
	time = (((long)now.tv_usec / 1000) + ((double)now.tv_sec * 1000)) - \
		(((long)born.tv_usec / 1000) + ((double)born.tv_sec * 1000));
	return (time);
}
//pb ici
int		dead(t_info *v)
{
    long now;
    int j;

    j = 1;
    usleep(1);
    while (j < v->total_phi + 1)
    {
        now = get_time_stamp();
        pthread_mutex_lock(&v->time_mutex);
        // printf("time %ld %ld %ld\n", now - *v[j].p_last_meal, now, *v[j].p_last_meal);
	    if (now - *v[j].p_last_meal > v[0].die_time)
        {
            // ft_putstr_nbr(now - *v[j].p_last_meal, 1);
		    pthread_mutex_unlock(&v->time_mutex);
            // pthread_mutex_lock(&v[0].death_mutex);
            printf("dead %p %d", &v[j].death_mutex, j);
            pthread_mutex_lock(&v[0].p_death_mutex[j - 1]);
            *(v[j].p_is_dead) = 1;
            // pthread_mutex_unlock(&v[0].death_mutex);
            pthread_mutex_unlock(&v[0].p_death_mutex[j - 1]);
            speaker(&v[j], j, " died");
            // ft_putstr_nbr(get_time(v[j].born, 1));
    		return (1);
	    }
        // write(1, "ok", 2);
        pthread_mutex_unlock(&v->time_mutex);
        j++;
    }
	return (0);
}

int good_meal(t_info *v)
{
    int j;
    int k;

    j = 1;
    k = 0;
    usleep(1);
    while (j < v->total_phi + 1)
    {
        pthread_mutex_lock(&v->goal_mutex);
	    if (*v[j].p_is_full == 0)
        {
		    pthread_mutex_unlock(&v->goal_mutex);
            k++;
	    }
        pthread_mutex_unlock(&v->goal_mutex);
        j++;
    }
    if (k == v[0].total_phi)
    {
        j = 1;
        while (j < v->total_phi + 1)
        {
            pthread_mutex_lock(&v[j].death_mutex);
            *(v[j++].p_is_dead) = 1;
            pthread_mutex_unlock(&v[j].death_mutex);
        }
        return (1);
    }
	return (0);
}

void	*deathwatch(void *p)
{
	t_info *v;

	v = (t_info *)p;
	while (!dead(v) && !good_meal(v))
		usleep(1000);
	return (NULL);
}