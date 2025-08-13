#include "philo_bonus.h"

long long long_atoi(const char *str)
{
	long long	res;
	res = 0;
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - '0');
		str++;
	}
	return res;
}

void error_msg(char *msg, int code)
{
	while (*msg)
		write(2, msg++, 1);
	exit(code);
}

int is_valid_arg(char *str)
{
	long	arg;
	char	*start;

	if (*str == '-' || *str == '\0')
		return (0);
	if (*str == '+')
		str++;
	start = str;
	while (*str)
	{
		if (!(*str >= '0' && *str <= '9'))
			return (0);
		str++;
	}
	arg = long_atoi(start);
	if (arg <= 0 || arg > INT_MAX)
		return (0);
	return (1);
}

void parse_args(t_data *data, int argc, char **argv)
{
	int	i;

	if (argc != 5 && argc != 6)
		error_msg("error: invalid number of arguments\n", 1);
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
	else
		data->num_times = -1;
}
