/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaefourn <gaefourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 15:34:47 by gaefourn          #+#    #+#             */
/*   Updated: 2020/09/16 12:10:57 by gaefourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	get_params(char **av, t_params *params)
{
	params->philos = -5;
	params->die = -5;
	params->eat = -5;
	params->sleep = -5;
	params->timetoeat = -5;
	params->process = 1;
	params->philos = ft_atoi(av[1]);
	params->die = ft_atoi(av[2]);
	params->eat = ft_atoi(av[3]);
	params->sleep = ft_atoi(av[4]);
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
	t_params *params;
	int timer;
	int i;
	
	params = (t_params*)arg;
	i = params->process;
	timer = 0;
	while (timer < params->die)
	{
		if (timer >= params->die / 3)
		{
			pthread_mutex_lock(&params->mutex[i]);
			printf("Philo %d has taken a fork\n", i);
			if ((i + 1) != params->philos)
				pthread_mutex_lock(&params->mutex[i + 1]);
			else
				pthread_mutex_lock(&params->mutex[0]);
			printf("Philo %d has taken a fork\n", i);
			printf("Philo %d has is eating\n", i);
			usleep(params->eat);
			pthread_mutex_unlock(&params->mutex[i]);
			if ((i + 1) != params->philos)
				pthread_mutex_unlock(&params->mutex[i + 1]);
			else
				pthread_mutex_unlock(&params->mutex[0]);
			printf("Philo %d is sleeping\n", i);
			usleep(params->sleep);
			timer = 0;
		}
		else
		{
			printf("Philo %d is thinking\n", i);
			usleep(params->die/5);
			timer += params->die/5;
		}
		usleep(10000);
		printf("\n\nTIMER PHILO [%d] = = = = = = [%d]\n\n", i, timer);
	}	
	if (timer == i)
	{
		ft_putnbr_fd(i, 1);
		write(1, "died\n", 5);
		exit(0);
	}
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
		usleep(1000);
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