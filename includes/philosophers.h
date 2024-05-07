/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abesneux <abesneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 20:39:51 by abesneux          #+#    #+#             */
/*   Updated: 2024/05/06 17:36:32 by abesneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_params
{
	int				num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meal_max;
	long			start_time;
	int				is_dead;
	pthread_mutex_t	mutex_is_dead;
	pthread_t		death_thread;
}					t_params;

typedef struct s_fork
{
	int				used;
	pthread_mutex_t	lock;
}					t_fork;

typedef struct s_philo
{
	pthread_t		thread;
	int				pos;
	long			last_meal;
	int				meal_count;

	pthread_mutex_t	meal_lock;

	t_fork			*l_fork;
	int				l_taken;
	t_fork			*r_fork;
	int				r_taken;

	t_params		*param;
}					t_philo;

// UTILS.C
void				exit_error(char *msg);
int					ft_atoi(const char *str);
void				write_state(char *str, t_philo *phil);
int					ft_usleep(size_t milliseconds);
long				get_timestamp(void);

// INIT.C
int					init_params(t_params *params, int ac, char **av);
int					create_philos(t_philo **philos, t_fork **forks,
						t_params *params);

// THREADS.C
int					create_threads(t_philo **philos, t_params *params);
int					wait_threads(t_philo **philos, t_params *params);

// DEATH.C
int					is_dead(t_philo *phil);
int					check_death(t_philo *phil, long current_time);
void				*check_philos_death(void *arg);
int					stop_thread(t_philo *phil);

// FORK.C
void				take_fork(char fork_name, t_philo *phil);
void				release_fork_and_sleep(t_philo *phil);
void				release_fork(char fork_name, t_philo *phil);

// MAIN.C
void				*philo_life(void *arg);
void				free_all(t_philo *philos, t_fork *forks);

#endif
