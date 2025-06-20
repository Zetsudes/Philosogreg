
# include "philo.h"

void	parse_args(t_data *data, int argc, char **argv)
{
	int i;

	if (argc != 5 && argc != 6)
        error_msg("error: too few arguments\n", 1);
	i = 1;
    while (i < argc)
    {
        if (!is_valid_arg(argv[i]))
            error_msg("error: invalid argument(s)\n", 1);
        i++;
	}
	data->num_philos = long_atoi(argv[1]);
	data->time_to_die = long_atoi(argv[2]);
	data->time_to_eat = long_atoi(argv[3]);
	data->time_to_sleep = long_atoi(argv[4]);
	if (argc == 6)
		data->num_times = long_atoi(argv[5]);
}

int is_valid_arg(char *str)
{
    long    arg;
	char *start;

    if (*str == '-')
		error_msg("error: argument must be a positive int\n", 0);
    if (*str == '+')
        {str++;}
	if (*str == '\0')
		error_msg("error: argument is null\n", 0);
	start = str;
	while (*str)
	{
		if (!(*str >= 48 && *str <= 57))
			error_msg("error: argument must be of type int\n", 0);
		str++;
	}
    arg = long_atoi(start);
	if (arg > INT_MAX)
        error_msg("error: argument must be a valid int\n", 0);
	if (arg <= 0)
        error_msg("error: argument must be > 0\n", 0);
    return (1);
}

