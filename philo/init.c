
#include "philo.h"

t_philo	*init_philos(t_data *data)
{
	int		i;
	t_philo	*philos;

	philos = malloc(sizeof(t_philo) * data->num_philos);
	if (!philos)
		error_msg("Error: philo malloc failed :(", 1);
	return (philos);
}

pthread_mutex_t	*init_forks(t_data *data)
{
	int				i;
	pthread_mutex_t	*forks;

	forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	if (!forks)
		error_msg("Error: forks malloc failed :(", 1);
	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	return (forks);
}

void	setup_philos(t_data *data, t_philo *philos, pthread_mutex_t *forks)
{
	int i;

	i = 0;
	while (i < data->num_philos)
	{
		philos[i].id = i + 1;
		philos[i].data = data;
		philos[i].meals_eaten = 0;
		philos[i].last_meal_time = 0;
		philos[i].left_fork = &forks[i];
		philos[i].right_fork = &forks[(i + 1) % data->num_philos];
		i++;
	}
}
