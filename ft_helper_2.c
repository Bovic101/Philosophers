/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_helper_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vodebunm <vodebunm@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 10:59:15 by vodebunm          #+#    #+#             */
/*   Updated: 2024/08/05 11:32:24 by vodebunm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*malloc_control(size_t type)
{
	void *result;
	
	result = malloc(type);
	if (result == NULL)
	{
		handle_error("Memory allocation failed");
	}
	return(result);
}
static void mutex_return_status(int status, t_mutexfunc mutexfunc)
{
	if (status == 0)
	{
		return;
	}
	if (EINVAL == status && (MUTEX_LOCK == mutexfunc ||MUTEX_UNLOCK == mutexfunc ))
	{
		handle_error("The mutex was created with the protocol attr having the value PTHREAD_PRIO_PROTECT ");
	}
	else if (EINVAL == status && MUTEX_INIT == mutexfunc)
		handle_error("The value created by attribute is invalid");
	else if (EDEADLK == status)
		handle_error("A deadlock condition was detected.");
	else if (EBUSY == status)
		handle_error("The mutex could not be acquired because it was already locked");
	else if (EPERM == status)
		handle_error("The mutex type is PTHREAD_MUTEX_ERRORCHECK or PTHREAD_MUTEX_RECURSIVE");
	else if (ENOMEM == status)
		handle_error("The process can not allocate memory to create another mutex");
	else if (EOWNERDEAD == status)
		handle_error("The mutex is a robust mutex and the process containing the previous owning thread terminated while holding the mutex lock");
}

//mutex - init, destroy, lock and unlock function
void	mutex_control(t_mutex *mutex, t_mutexfunc mutexfunc)//possible problem
{
	if (MUTEX_LOCK == mutexfunc)
	{
		mutex_return_status(pthread_mutex_lock(mutex), mutexfunc);
	}
	else if (MUTEX_UNLOCK == mutexfunc)
	{
		mutex_return_status(pthread_mutex_unlock(mutex),mutexfunc);
	}
	else if (MUTEX_INIT == mutexfunc)
	{
		mutex_return_status(pthread_mutex_init(mutex,NULL),mutexfunc);
	}
	else if (MUTEX_DESTROY== mutexfunc)
	{
		mutex_return_status(pthread_mutex_destroy(mutex), mutexfunc);
	}
	else
		handle_error("Mutex control error,please check mutex contol function");
}

//create, join and detach
static void thread_return_status(int status, t_mutexfunc mutexfunc)
{
	if (status == 0)
	{
		return;
	}
	if (EAGAIN == status)
	{
		handle_error("A system-imposed limit on the number of threads was encountered");
	}
	else if (EINVAL == status && MUTEX_CREATE == mutexfunc)
		handle_error("Invalid settings in attr.");
	else if (EINVAL == status && MUTEX_JOIN == mutexfunc)
		handle_error("thread is not a joinable");
	else if (EINVAL == status && MUTEX_DETACH == mutexfunc)
		handle_error(" thread is not a joinable thread");
	else if (EDEADLK == status)
		handle_error("A deadlock condition was detected.");
	else if (EPERM == status)
		handle_error(" No permission to set the scheduling policy and parameters specified in attr");
	else if (ESRCH == status)
		handle_error(" thread is not a joinable thread");
}

void	thread_control(pthread_t *thread, void *(*start)(void *), void *arg, t_mutexfunc mutexfunc)
{
	if (MUTEX_CREATE == mutexfunc)
	{
		thread_return_status(pthread_create(thread, NULL, start, arg), mutexfunc);
	}
	else if (MUTEX_JOIN == mutexfunc)
	{
		thread_return_status(pthread_join(*thread, NULL), mutexfunc);
	}
	else if (MUTEX_DETACH == mutexfunc)
	{
		thread_return_status(pthread_detach(*thread), mutexfunc);
	}
	else
	{
		handle_error("Thread return status function erroe");
	}
}




