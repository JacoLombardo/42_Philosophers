/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 16:25:48 by jalombar          #+#    #+#             */
/*   Updated: 2024/09/10 16:51:20 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_is_dead(t_rules *rules, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < rules->size)
	{
		pthread_mutex_lock(&rules->meal);
		if ((ft_get_time() - philos[i].last_eat) > rules->time_die)
		{
			ft_print_message(philos[i].id, 5, rules);
			rules->dead = 1;
			pthread_mutex_unlock(&rules->meal);
			return (1);
		}
		pthread_mutex_unlock(&rules->meal);
		i++;
	}
	return (0);
}

int	ft_all_full(t_rules *rules, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < rules->size && philos[i].full)
		i++;
	if (i == rules->size)
	{
		rules->full = 1;
		return (1);
	}
	else
		return (0);
}

void	ft_eat(t_philo *philo, t_rules *rules)
{
	pthread_mutex_lock(&rules->forks[philo->left_fork_id]);
	ft_print_message(philo->id, 1, rules);
	pthread_mutex_lock(&rules->forks[philo->right_fork_id]);
	ft_print_message(philo->id, 1, rules);
	pthread_mutex_lock(&rules->meal);
	ft_print_message(philo->id, 2, rules);
	philo->last_eat = ft_get_time();
	philo->meals++;
	if (rules->limit && philo->meals == rules->meals)
		philo->full = 1;
	pthread_mutex_unlock(&rules->meal);
	ft_usleep(rules->time_eat);
	pthread_mutex_unlock(&rules->forks[philo->left_fork_id]);
	pthread_mutex_unlock(&rules->forks[philo->right_fork_id]);
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
		ft_usleep(100);
	while (!rules->dead && !rules->full)
	{
		ft_eat(philo, rules);
		if (rules->full || rules->dead)
			break ;
		ft_print_message(philo->id, 3, rules);
		ft_usleep(rules->time_sleep);
		ft_print_message(philo->id, 4, rules);
	}
	return (NULL);
}
