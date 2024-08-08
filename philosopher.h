/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vodebunm <vodebunm@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 22:00:51 by vodebunm          #+#    #+#             */
/*   Updated: 2024/08/08 07:01:12 by vodebunm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
#define PHILOSOPHER_H

#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>
#include <limits.h> 
#include <string.h>
#include <errno.h>
#include <stdbool.h>

#define DEBUG_MODE 0

// Structure definition
typedef pthread_mutex_t t_mutex;

// Forward declaration of the structure
typedef struct s_philo_arg t_philo_arg;

typedef enum mutexfunc 
{
    MUTEX_DETACH,
    MUTEX_UNLOCK,
    MUTEX_LOCK,
    MUTEX_INIT,
    MUTEX_CREATE,
    MUTEX_JOIN,
    MUTEX_DESTROY,
}       t_mutexfunc;


typedef enum e_philo_action 
{
    EATING,
    SLEEPING,
    THINKING,
    M_RIGHT_FORK,
    M_LEFT_FORK,
    DEAD,
}    t_philo_action;

typedef enum e_timeofday
{
    SECOND,
    MILLISECOND,
    MICROSECOND,
}       t_timeofday;


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
    t_mutex philo_mutex;//control data races with screen
    t_philo_arg *philo_arg;
} t_philosopher;

// Parameters for philosophers
struct s_philo_arg
{
    long num_philo;
    long time_2_die;
    long time_2_eat;
    long time_2_sleep;
    long num_time_2_eat; // number of times each philosopher must eat Flag if -1
    long start_activity;
    long threads_run_num;
    bool end_activity; // philosopher is full or dies
    pthread_mutex_t philo_av_mutex;//data races avoidance
    t_fork *m_forks; // array of forks
    t_philosopher *philosophers; // array of philosophers
    t_mutex mutex_write_status;
    pthread_t   monitor;
    bool synchronize_thread;

};
void	*malloc_control(size_t type);
void	reading_input(t_philo_arg *philo_av, char **argv);
void    handle_error(const char *str);
const char	*acceptable_input(const char *str);
long convert_to_millisec(const char *time_str);
void	mutex_control(t_mutex *mutex, t_mutexfunc mutexfunc);
void	thread_control(pthread_t *thread, void *(*start)(void *), void *arg, t_mutexfunc mutexfunc);
void	philosopher_init(t_philo_arg *philo_av);
void    m_fork_alloc(t_philosopher *philo_av, t_fork *forks, int philosopher_pos);
void	data_init(t_philo_arg *philo_av);
void	*dinner_simulation(void *argv);
void	bool_assign(t_mutex *mutex, bool *s, bool value);
bool	bool_retrieve(t_mutex *mutex, bool *value);
void	long_assign(t_mutex *mutex, long *s, long value);
bool	long_retrieve(t_mutex *mutex, long *value);
bool	end_of_simulation(t_philo_arg *philo_av);
void	delay_threads(t_philo_arg *philo_av);
long	get_timeofday(t_timeofday timeofday);
void    ft_usleep(long t, t_philo_arg *philo_av);
void	mutex_write_debug(t_philo_action action, t_philosopher *philo_av, long buf);
void	mutex_write(t_philo_action action, t_philosopher *philo_av, bool debug);
void	philo_eat(t_philosopher *philo_av);
void	philo_thinking(t_philosopher *philo_av, bool value);
void	start_simulation(t_philo_arg *philo_av);
void	long_increments( t_mutex *mutex, long *value);
long    atol_custom(const char *str);
void	*check_dinner(void *argv);
void	*long_thread(void *argv);
void    clean(t_philo_arg *philo_av);
bool    threads_active(t_mutex *mutex, long *threads, long philo_num);
void	disengage_threads(t_philosopher *philos);
bool	philo_dead(t_philosopher *philo_av);
#endif // PHILOSOPHER_H

