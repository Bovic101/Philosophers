/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vodebunm <vodebunm@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 10:44:00 by vodebunm          #+#    #+#             */
/*   Updated: 2024/08/05 11:32:02 by vodebunm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void data_init(t_philo_arg *philo_av)
{
    int i = -1;

    philo_av->end_activity = false;
    philo_av->synchronize_thread = false;

    // Allocate memory for philosophers
    philo_av->philosophers = malloc_control(sizeof(t_philosopher) * philo_av->num_philo);
    if (philo_av->philosophers == NULL)
    {
        handle_error("Failed to allocate memory for philosophers");
    }

    // Initialize the mutex for philo_av_mutex
    mutex_control(&philo_av->philo_av_mutex, MUTEX_INIT);

    // Initialize the mutex for writing status
    mutex_control(&philo_av->mutex_write_status, MUTEX_INIT);

    // Allocate memory for forks
    philo_av->m_forks = malloc_control(sizeof(t_fork) * philo_av->num_philo);
    if (philo_av->m_forks == NULL)
    {
        free(philo_av->philosophers);
        handle_error("Failed to allocate memory for forks");
    }

    // Initialize each fork's mutex and set their IDs
    while (++i < philo_av->num_philo)
    {
        mutex_control(&philo_av->m_forks[i].fork, MUTEX_INIT);
        philo_av->m_forks[i].fid = i;
    }

    // Initialize philosophers with their respective arguments
    philosopher_init(philo_av);
}


void philosopher_init(t_philo_arg *philo_av)
{
    int i = -1;
    t_philosopher *p;

    while (++i < philo_av->num_philo)
    {
        p = &philo_av->philosophers[i];
        p->id = i + 1;
        p->satisfy = false;
        p->food_count = 0;
        p->philo_arg = philo_av;
        mutex_control(&p->philo_mutex, MUTEX_INIT); // Initialize mutex for each philosopher

        m_fork_alloc(p, philo_av->m_forks, i);
    }
}

void m_fork_alloc(t_philosopher *philo_av, t_fork *forks, int philosopher_pos)
{
    int philo_num = philo_av->philo_arg->num_philo;

    // Default fork allocation
    philo_av->left_m_fork = &forks[(philosopher_pos + 1) % philo_num];
    philo_av->right_m_fork = &forks[philosopher_pos];

    // Reassign forks for odd philosopher IDs to prevent deadlock
    if (philo_av->id % 2 != 0)
    {
        philo_av->left_m_fork = &forks[philosopher_pos];
        philo_av->right_m_fork = &forks[(philosopher_pos + 1) % philo_num];
    }
}

