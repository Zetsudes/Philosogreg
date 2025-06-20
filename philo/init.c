
# include "philo.h"

void    init_simulation(t_data *data, t_philo **philos, pthread_mutex_t **forks)
{
    int i;

    *philos = malloc(sizeof(t_philo) * data->num_philos);
    if (!*philos)
        error_msg("Error: philo malloc failed :(", 1);
    *forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
    if (!*forks)
        error_msg("Error: fork malloc failed :(", 1);
    i = 0;
    while (i < data->num_philos)
	{
		if (pthread_mutex_init(&(*forks)[i], NULL) != 0)
			error_msg("fork mutex init failed", 1);
		i++;
	}
}