/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vodebunm <vodebunm@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 12:58:12 by vodebunm          #+#    #+#             */
/*   Updated: 2024/08/11 05:24:10 by vodebunm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"
//check between last-to eat, act a monitor
void	*check_dinner(void *argv)
{
	int i;
	t_philo_arg *philo_av;
	philo_av = (t_philo_arg *)argv;
	//ensure all threads are running & spinlock until all threads are active
	while (!threads_active(&philo_av->philo_av_mutex, &philo_av->threads_run_num, philo_av->num_philo))
		;
	//regurlary checking time-2_die
	while (!end_of_simulation(philo_av))
	{
		i = -1;
		while (++i < philo_av->num_philo && !end_of_simulation(philo_av))
		{
			if (philo_dead(philo_av->philosophers + i))//To do
			{
				bool_assign(&philo_av->philo_av_mutex, &philo_av->end_activity, true);
				mutex_write(DEAD, philo_av->philosophers + i, DEBUG_MODE);
			}
		}
		
	}
	
	return(NULL);
}
//review if all threads are running
bool threads_active(t_mutex *mutex, long *threads, long philo_num)
{
	bool result;
	
	result = false;
	mutex_control(mutex, MUTEX_LOCK);
	if (*threads == philo_num)
	{
		result == true;
	}
	mutex_control(mutex, MUTEX_UNLOCK);
	return(result);
	
}
//increase threads active to synchro with the checker
void	long_increments( t_mutex *mutex, long *value)
{
	mutex_control(mutex, MUTEX_LOCK);
	(*value)++;
	mutex_control(mutex, MUTEX_UNLOCK);
}

bool	philo_dead(t_philosopher *philo_av)
{
	long	buf;
	long	time_die;
	if (bool_retrieve(&philo_av->philo_mutex, &philo_av->satisfy))//check for error
	{
		return(false);
	}
	buf = get_timeofday(MILLISECOND) - long_retrieve(&philo_av->philo_mutex, &philo_av->last_food_time);
	time_die = philo_av->philo_arg->time_2_die / 1e3;
	if (buf > time_die)
	{
		return(true);
	}
	return(false);
}
void	*long_thread(void *argv)
{
	t_philosopher *philo_av;
	philo_av = (t_philosopher *)argv;
	delay_threads(philo_av->philo_arg);
	long_assign(&philo_av->philo_mutex, &philo_av->last_food_time, get_timeofday(MILLISECOND));
	long_increments(&philo_av->philo_arg->philo_av_mutex, &philo_av->philo_arg->threads_run_num);
	while (!end_of_simulation(philo_av->philo_arg))
	{
		usleep(150);//check if it works
	}
	return(NULL);
}
//function to make a sytem respond in a reasonable way
void	disengage_threads(t_philosopher *philos)
{
	if (philos->philo_arg->num_philo % 2 == 0)
	{
		if (philos->id % 2 == 0)
		{
			ft_usleep(3e4, philos->philo_arg);
		}
	}
	else
	{
		if (philos->id % 2)//system is heating
		{
			philo_thinking(philos,true);
		}
	}
}
