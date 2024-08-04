/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vodebunm <vodebunm@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 11:09:45 by vodebunm          #+#    #+#             */
/*   Updated: 2024/08/04 16:48:58 by vodebunm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"
// ./philo 5 800 300 300 [5]-number of times to eat
//if no meal, return 0
//
void	start_simulation(t_philo_arg *philo_av)
{
	int	i;
	
	i = -1;
	if (philo_av->num_time_2_eat == 0)
	{
		return;//To do using the clean function
	}
	else if (philo_av->num_philo == 1)
	{
		/* code  to do*/
	}
	else
	{
		while (++i < philo_av->num_philo)
		{
			thread_control(&philo_av->philosophers[i].philo_id,dinner_simulation,&philo_av->philosophers[i],MUTEX_CREATE);
		}
		
	}
	//start simulation
	philo_av->start_activity = get_timeofday(MILLISECOND);
	//synchronise all threads
	bool_assign(&philo_av->philo_av_mutex, &philo_av->synchronize_thread,true);
	//Thread Join
	i = -1;
	while (++i < philo_av->num_philo)
		thread_control(&philo_av->philosophers[i].philo_id,NULL, NULL, MUTEX_JOIN); //Philos satifised at this level
	
}
void	*dinner_simulation(void *argv)
{
	t_philosopher *philo_av;
	philo_av = (t_philosopher *)argv;
	//lock
	delay_threads(philo_av->philo_arg);//posible error
	//last_food_time
	while (!end_of_simulation(philo_av->philo_arg))
	{
		if (philo_av->satisfy) //condition to check if philo is full--To DO
		{
			break;
		}
		//to eat
		philo_eat(philo_av);
		//sleep
		
		//think
		philo_thinking(philo_av);
	}
	
	return(NULL);
}