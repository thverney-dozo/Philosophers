#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>


typedef struct	s_params
{
	int				philos;
	int				die;
	int				eat;
	int				sleep;
	int				timetoeat;
	int				process;
	int				alive;
	char			*forks;
	pthread_mutex_t *mutex;
}				t_params;



int     ft_atoi(const char *nptr);
void	ft_putnbr_fd(int n, int fd);

#endif