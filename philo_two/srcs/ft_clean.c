/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeoithd <aeoithd@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 15:18:27 by aeoithd           #+#    #+#             */
/*   Updated: 2020/10/02 08:56:02 by aeoithd          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void			get_name(char *name, int pos, int eat)
{
	int			i;
	const char	prefix[7] = "/philo-";
	const char	prefix_eat[11] = "/philo-eat-";

	i = -1;
	if (eat)
		while (++i < 11)
			name[i] = prefix_eat[i];
	else
		while (++i < 7)
			name[i] = prefix[i];
	while (pos)
	{
		name[i++] = (pos % 10) + '0';
		pos /= 10;
	}
	name[i] = '\0';
}

int				ft_clean(void)
{
	int			i;
	char		name[50];

	i = 0;
	sem_unlink(ASKFORKS);
	sem_unlink(FORKS);
	sem_unlink(WRITE);
	sem_unlink(DEATH);
	if (g_banquet.philos)
		while (i < g_banquet.nb_philos)
		{
			get_name(name, i + 1, 0);
			sem_unlink(name);
			get_name(name, i + 1, 1);
			sem_unlink(name);
			i++;
		}
	free(g_banquet.philos);
	g_banquet.philos = NULL;
	return (0);
}
