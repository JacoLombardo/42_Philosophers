/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 15:07:22 by jalombar          #+#    #+#             */
/*   Updated: 2024/09/09 18:38:32 by jalombar         ###   ########.fr       */
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
		if (i)
			philos[i].left_fork_id = i;
		else
			philos[i].left_fork_id = rules->size;
		philos[i].right_fork_id = i + 1;
		philos[i].dead = 0;
		philos[i].limit = rules->limit;
		philos[i].meals = 0;
		philos[i].rules = rules;
		i++;
	}
	return (philos);
}

void	ft_monitor(t_rules *rules)
{
	int		i;
	t_philo	*philos;

	philos = rules->philos;
	while (!rules->dead && !rules->full)
	{
		i = 0;
		while (i < rules->size)
		{
			pthread_mutex_lock(&rules->meal);
			if ((ft_get_time() - philos[i].last_eat) >= rules->time_die)
			{
				//printf("TIME: %lli\n\n", (ft_get_time() - philos[i].last_eat));
				ft_print_message(philos[i].id, 5, rules);
				rules->dead = 1;
			}
			pthread_mutex_unlock(&rules->meal);
			i++;
		}
		if (rules->dead)
			break ;
		// i = 0;
		// while (rules->limit && i < rules->size && philos[i].meals >= rules->meals)
		// 	i++;
		// if (i == rules->size)
		// {
		// 	rules->full = 1;
		// 	printf("                                                   DONE!\n");
		// 	break ;
		// }
	}
}

void	philo(t_rules rules)
{
	rules.dead = 0;
	rules.full = 0;
	if (rules.size == 1)
	{
		printf("%i %i died\n", 0, 1);
		return ;
	}
	if (ft_mutexes_init(&rules))
		return ;
	ft_create_philos(rules.philos, &rules);
	if (ft_threads_init(&rules))
		return ;
	//ft_monitor(&rules);
	ft_threads_n_mutex_close(&rules);
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
		printf("ERROR: too few parameters\n");
	else if (argc > 6)
		printf("ERROR: Too many parameters\n");
	return (0);
}
