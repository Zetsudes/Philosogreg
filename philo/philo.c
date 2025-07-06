
# include "philo.h"

int main(int argc, char **argv)
{
	t_data data;
	t_philo *philos;
	pthread_mutex_t *forks;
	pthread_t		monitor_thread;

	init_data(&data);
	parse_args(&data, argc, argv);
	philos = init_philos(&data);
	forks = init_forks(&data);
	setup_philos(&data, philos, forks);
	create_threads(&data, philos);
	if (pthread_create(&monitor_thread, NULL, &monitor, philos) != 0)
		error_msg("Error: monitor thread creation failed\n", 1);
	if (pthread_join(monitor_thread, NULL) != 0)
		error_msg("Error: monitor thread join failed\n", 1);
	cleanup(&data, philos, forks);
	return (0);
}
