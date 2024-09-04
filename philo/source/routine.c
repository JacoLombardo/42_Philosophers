/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 16:25:48 by jalombar          #+#    #+#             */
/*   Updated: 2024/09/04 18:12:07 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

/* int	ft_need_to_think(t_philo *philos, t_rules *rules)
{
	int	i;
	int	id;

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
	int	i;
	int	id;

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
	int	i;
	int	id;

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
	struct timeval	time;

	gettimeofday(&time, NULL);
	if (id == ft_need_to_eat(vars->philos, vars->rules))
	{
		printf("%li %i is eating...\n", vars->philos[id].last_eat, id);
		vars->philos[id].last_eat = ft_convert_milli(time);
		return (id);
	}
	return (0);
} */

int	ft_is_dead(t_philo *philo, t_rules *rules)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	//printf("DEAD: %lli, %li, %i\n", ft_convert_milli(time), philo->last_eat, rules->time_die);
	if ((ft_convert_milli(time) - philo->last_eat) >= rules->time_die)
	{
		ft_print_message(philo->id, 5, philo->vars);
		return (1);
	}
	else
		return (0);
}

void	ft_eat(t_philo *philo, t_vars *vars)
{
	struct timeval	time;

	pthread_mutex_lock(&vars->forks[philo->left_fork_id]);
	ft_print_message(philo->id, 1, vars);
	pthread_mutex_lock(&vars->forks[philo->right_fork_id]);
	ft_print_message(philo->id, 1, vars);
	pthread_mutex_lock(&vars->meal);
	ft_print_message(philo->id, 2, vars);
	pthread_mutex_unlock(&vars->meal);
	gettimeofday(&time, NULL);
	philo->last_eat = ft_convert_milli(time);
	pthread_mutex_unlock(&vars->forks[philo->left_fork_id]);
	pthread_mutex_unlock(&vars->forks[philo->right_fork_id]);
}

void	ft_sleep(t_philo *philo, t_rules *rules, t_vars *vars)
{
	ft_print_message(philo->id, 3, vars);
	usleep(rules->time_sleep);
}

void	ft_think(t_philo *philo, t_vars *vars)
{
	ft_print_message(philo->id, 4, vars);
}

void	*ft_routine(void *pointer)
{
	t_philo	*philo;
	t_rules	*rules;
	t_vars	*vars;

	philo = (t_philo *)pointer;
	rules = philo->rules;
	vars = philo->vars;
	//printf("ciaoooo\n");
	while (!ft_is_dead(philo, rules))
	{
		printf("ciao\n");
		ft_eat(philo, vars);
		ft_sleep(philo, rules, vars);
		ft_think(philo, vars);
	}
	return (0);
}
