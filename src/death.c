/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabaud <vabaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:52:48 by qrshh             #+#    #+#             */
/*   Updated: 2024/05/07 18:54:53 by vabaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	is_dead(t_philo *phil)
{
	int	alive;

	alive = 0;
	pthread_mutex_lock(&(phil->param->mutex_is_dead));
	alive = phil->param->is_dead;
	pthread_mutex_unlock(&(phil->param->mutex_is_dead));
	return (alive);
}

int stop_thread(t_philo *phil)
{
	pthread_mutex_lock(&(phil->param->mutex_is_dead));
	phil->param->is_dead = 1;
	pthread_mutex_unlock(&(phil->param->mutex_is_dead));
	return(0);
}

int	check_death(t_philo *phil, long current_time)
{
	int	dead;
	int	last_meal;

	dead = 0;
	pthread_mutex_lock(&(phil->meal_lock));
	last_meal = current_time - phil->last_meal;
	pthread_mutex_unlock(&(phil->meal_lock));
	if (last_meal > phil->param->time_to_die)
	{
		write_state("Died", phil);
		pthread_mutex_lock(&(phil->param->mutex_is_dead));
		phil->param->is_dead = 1;
		pthread_mutex_unlock(&(phil->param->mutex_is_dead));
		dead = 1;
	}
	return (dead);
}

int all_philo_have_eat(t_philo **philos)
{
    t_params *params;
    int i = 0;

    params = (*philos)[0].param;
    while (i < params->num)
    {
        pthread_mutex_lock(&(params->mutex_is_dead));
        if ((*philos)[i].meal_count < params->meal_max)
        {
            pthread_mutex_unlock(&(params->mutex_is_dead));
            return (0);
        }
        i++;
        pthread_mutex_unlock(&(params->mutex_is_dead));
    }
    return (1);
}

void	*check_philos_death(void *arg)
{
	t_params	*params;
	t_philo		**philos;
	long		current_time;
	int			current;

	philos = (t_philo **)arg;
	params = (*philos)[0].param;
	while (1)
	{
		current = 0;
		current_time = get_timestamp() - params->start_time;
		while (current < params->num)
		{
            if (all_philo_have_eat(philos) && params->meal_max != -1)
                return (NULL);
			if (check_death(&(*philos)[current], current_time))
				return (NULL);
			current++;
		}
		ft_usleep(1);
	}
	return (NULL);
}
