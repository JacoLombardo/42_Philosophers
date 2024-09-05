/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 11:56:21 by jalombar          #+#    #+#             */
/*   Updated: 2024/09/05 16:27:03 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_mutexes_init(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < vars->rules->size)
	{
		if (pthread_mutex_init(&vars->forks[i], NULL))
			return (1);
		i++;
	}
	if (pthread_mutex_init(&vars->meal, NULL))
		return (1);
	if (pthread_mutex_init(&vars->write, NULL))
		return (1);
	return (0);
}

int	ft_threads_n_mutex_close(t_vars *vars)
{
	int	i;

	i = 0;
    //printf("I'm closing everything\n");
	while (i < vars->rules->size)
	{
		if (pthread_join(vars->threads[i], NULL))
			return (1);
		if (pthread_mutex_destroy(&vars->forks[i]))
			return (1);
		i++;
	}
	return (0);
}

int	ft_threads_init(t_vars *vars)
{
	int	i;

	i = 0;
	/* vars.threads = (pthread_t *)malloc(rules.size * sizeof(pthread_t));
	if (!vars.threads)
		return (0); */
	while (i < vars->rules->size)
	{
		if (pthread_create(&vars->threads[i], NULL, ft_routine,
				&(vars->philos[i])))
			return (1);
            //return (ft_threads_n_mutex_close(vars));
		i++;
	}
	return (0);
}
