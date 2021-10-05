#	ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_info
{
	int				total_phi;
	int				num_phi;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				goal;
	int				is_dead;
	long			last_meal;
	int				is_full;
	long			*p_last_meal;
	int				*p_is_dead;
	int				*p_is_full;
	struct timeval	born;
	pthread_mutex_t	left_spoon;
	pthread_mutex_t right_spoon;
	pthread_mutex_t	*p_death_mutex;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	goal_mutex;
	pthread_mutex_t	time_mutex;
	pthread_mutex_t	main;
	pthread_mutex_t	*spoons;
}t_info;

/*
**main
*/
void	sleepy_time(int time, t_info *p);

/*
**philo
*/
void	handle_food(t_info *p);
void	get_spoons(t_info *p);
void	handle_sleep(t_info *p);
int	check_alive(t_info *p);
void	speaker(t_info *i, int n, char *str);

/*
**deathwatch
*/
long	get_time_stamp(void);
int	get_time(struct timeval born);
int		dead(t_info *v);
int good_meal(t_info *v);
void	*deathwatch(void *p);

/*
**setup
*/
int	error_arg(int num);
int	get_param(int argc, char **argv, t_info *i);
void    copy_param(t_info *i);
int	create_spoons(t_info *i);
void    setting_up(t_info *i);

/*
**basic_utils
*/
void	ft_putstr_fd(char *s, int fd);
void	ft_putstr_nbr(int i, int fd);
int		ft_isdigit(int c);
int		ft_atoi(const char *str);

/*
**ft_itoa
*/
char	*ft_itoa(int n);

#endif