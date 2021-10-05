#include "philo.h"

void	sleepy_time(int time, t_info *p)
{
	long	start;
	long	now;

	start = get_time_stamp();
	// void *p;
	now = start;
	// ft_putstr_nbr(p->goal, 1);
	while (time > now - start)
	{
		usleep(1);
		if (check_alive(p))
			return ;
		now = get_time_stamp();
	}
}

void	live_life_odd(t_info *p)
{
	while (1)
	{
		if (check_alive(p))
			return ;
		get_spoons(p);
		if (check_alive(p))
			return ;
		handle_sleep(p);
		if (check_alive(p))
			return ;
		// write(1, "lol", 3);
	}
	return ;
}

void	live_life_even(t_info *p)
{
	while (1)
	{
		if (check_alive(p))
			return ;
		handle_sleep(p);
		if (check_alive(p))
			return ;
		get_spoons(p);
		if (check_alive(p))
			return ;
	}
	return ;
}

void	*ft_life(void *test)
{
	t_info	*p;

	p = (t_info *)test;
	// p->born = get_time_stamp();
	gettimeofday(&p->born, NULL);
	// *p->p_last_meal = get_time_stamp();
	pthread_mutex_lock(&p[0].time_mutex);
	*p->p_last_meal = get_time_stamp();
	pthread_mutex_unlock(&p[0].time_mutex);
	// gettimeofday(&p->last_meal, NULL);
	if ((p->num_phi) % 2 != 0)
		live_life_odd(p);
	else
		live_life_even(p);
	return (NULL);
}

void	run_life(t_info *i)
{
	int	j;
	int	ret;
    pthread_t	*threads;

	j = 1;
    threads = malloc(sizeof(pthread_t) * (i[0].total_phi));
	ft_putstr_fd("Start:\n", 1);
	while (j < i[0].total_phi + 1)
	{
        // i[j].num_phi = j;
		// write(1, "ok", 2);
		// ft_putstr_nbr(i->num_phi, 1);
		// write(1, "ok", 2);
		ret = pthread_create(&threads[j - 1], NULL, ft_life, &i[j]);
		if (ret == -1)
		{
			ft_putstr_fd("error thread", 2);
			return ;
		}
		j++;
	}
	j = 1;
	while (j < i[0].total_phi + 1)
	{
		pthread_join(threads[j - 1], NULL);
		// write(1, "threads", 7);
		j++;
	}
	// j = 0;
	// while (j < i[0].total_phi)
	// {
	// 	free(&threads[j++]);
	// }
	free(threads);
}

int	main(int argc, char *argv[])
{
    t_info *i;
    pthread_t *t;

	if (argc < 5 || argc > 6)
		return (error_arg(0));
    i = malloc(sizeof(t_info) * (ft_atoi(argv[1]) + 1));
    t = malloc(sizeof(pthread_t));
	if (!i || !t)
		return (error_arg(2));
	if (get_param(argc, argv, i) == -1)
	{
		free(i);
		return (error_arg(1));
	}
	setting_up(i);
	pthread_create(t, NULL, deathwatch, i);
	run_life(i);
    pthread_join(*t, NULL);
	int j = 0;
	while (j < i[0].total_phi)
	{
		pthread_mutex_destroy(&i[0].spoons[j]);
		pthread_mutex_destroy(&i[0].p_death_mutex[j]);
		j++;
	}
	free(i[0].spoons);
	free(i[0].p_death_mutex);
	free(i);
	free(t);
	// while (i < info->philo)
	// 	pthread_mutex_destroy(&info->spoons[i++]);
	// pthread_mutex_destroy(&info->main);
	// // pthread_mutex_destroy(&info->main);
	// free(info->philos);
	// free(info->spoons);
	return (0);
}
