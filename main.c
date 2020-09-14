/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 11:26:28 by thverney          #+#    #+#             */
/*   Updated: 2020/09/14 12:07:56 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int     ft_parse(char **av, t_params *p)
{

}

int main(int ac, char **av)
{
    if (ac != 5 || ac != 6)
        return (-1);
    t_params *p;

    if (!(p = malloc(sizeof(t_params))))
        return (-1);
    ft_parse(av, p);
}