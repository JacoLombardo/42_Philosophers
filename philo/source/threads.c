/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 11:56:21 by jalombar          #+#    #+#             */
/*   Updated: 2024/09/09 18:37:55 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

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
	if (pthread_mutex_init(&rules->meal, NULL))
		return (1);
	if (pthread_mutex_init(&rules->write, NULL))
		return (1);
	return (0);
}

int	ft_threads_n_mutex_close(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->size)
	{
		if (pthread_join(rules->threads[i], NULL))
			return (1);
		if (pthread_mutex_destroy(&rules->forks[i]))
			return (1);
		i++;
	}
	if (pthread_join(rules->monitor_dead, NULL))
			return (1);
	if (rules->limit)
	{
		if (pthread_join(rules->monitor_meals, NULL))
			return (1);
	}
	return (0);
}

void	*ft_monitor_dead(void *pointer)
{
	int i;
	t_rules	*rules;
	t_philo	*philos;

	rules = (t_rules *)pointer;
	philos = rules->philos;
	while (!rules->dead && !rules->full)
	{
		i = 0;
		while (i < rules->size)
		{
			pthread_mutex_lock(&rules->meal);
			if ((ft_get_time() - philos[i].last_eat) >= rules->time_die)
			{
				ft_print_message(philos[i].id, 5, rules);
				rules->dead = 1;
			}
			pthread_mutex_unlock(&rules->meal);
			i++;
		}
		if (rules->dead)
			break ;
	}
	return (NULL);
}

void	*ft_monitor_meals(void *pointer)
{
	int i;
	t_rules	*rules;
	t_philo	*philos;

	rules = (t_rules *)pointer;
	philos = rules->philos;
	while (!rules->dead)
	{
		i = 0;
		while (rules->limit && i < rules->size && philos[i].meals >= rules->meals)
			i++;
		if (i == rules->size)
		{
			rules->full = 1;
			break ;
		}
		//i++;
	}
	return (NULL);
}

int	ft_threads_init(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->size)
	{
		if (pthread_create(&rules->threads[i], NULL, ft_routine,
				&(rules->philos[i])))
			return (1);
		i++;
	}
	if (pthread_create(&rules->monitor_dead, NULL, ft_monitor_dead, rules))
			return (1);
	if (rules->limit)
	{
		if (pthread_create(&rules->monitor_meals, NULL, ft_monitor_meals, rules))
			return (1);
	}
	return (0);
}
