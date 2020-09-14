#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>


static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

typedef struct	s_params
{
	int		philos;
	int		die;
	int		eat;
	int		sleep;
	int		timetoeat;
}				t_params;



int     ft_atoi(const char *nptr);
void	ft_putnbr_fd(int n, int fd);

#endif