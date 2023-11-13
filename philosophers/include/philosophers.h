#ifndef PHILO_LIB
#define PHILO_LIB
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>

typedef pthread_t t_thread;
typedef pthread_mutex_t t_mutex;

typedef struct s_fork
{
	t_mutex	fork;
	int		fork_id;
}	t_fork;

typedef struct s_philo
{
	int			philo_id;
	bool		full;
	long		meals_count;
	long		last_meal_time;
	t_thread	thread_id;
	t_fork		*first;
	t_fork		*second;
	t_mutex		philo_mutex;
	t_table		table;
}	t_philo;

typedef struct s_table
{
	long		philo_nbr;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	long		limit_meals_nbr;
	long		threads_running;
	long		start_simulation;
	bool		end_simulation;
	bool		threads_ready;
	t_thread	monitor;
	t_fork		*forks;
	t_philo		*philos;
	t_mutex		table_mutex;
	t_mutex		write_mutex;
}	t_table;

int		ft_atoi(const char *str);
long	ft_atol(const char *str);
int		ft_usleep(useconds_t time);

#endif
