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

typedef pthread_t t_thread;
typedef pthread_mutex_t t_mutex;

#define RESET   "\033[0m"
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define BLUE    "\033[1;34m"
#define MAGENTA "\033[1;35m"
#define CYAN    "\033[1;36m"
#define WHITE   "\033[1;37m"

typedef enum e_mutex_code
{
	LOCK,
	UNLOCK,
    INIT,
    DESTROY,
}   t_pthread_code;

typedef enum e_pthread_code
{
	CREATE,
	JOIN,
	DETACH,
}   t_pthread_code;

typedef struct s_data
{
	long		philo_nbr;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	long		limit_meals_nbr;
}	t_data;

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
	t_fork		*left;
	t_fork		*right;
	t_data		*data;
	bool		full;
}	t_philo;

typedef struct s_table
{
	t_fork		*forks;
	t_philo		*philos;
}	t_table;

//***************    PROTOTYPES     ***************

//***	main	***

//process the input
void	    parse_input(t_data *data, t_table *table, char **argv);
//init table and philos data
void		prepare_table(t_table *table, t_data *data);
//🥩
void		start_eating(t_table *table, t_data *data);

//***	utils	***
int			ft_atoi(const char *str);
long		ft_atol(const char *str);
void		ft_clear_data(t_table *table);
int			ft_error(char *str);
void		ft_exit(t_table table);
bool		ft_found(char c, char *str);
u_int64_t	ft_get_time(void);
int			ft_input_checker(char **argv);
void	    *ft_safe_malloc(size_t bytes);
void		ft_safe_mutex(t_mutex *mutex, t_pthread_code code);
void		ft_safe_thread(t_thread *thread, t_pthread_code code);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_usleep(useconds_t time);

#endif
