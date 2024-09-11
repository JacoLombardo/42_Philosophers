/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 11:56:21 by jalombar          #+#    #+#             */
/*   Updated: 2024/09/11 15:18:16 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_error_close(t_rules *rules, int end)
{
	int	i;

	i = 0;
	rules->dead = 1;
	while (i < end)
	{
		pthread_join(rules->threads[i], NULL);
		i++;
	}
	ft_mutexes_close(rules);
	return (1);
}

void	ft_mutexes_close(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->size)
	{
		pthread_mutex_destroy(&rules->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&rules->meal_m);
	pthread_mutex_destroy(&rules->write_m);
	pthread_mutex_destroy(&rules->dead_m);
	pthread_mutex_destroy(&rules->full_m);
}

int	ft_threads_close(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->size)
	{
		if (pthread_join(rules->threads[i], NULL))
			return (ft_print_error(6), 1);
		i++;
	}
	if (pthread_join(rules->monitor, NULL))
		return (ft_print_error(6), 1);
	ft_mutexes_close(rules);
	return (0);
}

int	ft_mutexes_init(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->size)
	{
		if (pthread_mutex_init(&rules->forks[i], NULL))
			return (1);
		i++;
	}
	if (pthread_mutex_init(&rules->meal_m, NULL))
		return (1);
	if (pthread_mutex_init(&rules->write_m, NULL))
		return (1);
	if (pthread_mutex_init(&rules->dead_m, NULL))
		return (1);
	if (pthread_mutex_init(&rules->full_m, NULL))
		return (1);
	return (0);
}

int	ft_threads_init(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->size)
	{
		if (pthread_create(&rules->threads[i], NULL, ft_routine,
				&(rules->philos[i])))
			return (ft_error_close(rules, i));
		i++;
	}
	if (pthread_create(&rules->monitor, NULL, ft_monitor, rules))
		return (ft_error_close(rules, i));
	return (0);
}
