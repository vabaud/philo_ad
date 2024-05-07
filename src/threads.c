/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abesneux <abesneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 20:39:12 by abesneux          #+#    #+#             */
/*   Updated: 2024/05/06 18:35:06 by abesneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	create_threads(t_philo **philos, t_params *params)
{
	int	current;

	params->start_time = get_timestamp();
	current = 0;
	while (current < params->num)
	{
		if (pthread_create(&((*philos)[current].thread), NULL, philo_life,
			&((*philos)[current])))
			return (0);
		current++;
	}
	if (pthread_create(&(params->death_thread), NULL, check_philos_death,
			philos))
		return (0);
	return (1);
}

int	wait_threads(t_philo **philos, t_params *params)
{
	int	current;
	int	return_code;

	current = 0;
	return_code = 1;
	while (current < params->num)
	{
		if (pthread_join((*philos)[current].thread, NULL))
			return_code = 0;
		current++;
	}
	if (pthread_join(params->death_thread, NULL))
        return_code = 0;
	return (return_code);
}
