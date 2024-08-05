/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vodebunm <vodebunm@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 09:27:56 by vodebunm          #+#    #+#             */
/*   Updated: 2024/08/05 11:33:44 by vodebunm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"
//./philo ,nbr philo,die, eat, sleep, no. of philo must eat(optional)
// ◦ timestamp_in_ms X has is eating > 60ms(assumed)
void reading_input(t_philo_arg *philo_av, char **argv)
{
    philo_av->num_philo = atol_custom(argv[1]);
    philo_av->time_2_die = convert_to_millisec(argv[2]);
    philo_av->time_2_eat = convert_to_millisec(argv[3]);
    philo_av->time_2_sleep = convert_to_millisec(argv[4]);

    if (philo_av->time_2_die < 60000 || philo_av->time_2_eat < 60000 || philo_av->time_2_sleep < 60000)
    {
        handle_error("Assumed timestamp value error");
    }

    if (argv[5])
    {
        philo_av->num_time_2_eat = atol_custom(argv[5]);
    }
    else
    {
        philo_av->num_time_2_eat = -1;
    }
}