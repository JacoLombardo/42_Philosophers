/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 15:07:36 by jalombar          #+#    #+#             */
/*   Updated: 2024/09/11 17:24:06 by jalombar         ###   ########.fr       */
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
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
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
	pthread_mutex_t	meal_m;
	pthread_mutex_t	write_m;
	pthread_mutex_t	dead_m;
	pthread_mutex_t	full_m;
	pthread_t		threads[200];
	pthread_t		monitor;
}					t_rules;

/* routine_utils */
int					ft_is_dead(t_rules *rules, t_philo *philos);
int					ft_all_full(t_rules *rules, t_philo *philos);
int					ft_dead_get(t_rules *rules);

/* routine */
void				ft_eat(t_philo *philo, t_rules *rules);
void				*ft_monitor(void *pointer);
void				*ft_routine(void *pointer);

/* threads */
int					ft_error_close(t_rules *rules, int end);
void				ft_mutexes_close(t_rules *rules);
int					ft_threads_close(t_rules *rules);
int					ft_mutexes_init(t_rules *rules);
int					ft_threads_init(t_rules *rules);

/* utils */
void				ft_print_error(int nb);
void				ft_print_message(int id, int nb, t_rules *rules);
void				ft_usleep(long long milliseconds);
long long			ft_get_time(void);
int					ft_atoi(char *str);

#endif