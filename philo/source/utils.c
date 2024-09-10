/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 15:49:13 by jalombar          #+#    #+#             */
/*   Updated: 2024/09/10 16:29:24 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_print_error(int nb)
{
	if (nb == 1)
		write(2, "ERROR: invalid parameter(s)\n", 29);
	else if (nb == 2)
		write(2, "ERROR: too few parameters\n", 27);
	else if (nb == 3)
		write(2, "ERROR: too many parameters\n", 28);
	else if (nb == 4)
		write(2, "ERROR: unable to initialize mutex\n", 35);
	else if (nb == 5)
		write(2, "ERROR: unable to create thread\n", 32);
	else if (nb == 6)
		write(2, "ERROR: unable to join thread\n", 30);
}

void	ft_print_message(int id, int nb, t_rules *rules)
{
	long long	start;

	start = rules->start;
	pthread_mutex_lock(&rules->write);
	if (nb == 1 && !rules->dead)
		printf("%lli %i has taken a fork\n", ft_get_time() - start, id);
	else if (nb == 2 && !rules->dead)
		printf("%lli %i is eating\n", ft_get_time() - start, id);
	else if (nb == 3 && !rules->dead)
		printf("%lli %i is sleeping\n", ft_get_time() - start, id);
	else if (nb == 4 && !rules->dead)
		printf("%lli %i is thinking\n", ft_get_time() - start, id);
	else if (nb == 5 && !rules->dead)
		printf("%lli %i died\n", ft_get_time() - start, id);
	pthread_mutex_unlock(&rules->write);
}

void	ft_usleep(long long milliseconds)
{
	long long	start;

	start = ft_get_time();
	while ((ft_get_time() - start) < milliseconds)
		usleep(500);
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
