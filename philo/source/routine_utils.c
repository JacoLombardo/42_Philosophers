/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 17:21:16 by jalombar          #+#    #+#             */
/*   Updated: 2024/09/11 17:21:53 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_is_dead(t_rules *rules, t_philo *philos)
{
	int			i;
	long long	time;

	i = 0;
	while (i < rules->size)
	{
		pthread_mutex_lock(&rules->meal_m);
		time = ft_get_time() - philos[i].last_eat;
		pthread_mutex_unlock(&rules->meal_m);
		if (time > rules->time_die)
		{
			ft_print_message(philos[i].id, 5, rules);
			pthread_mutex_lock(&rules->dead_m);
			rules->dead = 1;
			return (pthread_mutex_unlock(&rules->dead_m), 1);
		}
		i++;
	}
	return (0);
}

int	ft_all_full(t_rules *rules, t_philo *philos)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&rules->meal_m);
	while (i < rules->size && philos[i].full)
		i++;
	pthread_mutex_unlock(&rules->meal_m);
	if (i == rules->size)
	{
		pthread_mutex_lock(&rules->full_m);
		rules->full = 1;
		return (pthread_mutex_unlock(&rules->full_m), 1);
	}
	else
		return (0);
}

int	ft_dead_get(t_rules *rules)
{
	pthread_mutex_lock(&rules->dead_m);
	if (rules->dead)
		return (pthread_mutex_unlock(&rules->dead_m), 1);
	else
		return (pthread_mutex_unlock(&rules->dead_m), 0);
}
