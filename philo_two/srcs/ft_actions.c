/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_actions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeoithd <aeoithd@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 14:07:45 by aeoithd           #+#    #+#             */
/*   Updated: 2020/10/02 07:44:57 by aeoithd          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void	ft_actions(t_philo *p)
{
	sem_wait(g_banquet.ask_forks);
	sem_wait(g_banquet.forks);
	print_log(p, HAS_TAKEN_A_FORK);
	sem_wait(g_banquet.forks);
	print_log(p, HAS_TAKEN_A_FORK);
	sem_post(g_banquet.ask_forks);
	sem_wait(p->eating);
	p->last_meal = get_time();
	p->death_time = p->last_meal + g_banquet.die;
	print_log(p, IS_EATING);
	p->meal_count += 1;
	ft_usleep(g_banquet.eat);
	sem_post(p->eating);
	sem_post(p->eat_count);
	print_log(p, IS_SLEEPING);
	sem_post(g_banquet.forks);
	sem_post(g_banquet.forks);
	ft_usleep(g_banquet.sleep);
	print_log(p, IS_THINKING);
	usleep(100);
}
