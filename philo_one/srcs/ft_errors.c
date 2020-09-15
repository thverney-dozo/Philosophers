/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 14:37:46 by thverney          #+#    #+#             */
/*   Updated: 2020/09/15 15:48:47 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int     error_args(t_params *params, char **av)
{
    write(1, "\033[0;31mInvalid arg(s)\033[0m\n", 27);
    if (params->philos < 1)
        write(1, "Number_of_philosopher must be a nb > than 0 change: ", 53);
    if (params->philos < 1)
        ft_putstr_fd(av[1], 1);
    if (params->die < 1)
        write(1, "Time_to_die must be a nb > than 0 change: ", 43);
    if (params->die < 1)
        ft_putstr_fd(av[2], 1);
    if (params->eat < 1)
        write(1, "Time_to_eat must be a nb > than 0 change: ", 43);
    if (params->eat < 1)
        ft_putstr_fd(av[3], 1);
    if (params->sleep < 1)
        write(1, "Time_to_sleep must be a nb > than 0 change: ", 45);
    if (params->sleep < 1)
        ft_putstr_fd(av[4], 1);
    if (av[5] && params->timetoeat < 1)
        write(1, "Nb_of_time_each_philos_must_eat nb > 0 change: ", 48);
    if (av[5] && params->timetoeat < 1)
        ft_putstr_fd(av[5], 1);
    return (-1);
}
