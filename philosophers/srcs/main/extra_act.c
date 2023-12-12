
#include "philosophers.h"

bool	check_state(t_mutex *mutex, bool *val)
{
	bool ret;

	pthread_mutex_lock(mutex);
	ret = *val;
	pthread_mutex_unlock(mutex);
	return (ret);
}

static void	wait_threads(t_table *table)
{
	while (!check_state(&table->table_mutex, &table->threads_ready))
		;
}

static void	set_last_meal(t_mutex *mutex, long *dest, long value)
{
	pthread_mutex_lock(mutex);
	*dest = value;
	pthread_mutex_unlock(mutex);
}

static void increase_meals(t_mutex *mutex, long *count)
{
	pthread_mutex_lock(mutex);
	count++;
	pthread_mutex_unlock(mutex);
}