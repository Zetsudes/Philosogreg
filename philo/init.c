
# include "philo.h"

void	init_data(t_data *data)
{
	data->num_philos = 0;
	data->time_to_die = 0;
	data->time_to_eat = 0;
	data->time_to_sleep = 0;
	data->num_times = -1;
	data->dead = 0;
	pthread_mutex_init(&data->dead_mutex, NULL);
	pthread_mutex_init(&data->print_mutex, NULL); 
	gettimeofday(&data->start_time, NULL);
}

t_philo	*init_philos(t_data *data)
{
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

void	setup_philos(t_data *data, t_philo *philo, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		philo[i].id = i + 1;
		philo[i].data = data;
		philo[i].meals_eaten = 0;
		philo[i].last_meal_time = 0;
		philo[i].left_fork = &forks[i];
		philo[i].right_fork = &forks[(i + 1) % data->num_philos];
		pthread_mutex_init(&philo[i].last_meal_mutex, NULL);
		i++;
	}
}

void	delay_philo(t_philo *philo)
{
	if (philo->data->num_philos % 2 == 0) // If number of philos is even
	{
		if (philo->id == 0) // Delay the first one to avoid clash royale with last one
			usleep(300);
		else if (philo->id % 2 == 0) // If philo id is even, delay
			usleep(100);
	}
	else if (philo->id % 2 == 0) // If number of philos is odd delay
		usleep(100);
}