
#include "philo_bonus.h"

int main(int argc, char **argv)
{
	t_data	data;

	parse_args(&data, argc, argv);

	data.pids = malloc(sizeof(pid_t) * data.num_philos);
	if (!data.pids)
		return (1);

	sem_unlink("/forks");
	sem_unlink("/writing");
	sem_unlink("/meal_check");
	data.forks = sem_open("/forks", O_CREAT, 0644, data.num_philos);
	data.writing = sem_open("/writing", O_CREAT, 0644, 1);
	data.meal_check = sem_open("/meal_check", O_CREAT, 0644, 1);

	start_simulation(&data);
	return (0);
}
