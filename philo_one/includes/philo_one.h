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
void	ft_putstr_fd(char *s, int fd);
int		get_params(char **av, t_params *params);
void	*philo_fun(int i, t_params *params, pthread_mutex_t mutex);
void	main_func(t_params *params);
int     error_args(t_params *params, char **av);

#endif