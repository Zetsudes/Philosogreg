
# include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	init_data(&data);
	parse_args(&data, argc, argv);

	printf("Number of philosophers: %d\n", data.num_philos);
	printf("Time to die: %d\n", data.time_to_die);
	printf("Time to eat: %d\n", data.time_to_eat);
	printf("Time to sleep: %d\n", data.time_to_sleep);
	if (argc == 6)
		printf("Number of times each philosopher must eat: %d\n", data.num_times);
	return (0);
}