/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_actions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeoithd <aeoithd@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 14:07:45 by aeoithd           #+#    #+#             */
/*   Updated: 2020/10/02 07:26:09 by aeoithd          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	ft_actions(t_philo *p)
{
	pthread_mutex_lock(&g_banquet.mutex[p->pos % 2 ? p->rfork : p->lfork]);
	print_log(p, HAS_TAKEN_A_FORK);
	usleep(1000);
	pthread_mutex_lock(&g_banquet.mutex[p->pos % 2 ? p->lfork : p->rfork]);
	print_log(p, HAS_TAKEN_A_FORK);
	pthread_mutex_lock(&p->eating);
	p->last_meal = get_time();
	p->death_time = p->last_meal + g_banquet.die;
	print_log(p, IS_EATING);
	p->meal_count += 1;
	ft_usleep(g_banquet.eat);
	pthread_mutex_unlock(&g_banquet.mutex[p->pos % 2 ? p->rfork : p->pos]);
	pthread_mutex_unlock(&g_banquet.mutex[p->pos % 2 ? p->pos : p->rfork]);
	pthread_mutex_unlock(&p->eating);
	pthread_mutex_unlock(&p->eat_counter);
	print_log(p, IS_SLEEPING);
	ft_usleep(g_banquet.sleep);
	print_log(p, IS_THINKING);
	usleep(100);
}
