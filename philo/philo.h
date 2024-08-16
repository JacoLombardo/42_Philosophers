/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 15:07:36 by jalombar          #+#    #+#             */
/*   Updated: 2024/08/16 17:43:42 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_rules
{
	int				size;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				repetitions;
}					t_rules;

typedef struct s_philo
{
	int				id;
	struct timeval	last_eat;
	struct timeval	last_sleep;
	struct timeval	last_think;
	struct s_rules	*rules;
}					t_philo;

typedef struct s_vars
{
	struct s_philo	*philos;
    struct s_rules	*rules;
	pthread_mutex_t	*mutex;
}					t_vars;

int					ft_atoi(char *str);

#endif