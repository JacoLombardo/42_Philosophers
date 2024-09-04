/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 09:48:51 by jalombar          #+#    #+#             */
/*   Updated: 2024/08/22 09:49:04 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_need_to_think(t_philo *philos, t_rules *rules)
{
	int				i;
	int				id;
	struct timeval	time;

	i = 0;
	id = philos[i].id;
	gettimeofday(&time, NULL);
	while (i < rules->size)
	{
		if ((time.tv_sec - philos[i].last_think.tv_sec) > (time.tv_sec
				- philos[id].last_think.tv_sec))
		{
			if ((time.tv_usec - philos[i].last_think.tv_usec) > (time.tv_usec
					- philos[id].last_think.tv_usec))
				id = i;
		}
		i++;
	}
	return (id);
}

int	ft_need_to_sleep(t_philo *philos, t_rules *rules)
{
	int				i;
	int				id;
	struct timeval	time;

	i = 0;
	id = philos[i].id;
	gettimeofday(&time, NULL);
	while (i < rules->size)
	{
		if ((time.tv_sec - philos[i].last_sleep.tv_sec) > (time.tv_sec
				- philos[id].last_sleep.tv_sec))
		{
			if ((time.tv_usec - philos[i].last_sleep.tv_usec) > (time.tv_usec
					- philos[id].last_sleep.tv_usec))
				id = i;
		}
		i++;
	}
	return (id);
}

int	ft_need_to_eat(t_philo *philos, t_rules *rules)
{
	int				i;
	int				id;
	struct timeval	time;

	i = 0;
	id = philos[i].id;
	gettimeofday(&time, NULL);
	while (i < rules->size)
	{
		if ((time.tv_sec - philos[i].last_eat.tv_sec) > (time.tv_sec
				- philos[id].last_eat.tv_sec))
		{
			if ((time.tv_usec - philos[i].last_eat.tv_usec) > (time.tv_usec
					- philos[id].last_eat.tv_usec))
				id = i;
		}
		i++;
	}
	return (id);
}