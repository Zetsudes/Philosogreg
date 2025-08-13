#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <limits.h>
# include <fcntl.h> 
# include <sys/stat.h>
# include <sys/types.h> 
# include <sys/wait.h>  

typedef struct s_data
{
    int             num_philos;
    long            time_to_die;
    long            time_to_eat;
    long            time_to_sleep;
    int             num_times;
    sem_t           *forks;
    sem_t           *writing;
    sem_t           *meal_check;
    pid_t           *pids;
    long            start_time;
}               t_data;

typedef struct s_philo
{
    int         id;
    long        last_meal;
    int         meals_eaten;
    t_data      *data;
}               t_philo;

/* parsing.c */
void    parse_args(t_data *data, int argc, char **argv);
int     is_valid_arg(char *str);
long long long_atoi(const char *str);
void 		error_msg(char *msg, int code);

/* utils.c */
long    get_time(void);
void    smart_sleep(long time, t_data *data);
void    print_action(t_philo *philo, char *action);
void	cleanup(t_data *data);

/* actions.c */
void 	eat(t_philo *philo);
void	sleep_and_think(t_philo *philo);
void	monitor(void *arg);
void    philosopher_routine(t_philo *philo);
void    start_simulation(t_data *data);

#endif
