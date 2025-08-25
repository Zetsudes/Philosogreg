
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
}

void	philo_eat(t_philo *philo)
{
	if (check_philo_death(philo))
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return;
	}
	safe_print(philo, "is eating");
	update_meal_time(philo);
	philo_sleep(philo, philo->data->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	update_meal_time(philo);
	pthread_mutex_lock(&philo->meals_eaten_mutex);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meals_eaten_mutex);
	if (check_philo_death(philo))
		return;
	safe_print(philo, "is sleeping");
	philo_sleep(philo, philo->data->time_to_sleep);
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
	int meals;

	if (check_philo_death(philo))
		return (0);
	pthread_mutex_lock(&philo->data->dead_mutex);
	alive = (philo->data->dead == 0);
	pthread_mutex_unlock(&philo->data->dead_mutex);
	if (!alive)
		return (0); // Philo dead :(
	pthread_mutex_lock(&philo->meals_eaten_mutex);
	meals = philo->meals_eaten;
	pthread_mutex_unlock(&philo->meals_eaten_mutex);
	if (philo->data->num_times != -1 && meals >= philo->data->num_times)
		return (0); // Philo ate enough
	return (1);
}

void	*routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	if (philo->data->num_philos == 1)
    {
        pthread_mutex_lock(philo->left_fork);
        safe_print(philo, "has taken a fork");
        philo_sleep(philo, philo->data->time_to_die);
        pthread_mutex_unlock(philo->left_fork);
        return (NULL);
    }
	while (run_simulation(philo))
	{
	take_forks(philo);
	philo_eat(philo);
	safe_print(philo, "is thinking");
	}
	return (NULL);
} 