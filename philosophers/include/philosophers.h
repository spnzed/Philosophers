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
	FORK,
	DIE,
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

typedef struct s_table	t_table;

typedef struct s_fork
{
	t_mutex	fork;
	int		fork_id;
}	t_fork;

typedef struct s_philo
{
	int			philo_id;
	int			philo_position;
	long		meals_count;
	long		last_meal_time;
	t_thread	thread_id;
	t_mutex		mutex;
	t_fork		*left;
	t_fork		*right;
	t_table		*table;
	bool		full;
	bool		dead;
}	t_philo;

typedef struct s_table
{
	long		philo_nbr;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	long		limit_meals_nbr;
	long		start_simulation;
	long		threads_running;
	t_thread	monitor;
	t_fork		*forks;
	t_philo		*philos;
	t_mutex		table_mutex;
	t_mutex		write_mutex;
	bool		end;
	bool		ready;
}	t_table;


//***************    PROTOTYPES     ***************

	//dinner_routine.c		routine
void		*dinner_routine(void *data);

	//parsing.c				process the input
bool		init_mutex(t_table *table);
bool		init_malloc(t_table *table);
void    	parse_input(t_table *table, char **argv);

	//philo_does.c
void 		print_action(t_philo *philo, char *str);
bool 		do_eat(t_philo *philo);
bool		do_sleep(t_philo *philo);
bool		do_think(t_philo *philo);
bool		dead(t_philo *philo);
void 		philo_does(t_philo_code code, t_philo *philo);

	//prepare.c
bool		prepare_table(t_table *table);

	//safe_data.c
void		safe_increase_long(t_mutex *mutex, long *count);
void		safe_put_long(t_mutex *mutex, long *dest, long value);
long		safe_get_long(t_mutex *mutex, long value);
void		safe_put_bool (t_mutex *mutex, bool *dest, bool val);
bool		safe_get_bool(t_mutex *mutex, bool *val);

	//special_cases.c
void		*one_philo(void *pointer);
void		*monitor(void *data);


	//start_dinning.c
bool		simulation_finished(t_table *table);
bool 		philo_is_full(t_philo *philo);
bool		start_dinning(t_table *table);



//***	utils	***
int			ft_atoi(const char *str);
long		ft_atol(const char *str);
bool		ft_error(char *str);
bool		ft_found(char c, char *str);
u_int64_t	ft_get_time(void);
int			ft_input_checker(char **argv);
bool		ft_safe_mutex(t_mutex *mutex, t_mutex_code code);
bool		ft_safe_thread(t_thread *thread, void *(*function)(void *), void *data, t_pthread_code code);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_usleep(long time);

#endif
