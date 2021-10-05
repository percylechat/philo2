#include "philo.h"

int	error_arg(int num)
{
	if (num == 0)
		ft_putstr_fd("Error: arguments\n", 2);
	else if (num == 1)
		ft_putstr_fd("Error: invalid parameter\n", 2);
    else if (num == 2)
		ft_putstr_fd("Error: malloc\n", 2);
	return (-1);
}

int	get_param(int argc, char **argv, t_info *i)
{
	i[0].total_phi = ft_atoi(argv[1]);
	i[0].die_time = ft_atoi(argv[2]);
	i[0].eat_time = ft_atoi(argv[3]);
	i[0].sleep_time = ft_atoi(argv[4]);
	if (argc == 6)
	{
		i[0].goal = ft_atoi(argv[5]);
		if (i[0].goal == -1)
			return (-1);
	}
	else
		i[0].goal = -1;
	if (i[0].total_phi == -1 || i[0].die_time == -1 || i[0].eat_time == -1 || \
		i[0].sleep_time == -1)
		return (-1);
	if (i[0].total_phi == 0)
		return (-1);
	return (0);
}

void    copy_param(t_info *i)
{
    int j;
	// pthread_mutex_t death_m;

    j = 1;
	i[0].p_death_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * i[0].total_phi + 1);
	pthread_mutex_init(&i[0].time_mutex, NULL);
    pthread_mutex_init(&i[0].goal_mutex, NULL);
    // pthread_mutex_init(&i[0].death_mutex, NULL);
	// pthread_mutex_init(&death_m, NULL);
	// i[0].death_mutex = &death_m;
    pthread_mutex_init(&i[0].main, NULL);
    while (j < i[0].total_phi + 1)
    {
		write(1, "ok", 2);
        i[j].total_phi = i[0].total_phi;
    	i[j].die_time = i[0].die_time;
	    i[j].eat_time = i[0].eat_time;
	    i[j].sleep_time = i[0].sleep_time;
        i[j].goal = i[0].goal;
        i[j].goal_mutex = i[0].goal_mutex;
		pthread_mutex_init(&i[0].p_death_mutex[j - 1], NULL);
		// i[j].death_mutex = i[0].p_death_mutex[j - 1];
        // i[j].death_mutex = i[0].death_mutex;
        i[j].main = i[0].main;
        i[j].time_mutex = i[0].time_mutex;
		i[j].last_meal = get_time_stamp();
        i[j].p_last_meal = &i[j].last_meal;
		i[0].is_dead = 0;
		i[j].is_full = i[0].goal;
        i[j].p_is_dead = &i[0].is_dead;
        i[j].p_is_full = &i[j].is_full;
		i[j].num_phi = j;
        j++;
    }
}

int	create_spoons(t_info *i)
{
	int	j;

	j = 1;
	i[0].spoons = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * i[0].total_phi);
	if (!i[0].spoons)
		return (1);
	while (j < i->total_phi + 1)
	{
		pthread_mutex_init(&i[0].spoons[j - 1], NULL);
		i[j].left_spoon = i[0].spoons[j - 1];
		if (j == i->total_phi)
			i[j].right_spoon = i[0].spoons[0];
		else
			i[j].right_spoon = i[0].spoons[j];
		j++;
	}
    return (0);
}


void    setting_up(t_info *i)
{
    if (create_spoons(i) == -1)
        return ;
    copy_param(i);
// pari sur le last meal
}