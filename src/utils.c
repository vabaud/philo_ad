/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abesneux <abesneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 20:39:48 by abesneux          #+#    #+#             */
/*   Updated: 2024/05/06 17:35:03 by abesneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	exit_error(char *msg)
{
	printf("%s\n", msg);
	exit(EXIT_FAILURE);
}

int	ft_atoi(const char *str)
{
	int	sign;
	int	result;

	sign = 1;
	result = 0;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result *= 10;
		result += *str - 48;
		str++;
	}
	return (result * sign);
}

/*renvoie l'heure actuelle depuis l'epoque UNIX*/
long	get_timestamp(void)
{
	struct timeval	tv;
	time_t			t;
	time_t			t2;

	gettimeofday(&tv, NULL);
	t = tv.tv_sec * 1000;
	t2 = tv.tv_usec / 1000;
	return (t + t2);
}

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_timestamp();
	while ((get_timestamp() - start) < milliseconds)
		usleep(500);
	return (0);
}

void	write_state(char *str, t_philo *phil)
{
	long	current_time;

	current_time = get_timestamp() - phil->param->start_time;
	pthread_mutex_lock(&(phil->param->mutex_is_dead));
	if (phil->param->is_dead == 0)
		printf("%ld %d %s\n", current_time, phil->pos + 1, str);
	pthread_mutex_unlock(&(phil->param->mutex_is_dead));
}
