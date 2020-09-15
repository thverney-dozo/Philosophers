/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 14:30:27 by thverney          #+#    #+#             */
/*   Updated: 2020/09/15 15:48:06 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	get_params(char **av, t_params *params)
{
	params->philos = ft_atoi(av[1]);
	params->die = ft_atoi(av[2]);
	params->eat = ft_atoi(av[3]);
	params->sleep = ft_atoi(av[4]);
	if (av[5])
		params->timetoeat = ft_atoi(av[5]);
	if (params->philos < 1 || params->eat < 1 || params->eat < 1
	|| params->sleep < 1 || params->timetoeat < 1)
		return (error_args(params, av));
	return (0);
}

void	*philo_fun(int i, t_params *params, pthread_mutex_t mutex)
{
	int timer;
	
	timer = 0;
	usleep(10000 * i);
	while (timer < params->die)
	{
		if (pthread_mutex_lock(&mutex) == 0)
		{
			// printf("Philo %d has taken a fork\n", i);
			usleep(params->eat);
			pthread_mutex_unlock(&mutex);
			// printf("Philo %d is sleeping\n", i);
			usleep(params->sleep);
			timer = 0;
			usleep(10000);
		}
		else
		{
			ft_putnbr_fd(i, 1);
			// write(1, "is thinking\n", 13);
			usleep(1000);
			timer += 1000;
		}
		usleep(10000);
	}	
	if (timer == i)
	{
		ft_putnbr_fd(i, 1);
		write(1, "died\n", 5);
	}
	return NULL;
}

void	main_func(t_params *params)
{
	static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	pthread_t thread[params->philos];
	size_t i;
	
	i = 1;
	while ((int)i <= params->philos + 1)
	{
		pthread_create(&thread[i], NULL, philo_fun(i, params, mutex), (void*)(i + 1));
		i++;
	}
	usleep(1000);
	pthread_mutex_unlock(&mutex);
	i = 1;
	while ((int)i <= params->philos +1)
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
		return (-1);
	main_func(&params);
	return (0);
}