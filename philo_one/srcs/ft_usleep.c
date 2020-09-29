/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeoithd <aeoithd@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 04:34:58 by aeoithd           #+#    #+#             */
/*   Updated: 2020/09/29 04:38:22 by aeoithd          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void		ft_usleep(unsigned int n)
{
	uint64_t	start_time;

	start_time = get_time();
	while (1)
	{
		if (get_time() - start_time >= n)
			break ;
		usleep(50);
	}
}