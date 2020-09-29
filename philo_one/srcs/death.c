/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeoithd <aeoithd@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 04:00:53 by aeoithd           #+#    #+#             */
/*   Updated: 2020/09/29 14:22:59 by aeoithd          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

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
			pthread_mutex_lock(&g_banquet.philos[i++].eat_counter);
		nb_times_philos_have_eaten++;
	}
	print_log(NULL, MAX_EAT_REACHED);
	pthread_mutex_unlock(&g_banquet.stop_banquet);
	return (0);
}

void			*handle_death(void *philo)
{
	t_philo		*p;

	p = (t_philo*)philo;
	while (1)
	{
		usleep(1000);
		pthread_mutex_lock(&p->eating);
		if (p->death_time < get_time())
		{
			print_log(p, DIED);
			pthread_mutex_unlock(&p->eating);
			pthread_mutex_unlock(&g_banquet.stop_banquet);
			return (0);
		}
		pthread_mutex_unlock(&p->eating);
	}
}
