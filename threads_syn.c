/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_syn.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vodebunm <vodebunm@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 16:21:21 by vodebunm          #+#    #+#             */
/*   Updated: 2024/08/05 11:34:19 by vodebunm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

//Synchronise thread begining
void delay_threads(t_philo_arg *philo_av)
{
    while (!bool_retrieve(&philo_av->philo_av_mutex, &philo_av->synchronize_thread))
    {
        // Busy wait
    }
}
//time to implement, SECS; MILLISECS, MICROSEC
long get_timeofday(t_timeofday timeofday)
{
    struct timeval time_av;
    if (gettimeofday(&time_av, NULL))
    {
        handle_error("Gettimeofday failure");
    }
    if (timeofday == SECOND)
    {
        return (time_av.tv_sec + (time_av.tv_usec / 1e3));
    }
    else if (timeofday == MILLISECOND)
    {
        return ((time_av.tv_sec * 1e3) + (time_av.tv_usec / 1e3));
    }
    else if (timeofday == MICROSECOND)
    {
        return ((time_av.tv_sec * 1e6) + time_av.tv_usec);
    }
    else
    {
        handle_error("Gettime error");
    }
    return (1200); // Default return in case of error (shouldn't reach here)
}
//Implementation of accurate usleep function

void ft_usleep(long t, t_philo_arg *philo_av)
{
    long start = get_timeofday(MICROSECOND);
    long pass;
    long buf;

    while (get_timeofday(MICROSECOND) - start < t)
    {
        if (end_of_simulation(philo_av))
            break;

        pass = get_timeofday(MICROSECOND) - start;
        buf = t - pass;

        if (buf > 1000) // Sleep in smaller chunks to improve precision
        {
            usleep(buf / 2); // Sleep for half of the remaining time
        }
        else
        {
            while (get_timeofday(MICROSECOND) - start < t) // Spin-wait for the remaining time to avoid excessive CPU usage
            {
                struct timespec ts;
                ts.tv_sec = 0;
                ts.tv_nsec = buf * 1000; // Convert microseconds to nanoseconds
                nanosleep(&ts, NULL);
            }
        }
    }
}

//write status for philos_sleep in the dinner_simulation
void mutex_write(t_philo_action action, t_philosopher *philo_av, bool debug)
{
    long buf = get_timeofday(MILLISECOND) - philo_av->philo_arg->start_activity;

    if (philo_av->satisfy) // Skip if the philosopher is satisfied
        return;

    mutex_control(&philo_av->philo_arg->mutex_write_status, MUTEX_LOCK);

    if (debug)
    {
        mutex_write_debug(action, philo_av, buf);
    }
    else
    {
        if ((action == M_LEFT_FORK || action == M_RIGHT_FORK) && !end_of_simulation(philo_av->philo_arg))
            printf("%-6ld %d has taken a fork\n", buf, philo_av->id);
        else if (action == EATING && !end_of_simulation(philo_av->philo_arg))
            printf("%-6ld %d is eating\n", buf, philo_av->id);
        else if (action == SLEEPING && !end_of_simulation(philo_av->philo_arg))
            printf("%-6ld %d is sleeping\n", buf, philo_av->id);
        else if (action == THINKING && !end_of_simulation(philo_av->philo_arg))
            printf("%-6ld %d is thinking\n", buf, philo_av->id);
    }

    mutex_control(&philo_av->philo_arg->mutex_write_status, MUTEX_UNLOCK);
}
void mutex_write_debug(t_philo_action action, t_philosopher *philo_av, long buf)
{
    if (action == M_LEFT_FORK && !end_of_simulation(philo_av->philo_arg))
        printf("%-6ld %d has taken left fork (fid: %d)\n", buf, philo_av->id, philo_av->left_m_fork->fid);
    else if (action == M_RIGHT_FORK && !end_of_simulation(philo_av->philo_arg))
        printf("%-6ld %d has taken right fork (fid: %d)\n", buf, philo_av->id, philo_av->right_m_fork->fid);
    else if (action == EATING && !end_of_simulation(philo_av->philo_arg))
        printf("%-6ld %d is eating (food count: %ld)\n", buf, philo_av->id, philo_av->food_count);
    else if (action == SLEEPING && !end_of_simulation(philo_av->philo_arg))
        printf("%-6ld %d is sleeping\n", buf, philo_av->id);
    else if (action == THINKING && !end_of_simulation(philo_av->philo_arg))
        printf("%-6ld %d is thinking\n", buf, philo_av->id);
    else if (action == DEAD)
        printf("%-6ld %d philo is dead\n", buf, philo_av->id);
}
