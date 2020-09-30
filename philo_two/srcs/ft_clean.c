/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeoithd <aeoithd@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 15:18:27 by aeoithd           #+#    #+#             */
/*   Updated: 2020/09/29 15:26:45 by aeoithd          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int		ft_clean(void)
{
	int i;

	i = 0;
	if (g_banquet.philos)
		while (i < g_banquet.nb_philos)
		{
			pthread_mutex_destroy(&g_banquet.philos[i].eating);
			pthread_mutex_destroy(&g_banquet.philos[i++].eat_counter);
		}
	free(g_banquet.philos);
	i = 0;
	if (g_banquet.mutex)
		while (i < g_banquet.nb_philos)
			pthread_mutex_destroy(&g_banquet.mutex[i++]);
	free(g_banquet.mutex);
	g_banquet.philos = NULL;
	pthread_mutex_destroy(&g_banquet.stop_banquet);
	pthread_mutex_destroy(&g_banquet.write);
	return (0);
}
