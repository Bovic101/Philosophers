/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vodebunm <vodebunm@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 10:44:00 by vodebunm          #+#    #+#             */
/*   Updated: 2024/07/31 12:31:27 by vodebunm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	data_init(t_philo_arg *philo_av)
{
	int i;
	
	i = -1;
	philo_av->end_activity = false;
	philo_av->philosophers = malloc_control(sizeof(t_philosopher)* philo_av->num_philo);
	philo_av->m_forks = malloc_control(sizeof(t_fork)* philo_av->num_philo );
	while (++i < philo_av->num_philo)
	{
		mutex_control(&philo_av->m_forks[i],MUTEX_INIT);
		philo_av->m_forks[i].fid = i; 
	}
	
}
