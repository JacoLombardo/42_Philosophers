/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 15:07:36 by jalombar          #+#    #+#             */
/*   Updated: 2024/09/04 18:09:15 by jalombar         ###   ########.fr       */
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
	long			last_eat;
	long			last_sleep;
	long			last_think;
	int				left_fork_id;
	int				right_fork_id;
	struct s_rules	*rules;
	struct s_vars	*vars;
}					t_philo;

typedef struct s_vars
{
	struct s_philo	*philos;
	struct s_rules	rules;
	pthread_mutex_t	*forks;
	pthread_mutex_t	meal;
	pthread_mutex_t	write;
	pthread_t		*threads;
}					t_vars;

/* routine */
int					ft_is_dead(t_philo *philo, t_rules *rules);
void				ft_eat(t_philo *philo, t_vars *vars);
void				ft_sleep(t_philo *philo, t_rules *rules, t_vars *vars);
void				ft_think(t_philo *philo, t_vars *vars);
void				*ft_routine(void *vars);

/* utils */
void				ft_print_message(int id, int nb, t_vars *vars);
long long			ft_convert_milli(struct timeval time);
int					ft_atoi(char *str);

#endif