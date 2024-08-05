/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vodebunm <vodebunm@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 13:45:16 by vodebunm          #+#    #+#             */
/*   Updated: 2024/08/05 11:33:09 by vodebunm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	bool_assign(t_mutex *mutex, bool *s, bool value)
{
	mutex_control(mutex, MUTEX_LOCK);
	*s = value;
	mutex_control(mutex, MUTEX_UNLOCK);
}
bool	bool_retrieve(t_mutex *mutex, bool *value)
{
	bool	result;
	mutex_control(mutex, MUTEX_LOCK);
	result = *value;
	mutex_control(mutex, MUTEX_UNLOCK);
	return(result);
}
void	long_assign(t_mutex *mutex, long *s, long value)
{
	mutex_control(mutex, MUTEX_LOCK);
	*s = value;
	mutex_control(mutex, MUTEX_UNLOCK);
}
bool	long_retrieve(t_mutex *mutex, long *value)
{
	long	result;
	mutex_control(mutex, MUTEX_LOCK);
	result = *value;
	mutex_control(mutex, MUTEX_UNLOCK);
	return(result);
}
bool	end_of_simulation(t_philo_arg *philo_av)
{
	return( bool_retrieve(&philo_av->philo_av_mutex, &philo_av->end_activity));//Additional but not useful
}
