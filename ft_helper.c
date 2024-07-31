/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_helper.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vodebunm <vodebunm@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 00:42:47 by vodebunm          #+#    #+#             */
/*   Updated: 2024/07/31 12:33:06 by vodebunm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

long convert_to_millisec(const char *time_str)
{
    return (atol(time_str) * 1000);
}

void handle_error(const char *str)
{
	printf("Error occured:%s\n", str);
	exit(EXIT_FAILURE);
}

static inline bool is_digit(char c)
{
	return( c >= '0' && c <= '9');
}

const char	*acceptable_input(const char *str)
{
	int length;
	const char *nbr;
	
	length = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
	{
		str++;
	}
	if (*str == '+')
	{
		str++;
	}
	else if (*str == '-')
	{
		handle_error("Negative value not allowed");
	}
	if (!is_digit(*str))
	{
		handle_error("The digit is not within the acceptable range");
	}
	nbr = str;
	while (is_digit(*str++))
	{
		length++;
	}
	if (length > 10)
		handle_error("digit range is beyond accepatable limit");	
}

long atol(const char *str)
{
	long nbr;
	
	nbr = 0;
	str = acceptable_input(str);
	while (is_digit(*str))
	{
		nbr = (nbr * 10) + (*str++ - '0');
	}
	if (nbr > INT_MAX)
	{
		handle_error("digit range is beyond accepatable limit");
	}
	return(nbr);
}
