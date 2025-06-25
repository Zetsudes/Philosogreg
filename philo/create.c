
#include "philo.h"

void	create_threads(t_data *data, t_philo *philo)
{
	int			i;
	pthread_t	*thread_id;

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
		if (pthread_join(&philo[i].thread_id, NULL) != 0)
			error_msg("Error: pthread_join failed :(", 1);
		i++;
	}
}

void	*routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	if (philo->data->num_philos % 2 == 0) // If number of philos is even
	{
		if (philo->id == 0) // Delay the first one to avoid clash with last one
			usleep(300);
		else if (philo->id % 2 == 0) // If philo id is even, delay
			usleep(100);
	}
	// If number of philos is odd
	else if (philo->id % 2 == 0) // If philo id is even, delay
		usleep(100);
}
