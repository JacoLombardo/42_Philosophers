/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 15:49:13 by jalombar          #+#    #+#             */
/*   Updated: 2024/09/05 14:40:08 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_print_message(int id, int nb, t_vars *vars)
{
	long long	start;

	start = vars->rules->start;
	pthread_mutex_lock(&vars->write);
	if (nb == 1)
		printf("%lli %i has taken a fork\n", ft_get_time() - start, id);
	else if (nb == 2)
		printf("%lli %i is eating\n", ft_get_time() - start, id);
	else if (nb == 3)
		printf("%lli %i is sleeping\n", ft_get_time() - start, id);
	else if (nb == 4)
		printf("%lli %i is thinking\n", ft_get_time() - start, id);
	else if (nb == 5)
		printf("%lli %i died\n", ft_get_time() - start, id);
	pthread_mutex_unlock(&vars->write);
}

long long	ft_get_time(void)
{
	long long		milliseconds;
	struct timeval	time;

	gettimeofday(&time, NULL);
	milliseconds = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (milliseconds);
}

int	ft_atoi(char *str)
{
	int	result;
	int	sign;

	result = 0;
	sign = 1;
	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\r'
		|| *str == '\v' || *str == '\f')
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = sign * -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = (result * 10) + (*str - 48);
		str++;
	}
	return (result * sign);
}
