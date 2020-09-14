#ifndef _PHILO_ONE_H_
# define _PHILO_ONE_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct		s_params
{
    int             nb_args;
    size_t          number_of_philosopher;
    size_t          time_to_die;
    size_t          time_to_eat;
    size_t          time_to_sleep;
    size_t          number_of_time_each_philosophers_must_eat;
    struct timeval	*time_start;
}					t_params;

typedef struct		s_state
{
    char    name;

}					t_state;

#endif
