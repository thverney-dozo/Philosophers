/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeoithd <aeoithd@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 15:34:47 by thverney          #+#    #+#             */
/*   Updated: 2020/10/02 04:29:35 by aeoithd          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int				get_params(char **av)
{
	g_banquet.nb_philos = ft_atoi(av[1]);
	g_banquet.die = ft_atoi(av[2]);
	g_banquet.eat = ft_atoi(av[3]);
	g_banquet.sleep = ft_atoi(av[4]);
	g_banquet.timetoeat = (av[5] ? ft_atoi(av[5]) : 0);
	if ((g_banquet.nb_philos <= 0 || g_banquet.eat <= 0 || g_banquet.eat <= 0
	|| g_banquet.sleep <= 0 || g_banquet.timetoeat < 0))
		return (FAIL);
	return (SUCCESS);
}

void			*philo_fun(void *philo)
{
	t_philo		*p;
	pthread_t	death;

	p = (t_philo*)philo;
	g_banquet.start = get_time();
	p->last_meal = g_banquet.start;
	p->death_time = p->last_meal + g_banquet.die;
	if (pthread_create(&death, NULL, &handle_death, p))
		return ((void *)FAIL);
	pthread_detach(death);
	while (1)
		ft_actions(p);
	return ((void *)SUCCESS);
}

int				init2(void)
{
	pthread_t	thread;
	int			i;

	pthread_mutex_init(&g_banquet.write, NULL);
	pthread_mutex_init(&g_banquet.stop_banquet, NULL);
	pthread_mutex_lock(&g_banquet.stop_banquet);
	if (g_banquet.timetoeat)
	{
		if (pthread_create(&thread, NULL, &handle_timetoeat, NULL))
			return (FAIL);
		pthread_detach(thread);
	}
	i = 0;
	while (i < g_banquet.nb_philos)
	{
		pthread_create(&thread, NULL, &philo_fun,
		(void*)(&g_banquet.philos[i++]));
		pthread_detach(thread);
		usleep(100);
	}
	return (SUCCESS);
}

int				init(void)
{
	int			i;

	i = -1;
	g_banquet.philos = NULL;
	if (!(g_banquet.philos = malloc(sizeof(t_philo) * g_banquet.nb_philos)))
		return (FAIL);
	g_banquet.mutex = NULL;
	if (!(g_banquet.mutex = malloc(sizeof(pthread_mutex_t)
	* g_banquet.nb_philos)))
		return (FAIL);
	while (++i < g_banquet.nb_philos)
	{
		g_banquet.philos[i].pos = i;
		g_banquet.philos[i].meal_count = 0;
		g_banquet.philos[i].last_meal = 0;
		pthread_mutex_init(&g_banquet.mutex[i], NULL);
		pthread_mutex_init(&g_banquet.philos[i].eating, NULL);
		pthread_mutex_init(&g_banquet.philos[i].eat_counter, NULL);
		pthread_mutex_lock(&g_banquet.philos[i].eat_counter);
		g_banquet.philos[i].lfork = i;
		g_banquet.philos[i].rfork = (i + 1 != g_banquet.nb_philos) ? i + 1 : 0;
	}
	return (init2());
}

int				main(int ac, char **av)
{
	if (ac < 5 || ac > 6)
	{
		write(2, "No args.\n", 9);
		return (-1);
	}
	memset(&g_banquet, 0, sizeof(g_banquet));
	if (get_params(av))
	{
		write(2, "At least one argument is invalid.\n", 35);
		return (FAIL);
	}
	if (init())
		return (FAIL);
	pthread_mutex_lock(&g_banquet.stop_banquet);
	pthread_mutex_unlock(&g_banquet.stop_banquet);
	ft_clean();
	return (SUCCESS);
}
