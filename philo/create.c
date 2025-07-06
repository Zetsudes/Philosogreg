
#include "philo.h"

void	create_threads(t_data *data, t_philo *philo)
{
	int			i;

	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_create(&philo[i].thread_id, NULL, &routine, &philo[i]) != 0)
			error_msg("Error: pthread_create failed :(", 1);
		i++;
	}
	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_join(philo[i].thread_id, NULL) != 0)
			error_msg("Error: pthread_join failed :(", 1);
		i++;
	}
}

void	philo_eat_sleep(t_philo *philo)
{
	long long	ts;

	ts = timestamp(philo->data); // Current time
	safe_print(philo, "is eating");
	pthread_mutex_lock(&philo->last_meal_mutex);
	philo->last_meal_time = ts;
	pthread_mutex_unlock(&philo->last_meal_mutex);
	usleep(philo->data->time_to_eat * 1000);
	philo->meals_eaten++;
	ts = timestamp(philo->data);
	safe_print(philo, "is sleeping");
	usleep(philo->data->time_to_sleep * 1000);
}

void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		safe_print(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		safe_print(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		safe_print(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		safe_print(philo, "has taken a fork");
	}
}

int	run_simulation(t_philo *philo) // Returns 0 if simulation should stop, 1 if not
{
	int	alive;

	pthread_mutex_lock(&philo->data->dead_mutex);
	alive = (philo->data->dead == 0);
	pthread_mutex_unlock(&philo->data->dead_mutex);
	if (!alive)
		return (0); // Philo dead :(
	if (philo->data->num_times != -1 && philo->meals_eaten >= philo->data->num_times)
		return (0); // Philo ate enough
	return (1);
}

void	*routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	delay_philo(philo);
	if (philo->data->num_philos == 1)
    {
        pthread_mutex_lock(philo->left_fork);
        safe_print(philo, "has taken a fork");
        usleep((philo->data->time_to_die + 100) * 1000);
        pthread_mutex_unlock(philo->left_fork);
        return NULL;
    }
	while (run_simulation(philo))
	{
	take_forks(philo);
	philo_eat_sleep(philo);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	safe_print(philo, "is thinking");
	usleep(100);
	}
	return (NULL);
} 