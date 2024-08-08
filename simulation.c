/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vodebunm <vodebunm@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 11:09:45 by vodebunm          #+#    #+#             */
/*   Updated: 2024/08/08 07:06:07 by vodebunm         ###   ########.fr       */
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
		thread_control(&philo_av->philosophers[0].philo_id,long_thread, &philo_av->philosophers[0], MUTEX_CREATE);
	}
	else
	{
		while (++i < philo_av->num_philo)
		{
			thread_control(&philo_av->philosophers[i].philo_id,dinner_simulation,&philo_av->philosophers[i],MUTEX_CREATE);
		}
		
	}
	//thread survey
	thread_control(&philo_av->monitor, check_dinner,philo_av, MUTEX_CREATE); //to do
	//start simulation
	philo_av->start_activity = get_timeofday(MILLISECOND);
	//synchronise all threads
	bool_assign(&philo_av->philo_av_mutex, &philo_av->synchronize_thread,true);
	//Thread Join
	i = -1;
	while (++i < philo_av->num_philo)
		thread_control(&philo_av->philosophers[i].philo_id,NULL, NULL, MUTEX_JOIN); //Philos satifised at this level
	//All philo are full
	bool_assign(&philo_av->philo_av_mutex, &philo_av->end_activity,true);
	thread_control(&philo_av->monitor, NULL, NULL, MUTEX_JOIN);
	
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
	//setting last food time
	long_assign(&philo_av->philo_mutex, &philo_av->last_food_time, get_timeofday(MILLISECOND));
	
	//synchro wit checker/monitor
	long_increments(&philo_av->philo_arg->philo_av_mutex, &philo_av->philo_arg->threads_run_num);
	disengage_threads(philo_av);

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
        ft_usleep(philo_av->philo_arg->time_2_eat, philo_av->philo_arg);

        // Thinking phase
        philo_thinking(philo_av,false);
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
void philo_thinking(t_philosopher *philo_av, bool value)
{
	long	time_eat;
	long	time_think;
	long	time_sleep;
	if (!value)
	{
		 mutex_write(THINKING, philo_av, DEBUG_MODE);
	}
	
	if (philo_av->philo_arg->num_philo % 2 == 0)
	{
		return ;
	}
	//if ODD assigned is not fair
	time_eat = philo_av->philo_arg->time_2_eat;
	time_sleep =philo_av->philo_arg->time_2_sleep;
	time_think = time_eat * 2 - time_sleep;
	if (time_think < 0)
	{
		time_think = 0;
	}
	//forceful implementation on the thread
	ft_usleep(time_think * 0.30, philo_av->philo_arg);
}
