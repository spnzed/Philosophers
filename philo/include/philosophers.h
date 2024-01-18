/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaespino <aaespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 15:23:31 by aaespino          #+#    #+#             */
/*   Updated: 2024/01/18 13:55:01 by aaespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# define RESET   "\033[0m"
# define RED     "\033[1;31m"
# define GREEN   "\033[1;32m"
# define YELLOW  "\033[1;33m"
# define BLUE    "\033[1;34m"
# define MAGENTA "\033[1;35m"
# define CYAN    "\033[1;36m"
# define WHITE   "\033[1;37m"

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

typedef pthread_t			t_thread;
typedef pthread_mutex_t		t_mutex;
typedef struct s_table		t_table;

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
}	t_pthread_code;

typedef enum e_mutex_code
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
}	t_mutex_code;

typedef struct s_fork
{
	t_mutex	fork;
	int		fork_id;
}	t_fork;

typedef struct s_philo
{
	t_table		*table;
	t_thread	thread_id;
	t_fork		*left;
	t_fork		*right;
	t_mutex		mutex;
	int			meals_count;
	int			philo_id;
	int			philo_position;
	long		last_meal_time;
	long		time_to_die;
	long		limit_meals_nbr;
	bool		eating;
}	t_philo;

typedef struct s_table
{
	t_philo		*philos;
	t_philo		*monitor;
	t_thread	*threads;
	t_fork		*forks;
	t_mutex		mutex;
	t_mutex		write;
	int			philo_nbr;
	long		full_philos;
	long		limit_meals_nbr;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	long		start_simulation;
	bool		ready;
	bool		end;
}	t_table;

//***************    PROTOTYPES     ***************
	//actions.c		
void		wait_all_threads(t_table *table);
void		do_eat(t_philo *philo);
void		do_sleep(t_philo *philo);
void		do_think(t_philo *philo);
	//parsing.c				
int			parse_input(t_table *table, char **argv);
	//philo_does.c
void		print_act(long time, int id, char *string);
void		philo_does(t_philo_code code, t_philo *philo);
	//prepare.c
int			prepare_table(t_table *table);
	//routines.c		routine
void		*monitor(void *data);
void		*supervisor(void *data);
void		*lone_philo(void *data);
void		*dinner_routine(void *data);
	//safe_data.c
void		safe_increase_long(t_mutex *mutex, long *count);
void		safe_put_long(t_mutex *mutex, long *dest, long value);
long		safe_get_long(t_mutex *mutex, long value);
void		safe_put_bool(t_mutex *mutex, bool *dest, bool val);
bool		safe_get_bool(t_mutex *mutex, bool *val);
//***	utils	***
int			ft_atoi(const char *str);
long		ft_atol(const char *str);
int			ft_error(char *str);
bool		ft_found(char c, char *str);
long		ft_get_time(void);
int			ft_input_checker(char **argv);
bool		ft_safe_mutex(t_mutex *mutex, t_mutex_code code);
bool		ft_safe_thread(t_thread *thread, void *(*function)(void *),
				void *data, t_pthread_code code);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_usleep(long time);

#endif
