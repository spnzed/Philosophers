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
# include <errno.h>
# include <inttypes.h>

#define RESET   "\033[0m"
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define BLUE    "\033[1;34m"
#define MAGENTA "\033[1;35m"
#define CYAN    "\033[1;36m"
#define WHITE   "\033[1;37m"

typedef pthread_t 			t_thread;
typedef pthread_mutex_t 	t_mutex;

typedef enum e_philo_code
{
	EAT,
	SLEEP,
    THINK,
}	t_philo_code;

typedef enum e_pthread_code
{
	CREATE,
	JOIN,
	DETACH,
}   t_pthread_code;

typedef enum e_mutex_code
{
	LOCK,
	UNLOCK,
    INIT,
    DESTROY,
}	t_mutex_code;

typedef struct s_philo	t_philo;

typedef struct s_data
{
	long		philo_nbr;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	long		limit_meals_nbr;
	long		start_simulation;
	long		last_meal_time;
	long		threads_running;
}	t_data;

typedef struct s_fork
{
	t_mutex	fork;
	int		fork_id;
}	t_fork;

typedef struct s_table
{
	bool		threads_ready;
	t_fork		*forks;
	t_philo		*philos;
	t_thread	monitor;
	t_mutex		table_mutex;
}	t_table;

typedef struct s_philo
{
	int			philo_id;
	int			philo_position;
	long		meals_count;
	t_thread	thread_id;
	t_mutex		philo_mutex;
	t_fork		*left;
	t_fork		*right;
	t_table		*table;
	t_data		*data;
	bool		full;
	bool		dead;
}	t_philo;

//***************    PROTOTYPES     ***************

//***	main	***

//process the input
void    	parse_input(t_data *data, char **argv);
//init table and philos data
bool		prepare_table(t_table *table, t_data *data);
//🥩
bool		start_dinning(t_table *table, t_data *data);
//routines
void		*one_philo(void *pointer);
void		*dinner_routine(void *data);
void		*monitor(void *);
void 		philo_does(t_philo_code code, t_philo *philo);


//***	utils	***
int			ft_atoi(const char *str);
long		ft_atol(const char *str);
void		ft_clear_data(t_table *table);
bool		ft_error(char *str);
bool		ft_found(char c, char *str);
long		ft_get_time(void);
int			ft_input_checker(char **argv);
bool		ft_safe_mutex(t_mutex *mutex, t_mutex_code code);
bool		ft_safe_thread(t_thread *thread, void *(*function)(void *), void *data, t_pthread_code code);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_usleep(useconds_t time);

#endif
