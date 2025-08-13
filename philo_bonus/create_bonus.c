
#include "philo_bonus.h"

void eat(t_philo *philo)
{
	sem_wait(philo->data->forks);
	print_action(philo, "has taken a fork");
	sem_wait(philo->data->forks);
	print_action(philo, "has taken a fork");

	philo->last_meal = get_time();
	print_action(philo, "is eating");
	smart_sleep(philo->data->time_to_eat, philo->data);
	philo->meals_eaten++;

	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
}

void sleep_and_think(t_philo *philo)
{
	print_action(philo, "is sleeping");
	smart_sleep(philo->data->time_to_sleep, philo->data);
	print_action(philo, "is thinking");
}

void monitor(void *arg)
{
	t_philo	*philo;
	philo = (t_philo *)arg;
	while (1)
	{
		sem_wait(philo->data->meal_check);
		if ((get_time() - philo->last_meal) > philo->data->time_to_die)
		{
			print_action(philo, "died");
			exit(1);
		}
		sem_post(philo->data->meal_check);
		usleep(1000);
	}
}

void philosopher_routine(t_philo *philo)
{
	pthread_t	thread;

	philo->last_meal = get_time();
	pthread_create(&thread, NULL, (void *)monitor, philo);
	pthread_detach(thread);

	while (philo->data->num_times == -1 || philo->meals_eaten < philo->data->num_times)
	{
		eat(philo);
		sleep_and_think(philo);
	}
	exit(0);
}

void start_simulation(t_data *data)
{
	int		i;
	t_philo	philo;

	data->start_time = get_time();
	i = 0;
	while (i < data->num_philos)
	{
		philo.id = i + 1;
		philo.data = data;
		philo.meals_eaten = 0;
		data->pids[i] = fork();
		if (data->pids[i] == 0)
			philosopher_routine(&philo);
		usleep(100);
		i++;
	}
	i = 0;
	while (i < data->num_philos)
	{
		waitpid(data->pids[i], NULL, 0);
		i++;
	}
	cleanup(data);
}
