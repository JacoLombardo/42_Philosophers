/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 16:25:48 by jalombar          #+#    #+#             */
/*   Updated: 2024/08/16 17:57:30 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_need_to_think(t_philo *philos, t_rules *rules)
{
	int				i;
	int				id;
	struct timeval	time;

	i = 0;
	id = philos[i].id;
	gettimeofday(&time, NULL);
	while (i < rules->size)
	{
		if ((time.tv_sec - philos[i].last_think.tv_sec) > (time.tv_sec
				- philos[id].last_think.tv_sec))
		{
			if ((time.tv_usec - philos[i].last_think.tv_usec) > (time.tv_usec
					- philos[id].last_think.tv_usec))
				id = i;
		}
		i++;
	}
	return (id);
}

int	ft_need_to_sleep(t_philo *philos, t_rules *rules)
{
	int				i;
	int				id;
	struct timeval	time;

	i = 0;
	id = philos[i].id;
	gettimeofday(&time, NULL);
	while (i < rules->size)
	{
		if ((time.tv_sec - philos[i].last_sleep.tv_sec) > (time.tv_sec
				- philos[id].last_sleep.tv_sec))
		{
			if ((time.tv_usec - philos[i].last_sleep.tv_usec) > (time.tv_usec
					- philos[id].last_sleep.tv_usec))
				id = i;
		}
		i++;
	}
	return (id);
}

int	ft_need_to_eat(t_philo *philos, t_rules *rules)
{
	int				i;
	int				id;
	struct timeval	time;

	i = 0;
	id = philos[i].id;
	gettimeofday(&time, NULL);
	while (i < rules->size)
	{
		if ((time.tv_sec - philos[i].last_eat.tv_sec) > (time.tv_sec
				- philos[id].last_eat.tv_sec))
		{
			if ((time.tv_usec - philos[i].last_eat.tv_usec) > (time.tv_usec
					- philos[id].last_eat.tv_usec))
				id = i;
		}
		i++;
	}
	return (id);
}

int	ft_eating(t_vars *vars)
{
	int	i;

	i = 0;
	if (id == ft_need_to_eat(vars->philos, vars->rules))
}

void	*ft_routine(t_vars *vars)
{
	pthread_mutex_lock(vars->mutex);
}