
#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_data
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_times;
	int				dead;
	pthread_mutex_t			dead_mutex;
	pthread_mutex_t 		print_mutex;
	struct timeval				start_time;
}					t_data;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long long		last_meal_time;
	pthread_t		thread_id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	last_meal_mutex;
	pthread_mutex_t	meals_eaten_mutex;
	struct s_data	*data;
}					t_philo;

long				long_atoi(const char *str);
void				error_msg(char *msg, int exit_code);
long long			timestamp(t_data *data);
void 				safe_print(t_philo *philo, const char *msg);
void				cleanup(t_data *data, t_philo *philos, pthread_mutex_t *forks);

int					is_valid_arg(char *arg);
void				init_data(t_data *data);
void				parse_args(t_data *data, int argc, char **argv);

t_philo				*init_philos(t_data *data);
pthread_mutex_t		*init_forks(t_data *data);
void				setup_philos(t_data *data, t_philo *philo, pthread_mutex_t *fork);

void				create_threads(t_data *data, t_philo *philo);
void				philo_eat_sleep(t_philo *philo);
void				take_forks(t_philo *philo);
int					run_simulation(t_philo *philo);
void				*routine(void *arg);

int					check_philo_death(t_philo *philo);
int					all_stomachs_full(t_philo *philos);
void 				print_death(t_philo *philo);
void				*monitor(void *arg);
void 				philo_sleep(t_philo *philo, long long sleep_time_ms);
#endif
