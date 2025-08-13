#include "philo_bonus.h"

long get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void smart_sleep(long time, t_data *data)
{
	long	start;

	start = get_time();
	while ((get_time() - start) < time)
		usleep(100);
	(void)data;
}

void print_action(t_philo *philo, char *action)
{
	sem_wait(philo->data->writing);
	printf("%ld %d %s\n", get_time() - philo->data->start_time, \
	philo->id, action);
	sem_post(philo->data->writing);
}

void cleanup(t_data *data)
{
	int	i;

	i = 0;
	if (data->pids)
	{
		while (i < data->num_philos)
		{
			kill(data->pids[i], SIGTERM);
			i++;
		}
		free(data->pids);
	}
	sem_close(data->forks);
	sem_close(data->writing);
	sem_close(data->meal_check);
	sem_unlink("/forks");
	sem_unlink("/writing");
	sem_unlink("/meal_check");
}
