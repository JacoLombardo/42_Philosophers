/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 15:07:22 by jalombar          #+#    #+#             */
/*   Updated: 2024/09/04 18:11:58 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*ft_create_philos(t_philo *philos, t_rules rules, t_vars vars)
{
	int				i;
	struct timeval	time;

	i = 0;
	gettimeofday(&time, NULL);
	while (i < rules.size)
	{
		philos[i].id = i + 1;
		philos[i].last_eat = ft_convert_milli(time);
		philos[i].last_sleep = ft_convert_milli(time);
		philos[i].last_think = ft_convert_milli(time);
		if (i)
			philos[i].left_fork_id = i;
		else
			philos[i].left_fork_id = rules.size;
		philos[i].right_fork_id = i + 1;
		philos[i].rules = &rules;
		philos[i].vars = &vars;
		i++;
	}
	return (philos);
}

int	ft_mutexes_init(t_vars vars, t_rules rules)
{
	int	i;

	i = 0;
	vars.forks = (pthread_mutex_t *)malloc(rules.size
			* sizeof(pthread_mutex_t));
	if (!vars.forks)
		return (0);
	while (i < rules.size)
	{
		if (pthread_mutex_init(&vars.forks[i], NULL))
			return (1);
		i++;
	}
	if (pthread_mutex_init(&vars.meal, NULL))
		return (1);
	if (pthread_mutex_init(&vars.write, NULL))
		return (1);
	return (0);
}

int	ft_threads_init(t_vars vars, t_rules rules)
{
	int	i;

	i = 0;
	vars.threads = (pthread_t *)malloc(rules.size * sizeof(pthread_t));
	if (!vars.threads)
		return (0);
	while (i < rules.size)
	{
		if (pthread_create(&vars.threads[i], NULL, ft_routine,
				&(vars.philos[i])))
			return (1);
	}
	return (0);
}

void	philo(t_rules rules)
{
	t_vars	vars;

	vars.rules = rules;
	printf("%i, %i\n", vars.rules.time_die, rules.time_die);
	if (ft_mutexes_init(vars, rules))
		return ;
	vars.philos = (t_philo *)malloc(rules.size * sizeof(t_philo));
	if (!vars.philos)
		return ;
	ft_create_philos(vars.philos, rules, vars);
	ft_threads_init(vars, rules);
	printf("Fine\n");
}

int	main(int argc, char **argv)
{
	t_rules	rules;

	if (argc == 5 || argc == 6)
	{
		rules.size = ft_atoi(argv[1]);
		rules.time_die = ft_atoi(argv[2]);
		rules.time_eat = ft_atoi(argv[3]);
		rules.time_sleep = ft_atoi(argv[4]);
		if (argc == 5)
			philo(rules);
	}
	if (argc == 6)
	{
		rules.repetitions = ft_atoi(argv[5]);
		philo(rules);
	}
	else if (argc < 5)
		printf("ERROR: too few parameters\n");
	else if (argc > 6)
		printf("ERROR: Too many parameters\n");
	return (0);
}
