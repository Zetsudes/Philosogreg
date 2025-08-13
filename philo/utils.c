
# include "philo.h"

void    error_msg(char *msg, int exit_code)
{
    printf("%s", msg);
    exit (exit_code);
}

long	long_atoi(const char *str)
{
	long	res;
	int		sign;

	res = 0;
	sign = 1;
	if (!str || *str == '\0')
		return (-1);
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
		return (-1);
	if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		if (res > (LONG_MAX - (*str - '0')) / 10)
			return (-1);
		res = res * 10 + (*str - '0');
		str++;
	}
	if (*str != '\0')
		return (-1);
	return (res * sign);
}

long long	timestamp(t_data *data)
{
	struct timeval	now;
	long long	ms_now;
	long long	ms_start;

	gettimeofday(&now, NULL);
	ms_now = now.tv_sec * 1000LL + now.tv_usec / 1000;
	ms_start = data->start_time.tv_sec * 1000LL + data->start_time.tv_usec / 1000;
	return (ms_now - ms_start);
}

void safe_print(t_philo *philo, const char *msg)
{
    long long ts;

	pthread_mutex_lock(&philo->data->dead_mutex);
    pthread_mutex_lock(&philo->data->print_mutex);
    ts = timestamp(philo->data);
    if (!philo->data->dead)
        printf("%lld %d %s\n", ts, philo->id, msg);
    pthread_mutex_unlock(&philo->data->dead_mutex);
    pthread_mutex_unlock(&philo->data->print_mutex);
}

void	cleanup(t_data *data, t_philo *philos, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_destroy(&forks[i]);
		pthread_mutex_destroy(&philos[i].last_meal_mutex);
		pthread_mutex_destroy(&philos[i].meals_eaten_mutex);
		i++;
	}
	pthread_mutex_destroy(&data->dead_mutex);
	pthread_mutex_destroy(&data->print_mutex);
	free(forks);
	free(philos);
}
