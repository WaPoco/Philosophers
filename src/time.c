/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpogorel <vpogorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 19:50:21 by vpogorel          #+#    #+#             */
/*   Updated: 2025/05/06 19:50:32 by vpogorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int last_meal_time(t_philosopher *p)
{
    struct timeval end;
    gettimeofday(&end, NULL);
    return (end.tv_sec - p->last_meal.tv_sec) * 1000
        + ((end.tv_usec - p->last_meal.tv_usec) / 1000);
}

int	get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int cur_time(t_philosopher *p)
{
    struct timeval end;
    gettimeofday(&end, NULL);
    return (end.tv_sec - p->rules->start.tv_sec) * 1000
        + ((end.tv_usec - p->rules->start.tv_usec) / 1000);
}

int	ft_usleep(int milliseconds)
{
	int	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(500);
	return (0);
}