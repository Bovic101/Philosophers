/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vodebunm <vodebunm@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 00:14:10 by vodebunm          #+#    #+#             */
/*   Updated: 2024/07/29 14:41:06 by vodebunm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"
// ./philo 5 700 200 200 [6]
int main(int argc, char **argv)
{
	t_philo_arg philo_av;
	
	if (argc == 5 || argc == 6)
	{
		//1checking error, filling the table
		reading_input(&philo_av, argv);//to do
		//2 :creating the actual thing
		data_init(&philo_av);
		start_simulation(&philo_av);//3:dining start
		clean(&philo_av);//To do is for when all philo is full or 1 died
	}
	else
	{
		handle_error("Incorrect input, please pass atleast 5 arg\n");
	}
	
}