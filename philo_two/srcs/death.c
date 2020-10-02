/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeoithd <aeoithd@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 04:00:53 by aeoithd           #+#    #+#             */
/*   Updated: 2020/10/02 07:52:38 by aeoithd          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void			*handle_timetoeat(void *philo)
{
	int			nb_times_philos_have_eaten;
	int			i;

	(void)philo;
	nb_times_philos_have_eaten = 0;
	while (nb_times_philos_have_eaten < g_banquet.timetoeat)
	{
		i = 0;
		while (i < g_banquet.nb_philos)
			sem_wait(g_banquet.philos[i++].eat_count);
		nb_times_philos_have_eaten++;
	}
	print_log(NULL, MAX_EAT_REACHED);
	sem_post(g_banquet.stop_banquet);
	return (0);
}

void			*handle_death(void *philo)
{
	t_philo		*p;

	p = (t_philo*)philo;
	while (1)
	{
		usleep(1000);
		if (sem_wait(p->eating))
			return ((void *)FAIL);
		if (p->death_time < get_time())
		{
			print_log(p, DIED);
			if (sem_post(p->eating))
				return ((void *)FAIL);
			if (sem_post(g_banquet.stop_banquet))
				return ((void *)FAIL);
			return (SUCCESS);
		}
		if (sem_post(p->eating))
			return ((void *)FAIL);
	}
	return ((void *)SUCCESS);
}
