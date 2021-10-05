#include "philo.h"

void	handle_food(t_info *p)
{
	if (check_alive(p))
			return ;
	speaker(p, p->num_phi, " is eating\n");
	//test si un mutex ok ou need plusieurs
	pthread_mutex_lock(&p[0].goal_mutex);
	*p->p_is_full -= 1;
	if (*p->p_is_full == 0)	
		speaker(p, p->num_phi, " is full\n");
	pthread_mutex_unlock(&p[0].goal_mutex);
	pthread_mutex_lock(&p[0].time_mutex);
	*p->p_last_meal = get_time_stamp();
	pthread_mutex_unlock(&p[0].time_mutex);
	sleepy_time(p->eat_time, p);
	pthread_mutex_unlock(&p->right_spoon);
	pthread_mutex_unlock(&p->left_spoon);
}

void	get_spoons(t_info *p)
{
	if (check_alive(p))
			return ;
	if (p[0].total_phi > 1)
	{	
		pthread_mutex_lock(&p->left_spoon);
		speaker(p, p->num_phi, " has taken the spoon to his left\n");
		pthread_mutex_lock(&p->right_spoon);
		speaker(p, p->num_phi, " has taken the spoon to his right\n");
		handle_food(p);
	}
}

void	handle_sleep(t_info *p)
{
	if (check_alive(p))
		return ;
	speaker(p, p->num_phi, " is sleeping\n");
	sleepy_time(p->sleep_time, p);
	if (check_alive(p))
		return ;
	speaker(p, p->num_phi, " is thinking\n");
}

int	check_alive(t_info *p)
{
	int j;

	j = 1;
	// write(1, "ii", 2);
	while (j < p->total_phi + 1)
	{
		// write(1, "uu", 2);
		// printf("alive %p %d", &p[p->num_phi].death_mutex, p->num_phi);
		pthread_mutex_lock(&p[0].p_death_mutex[j - 1]);
		// write(1, "aa", 2);
		if (*(p->p_is_dead) == 1)
		{
			// write(1, "bb", 2);
			pthread_mutex_unlock(&p[0].p_death_mutex[j - 1]);
			return (1);
		}
		pthread_mutex_unlock(&p[0].p_death_mutex[j - 1]);
		j++;
	}
	return (0);
}

void	speaker(t_info *i, int n, char *str)
{
	pthread_mutex_lock(&i->main);
	// ft_putstr_nbr(n, 1);
	// ft_putstr_fd("ok", 1);
	printf("%u %d %s", get_time(i->born), n, str);
	pthread_mutex_unlock(&i->main);
}