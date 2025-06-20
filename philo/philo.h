
#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

typedef struct s_data 
{
    int		num_philos;
    int		time_to_die;
    int		time_to_eat;
    int		time_to_sleep;
    int		num_times;
}	t_data;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long long		last_meal_time; 
	pthread_t		thread_id;    
	pthread_mutex_t	*left_fork;  
	pthread_mutex_t	*right_fork;    
	struct s_data	*data;        
}	t_philo;


long        long_atoi(const char *str);
int         is_valid_arg(char *arg);
void        error_msg(char *msg, int exit_code);
void	    init_data(t_data *data);
void	    parse_args(t_data *data, int argc, char **argv);

#endif