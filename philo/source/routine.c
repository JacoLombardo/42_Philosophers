/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 16:25:48 by jalombar          #+#    #+#             */
/*   Updated: 2024/09/11 17:21:47 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_eat(t_philo *philo, t_rules *rules)
{
	if (philo->id % 2)
	{
		pthread_mutex_lock(philo->right_fork);
		ft_print_message(philo->id, 1, rules);
		pthread_mutex_lock(philo->left_fork);
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		ft_print_message(philo->id, 1, rules);
		pthread_mutex_lock(philo->right_fork);
	}
	ft_print_message(philo->id, 1, rules);
	pthread_mutex_lock(&rules->meal_m);
	ft_print_message(philo->id, 2, rules);
	philo->last_eat = ft_get_time();
	philo->meals++;
	if (rules->limit && philo->meals == rules->meals)
		philo->full = 1;
	pthread_mutex_unlock(&rules->meal_m);
	ft_usleep(rules->time_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	*ft_monitor(void *pointer)
{
	t_rules	*rules;
	t_philo	*philos;

	rules = (t_rules *)pointer;
	philos = rules->philos;
	while (1)
	{
		if (ft_is_dead(rules, philos))
			break ;
		if (rules->limit)
		{
			if (ft_all_full(rules, philos))
				break ;
		}
	}
	return (NULL);
}

void	*ft_routine(void *pointer)
{
	t_philo	*philo;
	t_rules	*rules;

	philo = (t_philo *)pointer;
	rules = philo->rules;
	if (philo->id % 2)
		ft_usleep(1);
	while (!ft_dead_get(rules))
	{
		ft_eat(philo, rules);
		pthread_mutex_lock(&rules->full_m);
		if (rules->full)
			return (pthread_mutex_unlock(&rules->full_m), NULL);
		pthread_mutex_unlock(&rules->full_m);
		ft_print_message(philo->id, 3, rules);
		ft_usleep(rules->time_sleep);
		ft_print_message(philo->id, 4, rules);
	}
	return (NULL);
}
