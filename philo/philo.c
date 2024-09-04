/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 15:07:22 by jalombar          #+#    #+#             */
/*   Updated: 2024/08/22 12:01:43 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* cercare di capire come passare argomenti al create_thread facendo si che si possano usare anche negli altri thread */

t_philo	*ft_create_philos(t_rules *rules, t_philo *philos)
{
	int	i;
	struct timeval	time;

	i = 0;
	gettimeofday(&time, NULL);
	while (i < rules->size)
	{
		philos[i].id = i + 1;
		philos[i].last_eat = ft_convert_milli(time);
		philos[i].last_sleep = ft_convert_milli(time);
		philos[i].last_think = ft_convert_milli(time);
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
	int				**test;

	i = 0;
	threads = (pthread_t *)malloc(rules->size * sizeof(pthread_t));
	if (!threads)
		return (0);
	test = (int **)malloc(rules->size * sizeof(int));
	if (!test)
		return (0);
	pthread_mutex_init(&mutex, NULL);
    vars->mutex = &mutex;
	while (i++ < rules->size)
	{
		vars->id = i;
		test[i - 1] = (int *)malloc(1 * sizeof(int));
		*test[i - 1] = 0;
		printf("Thread for %i opened\n", vars->id);
		if (pthread_create(&threads[i - 1], NULL, ft_routine, test[i - 1]) != 0)
			return (i);
	}
	vars->id = 0;
	printf("Count: %i\n", *test[3]);
	// i = 0;
	// while (i++ < rules->size)
	// {
	// 	printf("Thread for %i closed\n", i);
	// 	if (pthread_join(threads[i - 1], NULL) != 0)
	// 		return (i);
	// }
	pthread_mutex_destroy(&mutex);
	return (0);
}

void	philo(t_rules *rules)
{
	t_philo	*philos;
    t_vars  vars;
	int		id;

	philos = (t_philo *)malloc(rules->size * sizeof(t_philo));
	printf("Size: %i\n", rules->size);
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
