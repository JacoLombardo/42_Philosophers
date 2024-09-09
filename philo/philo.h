/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 15:07:36 by jalombar          #+#    #+#             */
/*   Updated: 2024/09/09 18:34:37 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	int				id;
	long			last_eat;
	int				left_fork_id;
	int				right_fork_id;
	int				dead;
	int				limit;
	int				meals;
	int				full;
	struct s_rules	*rules;
}					t_philo;

typedef struct s_rules
{
	long long		start;
	int				size;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				dead;
	int				limit;
	int				meals;
	int				full;
	struct s_philo	philos[200];
	pthread_mutex_t	forks[200];
	pthread_mutex_t	meal;
	pthread_mutex_t	write;
	pthread_t		threads[200];
	pthread_t		monitor_dead;
	pthread_t		monitor_meals;
}					t_rules;

typedef struct s_vars
{
	struct s_philo	philos[200];
	struct s_rules	*rules;
	pthread_mutex_t	forks[200];
	pthread_mutex_t	meal;
	pthread_mutex_t	write;
	pthread_t		threads[200];
}					t_vars;

/* routine */
void				ft_eat(t_philo *philo, t_rules *rules);
void				*ft_routine(void *pointer);

/* threads */
int					ft_mutexes_init(t_rules *rules);
int					ft_threads_n_mutex_close(t_rules *rules);
int					ft_threads_init(t_rules *rules);

/* utils */
void				ft_print_message(int id, int nb, t_rules *rules);
long long			ft_get_time(void);
int					ft_atoi(char *str);

#endif