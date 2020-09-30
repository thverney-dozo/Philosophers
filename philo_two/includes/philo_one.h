/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 19:48:10 by thverney          #+#    #+#             */
/*   Updated: 2020/09/30 19:48:12 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>

# define SUCCESS			0
# define FAIL				1
# define HAS_TAKEN_A_FORK	2
# define IS_EATING			3
# define IS_SLEEPING		4
# define IS_THINKING		5
# define HAS_LEFT_ITS_FORKS	6
# define MAX_EAT_REACHED	7
# define DIED				8

typedef struct				s_philo
{
	int						pos;
	int						meal_count;
	int						lfork;
	int						rfork;
	uint64_t				last_meal;
	uint64_t				death_time;
	pthread_mutex_t			eating;
	pthread_mutex_t			eat_counter;
}							t_philo;

typedef struct				s_banquet
{
	int						nb_philos;
	int						timetoeat;
	uint64_t				die;
	uint64_t				eat;
	uint64_t				sleep;
	uint64_t				start;
	t_philo					*philos;
	pthread_mutex_t			*mutex;
	pthread_mutex_t			death;
	pthread_mutex_t			stop_banquet;
	pthread_mutex_t			write;
	pthread_mutex_t			exit;
}							t_banquet;

t_banquet					g_banquet;

int							ft_clean(void);
int							ft_atoi(const char *nptr);
void						ft_putnbr_fd(int n, int fd);
void						print_log(t_philo *philo, const int status);
uint64_t					get_time(void);
void						ft_actions(t_philo *p);
int							is_available(t_philo *p, int i);
void						ft_usleep(unsigned int n);
void						*handle_death(void *philo);
void						*handle_timetoeat(void *philo);

#endif
