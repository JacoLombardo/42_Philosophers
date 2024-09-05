/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 15:07:36 by jalombar          #+#    #+#             */
/*   Updated: 2024/09/05 16:03:21 by jalombar         ###   ########.fr       */
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
	long long		start;
	int				size;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				reps;
	int				nb_reps;
	int				meals;
	int				done;
}					t_rules;

typedef struct s_philo
{
	int				id;
	long			last_eat;
	int				left_fork_id;
	int				right_fork_id;
	/* int				reps;
	int				nb_reps; */
	struct s_rules	*rules;
	struct s_vars	*vars;
}					t_philo;

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
int					ft_all_full(t_vars *vars);
int					ft_is_dead(t_philo *philo, t_rules *rules);
void				ft_eat(t_philo *philo, t_vars *vars);
/* void				ft_sleep(t_philo *philo, t_rules *rules, t_vars *vars);
void	ft_think(t_philo *philo, t_vars *vars); */
void				*ft_routine(void *vars);

/* threads */
int					ft_mutexes_init(t_vars *vars);
int					ft_threads_n_mutex_close(t_vars *vars);
int					ft_threads_init(t_vars *vars);

/* utils */
void				ft_print_message(int id, int nb, t_vars *vars);
long long			ft_get_time(void);
int					ft_atoi(char *str);

#endif