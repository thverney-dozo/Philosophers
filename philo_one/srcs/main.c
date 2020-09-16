/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaefourn <gaefourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 15:34:47 by gaefourn          #+#    #+#             */
/*   Updated: 2020/09/16 16:09:00 by gaefourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	get_params(char **av, t_params *params)
{
	int i;
	
	i = -1;
	params->philos = -5;
	params->die = -5;
	params->eat = -5;
	params->sleep = -5;
	params->timetoeat = -5;
	params->process = 1;
	params->alive = 0;
	params->philos = ft_atoi(av[1]);
	params->die = ft_atoi(av[2]);
	params->eat = ft_atoi(av[3]);
	params->sleep = ft_atoi(av[4]);
	params->forks = malloc(sizeof(char) * params->philos + 1);
	while (++i < params->philos)
		params->forks[i] = 'A';
	params->forks[i] = '\0';
	if (av[5])
		params->timetoeat = ft_atoi(av[5]);
	if (params->philos == 0 || params->eat == 0 || params->eat == 0 ||
		params->sleep == 0 || params->timetoeat == 0)
		return (-1);
	params->mutex = malloc(sizeof(pthread_mutex_t) * params->philos);
	return (0);
}

void	*philo_fun(void *arg)
{
	t_params	*params;
	int 		timer;
	int 		i;
	int 		j;
	int			k;
	int			l;
	int			check;

	params = (t_params*)arg;
	i = params->process;
	timer = 0;
	j = 0;
	k = 0;
	l = 0;
	check = -1;
	usleep(1000);
	while (timer <= params->die)
	{
		check++;
		if (params->alive == 10)
			return (NULL);
		if (params->forks[i] == 'A' && k == 0)
		{
			if ((i + 1) != params->philos && params->forks[i + 1] == 'A')
			{
				params->forks[i + 1] = 'F';
				pthread_mutex_lock(&params->mutex[i + 1]);
				l++;
			}
			else
			{
				if (params->forks[0] == 'A')
				{
					params->forks[0] = 'F';
					pthread_mutex_lock(&params->mutex[0]);
					l++;
				}
			}
			params->forks[i] = 'F';
			pthread_mutex_lock(&params->mutex[i]);
			l++;
		}
		if (l == 2)
		{
			printf("[%d] Philo %d has taken a fork\n", check, i);
			printf("[%d] Philo %d has taken a fork\n", check, i);
			printf("[%d] Philo %d is eating\n", check, i);
			usleep(params->eat);
			params->forks[i] = 'A';
			pthread_mutex_unlock(&params->mutex[i]);
			if ((i + 1) != params->philos)
			{
				params->forks[i + 1] = 'A';
				pthread_mutex_unlock(&params->mutex[i + 1]);
			}
			else
			{
				params->forks[0] = 'A';
				pthread_mutex_unlock(&params->mutex[0]);
			}
			timer = 0;
			printf("[%d] Philo %d is sleeping\n", check, i);
			usleep(params->sleep);
			timer = timer + params->sleep;
			j++;
			if (params->timetoeat != -5)
				if (j == params->timetoeat)
				{
					printf("[%d] Philo %d ate time_to_eat times\n", check, i);
					exit(0);
				}
			k++;
			l = 0;
		}
		else
		{
			params->forks[i] = 'A';
			pthread_mutex_unlock(&params->mutex[i]);
			if ((i + 1) != params->philos)
			{
				params->forks[i + 1] = 'A';
				pthread_mutex_unlock(&params->mutex[i + 1]);
			}
			else
			{
				params->forks[0] = 'A';
				pthread_mutex_unlock(&params->mutex[0]);
			}
			printf("[%d] Philo %d is thinking\n", check, i);
			usleep(params->eat);
			timer = timer + params->eat;
			k = 0;
			l = 0;
		}
		usleep(1000);
	}	
	printf("[%d] Philo %d died\n", check, i);
	params->alive = 10;
	exit(0);
	return NULL;
}

void	main_func(t_params *params)
{
	pthread_t thread[params->philos];
	int i;
	
	i = 0;
	while (i < params->philos)
	{
		pthread_mutex_init(&params->mutex[i], NULL);
		i++;
	}
	i = 0;
	while (i < params->philos)
	{
		pthread_create(&thread[i], NULL, philo_fun, (void*)(params));
		usleep(100);
		params->process++;
		i++;
	}
	usleep(1000);
	i = 0;
	while (i < params->philos)
	{
		pthread_join(thread[i], NULL);
		i++;
	}
	
}
int	main(int ac, char **av)
{
	t_params params;
	
	if (ac < 5 || ac > 6)
	{
		write(2, "No args.\n", 9);
		return (-1);
	}
	if (get_params(av, &params) == -1)
	{
		write(2, "At least one argument is invalid.\n", 35);
		return (-1);
	}
	main_func(&params);
	return (0);
}