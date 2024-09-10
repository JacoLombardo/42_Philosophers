/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 15:07:36 by jalombar          #+#    #+#             */
/*   Updated: 2024/09/10 16:31:50 by jalombar         ###   ########.fr       */
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
	pthread_t		monitor;
}					t_rules;

/* routine */
int					ft_is_dead(t_rules *rules, t_philo *philos);
int					ft_all_full(t_rules *rules, t_philo *philos);
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