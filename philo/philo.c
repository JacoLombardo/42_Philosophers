/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 15:07:22 by jalombar          #+#    #+#             */
/*   Updated: 2024/09/05 16:27:08 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*ft_create_philos(t_philo *philos, t_rules rules, t_vars vars)
{
	int	i;

	i = 0;
	while (i < rules.size)
	{
		philos[i].id = i + 1;
		philos[i].last_eat = ft_get_time();
		if (i)
			philos[i].left_fork_id = i;
		else
			philos[i].left_fork_id = rules.size;
		philos[i].right_fork_id = i + 1;
		/* philos[i].reps = rules.reps;
		if (philos[i].reps)
			philos[i].nb_reps = rules.nb_reps; */
		philos[i].rules = &rules;
		philos[i].vars = &vars;
		i++;
	}
	return (philos);
}

void	ft_monitor(t_vars *vars)
{
	int		i;
	t_philo	*philos;

	philos = vars->philos;
	while (!vars->rules->done)
	{
		i = 0;
		while (i < vars->rules->size)
		{
			if ((ft_get_time() - philos[i].last_eat) >= vars->rules->time_die)
			{
				ft_print_message(philos[i].id, 5, vars);
				vars->rules->done = 1;
				return ;
			}
		}
		if (ft_all_full(vars))
			break ;
	}
}

void	philo(t_rules rules)
{
	t_vars	vars;

	rules.done = 0;
	vars.rules = &rules;
	if (rules.size == 1)
	{
		printf("%i %i died\n", 0, 1);
		return ;
	}
	if (ft_mutexes_init(&vars))
		return ;
	ft_create_philos(vars.philos, rules, vars);
	if (ft_threads_init(&vars))
		return ;
	ft_monitor(&vars);
	ft_threads_n_mutex_close(&vars);
	//printf("Fine\n");
}

int	main(int argc, char **argv)
{
	t_rules	rules;

	if (argc == 5 || argc == 6)
	{
		rules.start = ft_get_time();
		rules.size = ft_atoi(argv[1]);
		rules.time_die = ft_atoi(argv[2]);
		rules.time_eat = ft_atoi(argv[3]);
		rules.time_sleep = ft_atoi(argv[4]);
		rules.reps = 0;
		if (argc == 5)
			philo(rules);
	}
	if (argc == 6)
	{
		rules.reps = 1;
		rules.nb_reps = ft_atoi(argv[5]);
		rules.meals = 0;
		philo(rules);
	}
	else if (argc < 5)
		printf("ERROR: too few parameters\n");
	else if (argc > 6)
		printf("ERROR: Too many parameters\n");
	return (0);
}
