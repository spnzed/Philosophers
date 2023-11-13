#ifndef PHILO_LIB
#define PHILO_LIB
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>
# include <limits.h>

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

//	main
//parsing.c
void	    parse_input(t_table *table, char **argv);
//	utils
int			ft_atoi(const char *str);
long		ft_atol(const char *str);
void		ft_clear_data(t_table *table);
int			ft_error(char *str);
void		ft_exit(t_table table);
bool		ft_found(char c, char *str);
u_int64_t	ft_get_time(void);
int			ft_input_checker(char **argv);
void	    *ft_safe_malloc(size_t bytes);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_usleep(useconds_t time);

#endif
