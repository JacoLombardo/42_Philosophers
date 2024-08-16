/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 15:07:22 by jalombar          #+#    #+#             */
/*   Updated: 2024/08/16 17:44:21 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*ft_create_philos(t_rules *rules, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < rules->size)
	{
		philos[i].id = i;
		gettimeofday(&philos[i].last_eat, NULL);
		gettimeofday(&philos[i].last_sleep, NULL);
		gettimeofday(&philos[i].last_think, NULL);
		philos[i].rules = (t_rules *)malloc(1 * sizeof(t_rules));
		philos[i].rules->size = rules->size;
		philos[i].rules->time_die = rules->time_die;
		philos[i].rules->time_eat = rules->time_eat;
		philos[i].rules->time_sleep = rules->time_sleep;
		philos[i].rules->repetitions = rules->repetitions;
		i++;
	}
	return (philos);
}



int	ft_threads_init(t_vars *vars, t_rules *rules)
{
	int				i;
	pthread_t		*threads;
	pthread_mutex_t	mutex;

	i = 0;
	threads = (pthread_t *)malloc(rules->size * sizeof(pthread_t));
	if (!threads)
		return (0);
	pthread_mutex_init(&mutex, NULL);
    vars->mutex = &mutex;
	while (i < rules->size)
	{
		if (pthread_create(&threads[i], NULL, ft_routine, vars) != 0)
			return (i);
	}
	i = 0;
	while (i < rules->size)
	{
		if (pthread_join(threads[i], NULL) != 0)
			return (i);
		i++;
	}
	pthread_mutex_destroy(&mutex);
}

void	philo(t_rules *rules)
{
	t_philo	*philos;
    t_vars  vars;
	int		id;

	philos = (t_philo *)malloc(rules->size * sizeof(t_philo));
	if (!philos)
		return ;
	ft_create_philos(rules, philos);
    vars.philos = philos;
    vars.rules = rules;
	id = ft_threads_init(&vars, rules);
	if (id)
		printf("Philosopher %i has died! :(\n", id);
}

int	main(int argc, char **argv)
{
	t_rules	*rules;

	rules = (t_rules *)malloc(1 * sizeof(t_rules));
	if (!rules)
		return (0);
	if (argc == 5 || argc == 6)
	{
		rules->size = ft_atoi(argv[1]);
		rules->time_die = ft_atoi(argv[2]);
		rules->time_eat = ft_atoi(argv[3]);
		rules->time_sleep = ft_atoi(argv[4]);
		if (argc == 5)
			philo(rules);
	}
	if (argc == 6)
	{
		rules->repetitions = ft_atoi(argv[5]);
		philo(rules);
	}
	else if (argc < 5)
		printf("ERROR: too few parameters\n");
	else if (argc > 6)
		printf("ERROR: Too many parameters\n");
	return (0);
}
