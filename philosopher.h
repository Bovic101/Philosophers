/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vodebunm <vodebunm@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 22:00:51 by vodebunm          #+#    #+#             */
/*   Updated: 2024/08/06 00:39:12 by vodebunm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
#define PHILOSOPHER_H

#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdlib.h>
#include <sys/time.h>
#include <limits.h> // INT_MAX
#include <string.h>

// Structure(data)
typedef pthread_mutex_t t_mutex;

typedef struct s_fork
{
	t_mutex	fork;
	int		fid;//useful for debuggibg
}			t_fork;

typedef struct s_philosopher
{
	int 	id;
	pthread_t philo_id;//a philo is a thread ID
	t_fork	*left_m_fork;
	t_fork	*right_m_fork;
	long	food_count;
	bool 	satisfy;
	long 	last_food_time;
	
} t_philosopher;
//philo parameters 
typedef struct s_philo_arg
{
	long	num_philo;
	long 	time_2_die;
	long	time_2_eat;
	long	time_2_sleep;
	long	num_times_2_eat;// number of times each philo must eat
}		t_philo_arg

#endif
