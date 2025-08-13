# include "philo.h"

int check_philo_death(t_philo *philo)
{
    long long time_since_meal;
    int meals;

    pthread_mutex_lock(&philo->meals_eaten_mutex);
    meals = philo->meals_eaten;
    pthread_mutex_unlock(&philo->meals_eaten_mutex);
    if (philo->data->num_times != -1 && meals >= philo->data->num_times)
        return (0);
    pthread_mutex_lock(&philo->last_meal_mutex);
    time_since_meal = timestamp(philo->data) - philo->last_meal_time;
    pthread_mutex_unlock(&philo->last_meal_mutex);
    if (time_since_meal > philo->data->time_to_die)
    {
        pthread_mutex_lock(&philo->data->dead_mutex);
        if (!philo->data->dead)
        {
            philo->data->dead = 1;
            print_death(philo);
        }
        pthread_mutex_unlock(&philo->data->dead_mutex);
        return (1);
    }
    return (0);
}

void print_death(t_philo *philo)
{
    long long ts;

    pthread_mutex_lock(&philo->data->print_mutex);
    ts = timestamp(philo->data);
    printf("%lld %d died\n", ts, philo->id);
    pthread_mutex_unlock(&philo->data->print_mutex);
}

int	all_stomachs_full(t_philo *philos)
{
	int	i;
	int meals;

	i = 0;
	while (i < philos[0].data->num_philos)
	{
		pthread_mutex_lock(&philos[i].meals_eaten_mutex);
		meals = philos[i].meals_eaten;
		pthread_mutex_unlock(&philos[i].meals_eaten_mutex);
		if (meals < philos[0].data->num_times)
			return (0);
		i++;
	}
	return (1);
}

void	*monitor(void *arg)
{
	t_philo	*philos;
	int		i;

	philos = (t_philo *)arg;
	while (1)
	{
		i = 0;
		while (i < philos[0].data->num_philos)
		{
			if (check_philo_death(&philos[i]))
				return (NULL);
			i++;
		}
		if (philos[0].data->num_times != -1 && all_stomachs_full(philos)) // If all philosophers ate enough, stop simulation
		{
			pthread_mutex_lock(&philos[0].data->dead_mutex);
			philos[0].data->dead = 1;
			pthread_mutex_unlock(&philos[0].data->dead_mutex);
			return (NULL);
		}
		usleep(1000);
	}
} 