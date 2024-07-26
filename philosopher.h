/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vodebunm <vodebunm@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 22:00:51 by vodebunm          #+#    #+#             */
/*   Updated: 2024/07/27 00:13:30 by vodebunm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
#define PHILOSOPHER_H

#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>
#include <limits.h> /
#include <string.h>
#include <stdbool.h>

// Structure definitions
typedef pthread_mutex_t t_mutex;

// Forward declaration of the structure
typedef struct s_philo_arg t_philo_arg;

typedef struct s_fork
{
    t_mutex fork;
    int fid; // useful for debugging
} t_fork;

typedef struct s_philosopher
{
    int id;
    pthread_t philo_id; // a philosopher is a thread ID
    t_fork *left_m_fork;
    t_fork *right_m_fork;
    long food_count;
    bool satisfy;
    long last_food_time;
    t_philo_arg *philo_arg;
} t_philosopher;

// Parameters for philosophers
struct s_philo_arg
{
    long num_philo;
    long time_2_die;
    long time_2_eat;
    long time_2_sleep;
    long num_time_2_eat; // number of times each philosopher must eat
    long start_activity;
    long end_activity; // philosopher is full or dies
    t_fork *m_forks; // array of forks
    t_philosopher *philosophers; // array of philosophers
};

#endif // PHILOSOPHER_H
