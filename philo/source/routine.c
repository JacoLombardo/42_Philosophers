/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 16:25:48 by jalombar          #+#    #+#             */
/*   Updated: 2024/09/09 18:47:56 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_eat(t_philo *philo, t_rules *rules)
{
	pthread_mutex_lock(&rules->forks[philo->left_fork_id]);
	ft_print_message(philo->id, 1, rules);
	pthread_mutex_lock(&rules->forks[philo->right_fork_id]);
	ft_print_message(philo->id, 1, rules);
	pthread_mutex_lock(&rules->meal);
	ft_print_message(philo->id, 2, rules);
	philo->last_eat = ft_get_time();
	pthread_mutex_unlock(&rules->meal);
	usleep(rules->time_eat * 1000);
	philo->meals++;
	if (rules->limit && philo->meals == rules->meals)
		philo->full = 1;
	pthread_mutex_unlock(&rules->forks[philo->left_fork_id]);
	pthread_mutex_unlock(&rules->forks[philo->right_fork_id]);
}

void	*ft_routine(void *pointer)
{
	t_philo	*philo;
	t_rules	*rules;

	philo = (t_philo *)pointer;
	rules = philo->rules;
	if (philo->id % 2)
		usleep(100);
	while (!rules->dead && !rules->full)
	{
		//printf("TIME: %lli\n\n", (ft_get_time() -  philo->last_eat));
		if ((ft_get_time() - philo->last_eat) >= rules->time_die)
			break ;
		ft_eat(philo, rules);
		if (rules->full || rules->dead)
			break ;
		ft_print_message(philo->id, 3, rules);
		usleep(rules->time_sleep * 1000);
		if (rules->full || rules->dead)
			break ;
		ft_print_message(philo->id, 4, rules);
		if (rules->full || rules->dead)
			break ;
	}
	return (NULL);
}

/* void	ft_sleep(t_philo *philo, t_rules *rules, t_vars *vars)
{
	ft_print_message(philo->id, 3, vars);
	usleep(rules->time_sleep * 1000);
}

void	ft_think(t_philo *philo, t_vars *vars)
{
	ft_print_message(philo->id, 4, vars);
} */

/* void	*ft_routine(void *pointer)
{
	t_philo	*philo;
	t_rules	*rules;
	t_vars	*vars;

	philo = (t_philo *)pointer;
	rules = philo->rules;
	vars = philo->vars;
	if (philo->id % 2)
		usleep(100);
	while (!ft_is_dead(philo, rules))
	{
		if (ft_all_full(vars))
		{
			printf("%i out\n", philo->id);
			break ;
		}
		ft_eat(philo, vars);
		if (rules->dead)
		{
			printf("%i out\n", philo->id);
			break ;
		}
		ft_print_message(philo->id, 3, vars);
		usleep(rules->time_sleep * 1000);
		if (rules->dead)
		{
			printf("%i out\n", philo->id);
			break ;
		}
		ft_print_message(philo->id, 4, vars);
	}
	return (NULL);
} */
