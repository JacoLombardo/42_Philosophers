/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 15:07:22 by jalombar          #+#    #+#             */
/*   Updated: 2024/09/10 16:33:07 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*ft_create_philos(t_philo *philos, t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->size)
	{
		philos[i].id = i + 1;
		philos[i].last_eat = ft_get_time();
		if (i - 1 >= 0)
			philos[i].left_fork_id = i - 1;
		else
			philos[i].left_fork_id = rules->size - 1;
		philos[i].right_fork_id = i;
		philos[i].dead = 0;
		philos[i].limit = rules->limit;
		philos[i].meals = 0;
		philos[i].full = 0;
		philos[i].rules = rules;
		i++;
	}
	return (philos);
}

void	philo(t_rules rules)
{
	if (rules.size == 1)
	{
		printf("%i %i has taken a fork\n", 0, 1);
		ft_usleep(rules.time_die);
		printf("%i %i died\n", rules.time_die, 1);
		return ;
	}
	if (ft_mutexes_init(&rules))
		return (ft_print_error(4));
	ft_create_philos(rules.philos, &rules);
	if (ft_threads_init(&rules))
		return (ft_print_error(5));
	ft_threads_close(&rules);
}

int	ft_set_n_check_rules(t_rules *rules, int argc, char **argv)
{
	rules->start = ft_get_time();
	rules->size = ft_atoi(argv[1]);
	rules->time_die = ft_atoi(argv[2]);
	rules->time_eat = ft_atoi(argv[3]);
	rules->time_sleep = ft_atoi(argv[4]);
	rules->dead = 0;
	rules->limit = 0;
	rules->full = 0;
	if (argc == 6)
	{
		rules->limit = 1;
		rules->meals = ft_atoi(argv[5]);
	}
	if (rules->size <= 0 || rules->time_die <= 0 || rules->time_eat <= 0
		|| rules->time_sleep <= 0 || (rules->limit && rules->meals <= 0))
		return (1);
	else
		return (0);
}

int	main(int argc, char **argv)
{
	t_rules	rules;

	if (argc == 5 || argc == 6)
	{
		if (ft_set_n_check_rules(&rules, argc, argv))
			ft_print_error(1);
		else
			philo(rules);
	}
	else if (argc < 5)
		ft_print_error(2);
	else if (argc > 6)
		ft_print_error(3);
	return (0);
}

/* int	main(int argc, char **argv)
{
	t_rules	rules;

	if (argc == 5 || argc == 6)
	{
		rules.start = ft_get_time();
		rules.size = ft_atoi(argv[1]);
		rules.time_die = ft_atoi(argv[2]);
		rules.time_eat = ft_atoi(argv[3]);
		rules.time_sleep = ft_atoi(argv[4]);
		rules.limit = 0;
		if (argc == 5)
			philo(rules);
	}
	if (argc == 6)
	{
		rules.limit = 1;
		rules.meals = ft_atoi(argv[5]);
		philo(rules);
	}
	else if (argc < 5)
		write(2, "ERROR: too few parameters\n", 27);
	else if (argc > 6)
		write(2, "ERROR: Too many parameters\n", 28);
	return (0);
} */
