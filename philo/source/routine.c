/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 16:25:48 by jalombar          #+#    #+#             */
/*   Updated: 2024/08/23 18:52:05 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_need_to_think(t_philo *philos, t_rules *rules)
{
	int				i;
	int				id;

	i = 0;
	id = philos[i].id;
	while (i < rules->size)
	{
		if (philos[i].last_think < philos[id - 1].last_think)
			id = philos[i].id;
		i++;
	}
	return (id);
}

int	ft_need_to_sleep(t_philo *philos, t_rules *rules)
{
	int				i;
	int				id;

	i = 0;
	id = philos[i].id;
	while (i < rules->size)
	{
		if (philos[i].last_sleep < philos[id - 1].last_sleep)
			id = philos[i].id;
		i++;
	}
	return (id);
}

int	ft_need_to_eat(t_philo *philos, t_rules *rules)
{
	int				i;
	int				id;

	i = 0;
	id = philos[i].id;
	while (i < rules->size)
	{
		if (philos[i].last_eat < philos[id - 1].last_eat)
			id = philos[i].id;
		i++;
	}
	return (id);
}

int	ft_eating(t_vars *vars, int id)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	if (id == ft_need_to_eat(vars->philos, vars->rules))
	{
		printf("%li %i is eating...\n", vars->philos[id].last_eat, id);
		vars->philos[id].last_eat = ft_convert_milli(time);
		return (id);
	}
	return (0);
}

void	*ft_routine(void *pointer)
{
	t_philo	*philo = (t_philo *)pointer;
	while (!ft_is_dead(philo))
	{
		ft_eat(philo);
		ft_sleep(philo);
		ft_think(philo);
	}
	return (0);
}