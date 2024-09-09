/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 16:25:48 by jalombar          #+#    #+#             */
/*   Updated: 2024/09/09 17:46:55 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// int	ft_all_full(t_vars *vars)
// {
// 	if (vars->rules->reps)
// 	{
// 		if (vars->rules->meals >= (vars->rules->nb_reps * vars->rules->size))
// 		{
// 			vars->rules->done = 1;
// 			return (1);
// 		}
// 		else
// 			return (0);
// 	}
// 	return (0);
// }

// int	ft_is_dead(t_philo *philo, t_rules *rules)
// {
// 	if ((ft_get_time() - philo->last_eat) >= rules->time_die)
// 	{
// 		ft_print_message(philo->id, 5, philo->vars);
// 		rules->done = 1;
// 		return (1);
// 	}
// 	else
// 		return (0);
// }

void	ft_eat(t_philo *philo, t_vars *vars)
{
	pthread_mutex_lock(&vars->forks[philo->left_fork_id]);
	ft_print_message(philo->id, 1, vars);
	pthread_mutex_lock(&vars->forks[philo->right_fork_id]);
	ft_print_message(philo->id, 1, vars);
	pthread_mutex_lock(&vars->meal);
	ft_print_message(philo->id, 2, vars);
	philo->last_eat = ft_get_time();
	pthread_mutex_unlock(&vars->meal);
	usleep(vars->rules->time_eat * 1000);
	philo->meals++;
	if (vars->rules->limit && philo->meals == vars->rules->meals)
		philo->full = 1;
	pthread_mutex_unlock(&vars->forks[philo->left_fork_id]);
	pthread_mutex_unlock(&vars->forks[philo->right_fork_id]);
}

void	*ft_routine(void *pointer)
{
	t_philo	*philo;
	t_rules	*rules;
	t_vars	*vars;

	philo = (t_philo *)pointer;
	rules = philo->rules;
	vars = philo->vars;
	if (philo->id % 2)
		usleep(100);
	//printf("Inside philo %i\n", philo->id);
	while (!rules->dead || !rules->full)
	{
		//printf("                                   %i\n", rules->full);
		ft_eat(philo, vars);
		if (rules->full)
			break ;
		ft_print_message(philo->id, 3, vars);
		usleep(rules->time_sleep * 1000);
		ft_print_message(philo->id, 4, vars);
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
