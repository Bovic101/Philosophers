/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vodebunm <vodebunm@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 11:09:45 by vodebunm          #+#    #+#             */
/*   Updated: 2024/08/05 11:34:06 by vodebunm         ###   ########.fr       */
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
void *dinner_simulation(void *argv)
{
    if (argv == NULL)
    {
        handle_error("Null argument passed to dinner_simulation");
    }

    t_philosopher *philo_av = (t_philosopher *)argv;

    // Delay threads to start simultaneously
    delay_threads(philo_av->philo_arg);

    // Simulation loop
    while (!end_of_simulation(philo_av->philo_arg))
    {
        if (philo_av->satisfy) // Check if the philosopher is full
        {
            break;
        }

        // Eating phase
        philo_eat(philo_av);

        // Sleeping phase
        mutex_write(SLEEPING, philo_av, DEBUG_MODE);
        ft_usleep(philo_av->philo_arg->time_2_sleep, philo_av->philo_arg);

        // Thinking phase
        philo_thinking(philo_av);
    }

    return NULL;
}
void philo_eat(t_philosopher *philo_av)
{
    if (philo_av->left_m_fork == NULL || philo_av->right_m_fork == NULL)
    {
        handle_error("Fork pointers are null in philo_eat");
    }

    // Lock the left fork
    mutex_control(&philo_av->left_m_fork->fork, MUTEX_LOCK);
    mutex_write(M_LEFT_FORK, philo_av, DEBUG_MODE);

    // Lock the right fork
    mutex_control(&philo_av->right_m_fork->fork, MUTEX_LOCK);
    mutex_write(M_RIGHT_FORK, philo_av, DEBUG_MODE);

    // Record the last time the philosopher ate
    long_assign(&philo_av->philo_mutex, &philo_av->last_food_time, get_timeofday(MILLISECOND));

    // Increase the food count
    philo_av->food_count++;
    mutex_write(EATING, philo_av, DEBUG_MODE);

    // Simulate eating duration
    ft_usleep(philo_av->philo_arg->time_2_eat, philo_av->philo_arg);

    // Check if the philosopher is satisfied
    if (philo_av->philo_arg->num_time_2_eat > 0 && philo_av->food_count == philo_av->philo_arg->num_time_2_eat)
    {
        bool_assign(&philo_av->philo_mutex, &philo_av->satisfy, true);
    }

    // Unlock the forks
    mutex_control(&philo_av->left_m_fork->fork, MUTEX_UNLOCK);
    mutex_control(&philo_av->right_m_fork->fork, MUTEX_UNLOCK);
}
void philo_thinking(t_philosopher *philo_av)
{
    mutex_write(THINKING, philo_av, DEBUG_MODE);
}