/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitore.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpogorel <vpogorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 19:49:46 by vpogorel          #+#    #+#             */
/*   Updated: 2025/08/13 17:51:18 by vpogorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	check_end_simulation(t_philosopher *p)
{
	int	i;
	int	sum;

	i = 0;
	sum = 0;
	if (p->rules->number_of_times_each_philosopher_must_eat == -1)
		return (1);
	while (i < p->rules->number_of_philosophers)
	{
		pthread_mutex_lock(p->rules->meal);
		if (p->rules->each_philosopher_has_eaten[i] 
			>= p->rules->number_of_times_each_philosopher_must_eat)
			sum += 1;
		pthread_mutex_unlock(p->rules->meal);
		i++;
	}
	if (sum == p->rules->number_of_philosophers)
	{
		pthread_mutex_lock(p->rules->dead_lock);
		*p->rules->dead = 1;
		pthread_mutex_unlock(p->rules->dead_lock);
		return (0);
	}
	return (1);
}

int	check_last_meal(t_philosopher *p)
{
	pthread_mutex_lock(p->meals);
	if ((last_meal_time(p) >= p->rules->time_to_die) && (*p->eats == 0))
	{
		pthread_mutex_unlock(p->meals);
		pthread_mutex_lock(p->rules->dead_lock);
		if (*p->rules->dead == 0)
		{
			pthread_mutex_lock(p->rules->print);
			printf("%d %d died\n", cur_time(p), p->id);
			pthread_mutex_unlock(p->rules->print);
		}
		*p->rules->dead = 1;
		pthread_mutex_unlock(p->rules->dead_lock);
		return (0);
	}
	pthread_mutex_unlock(p->meals);
	return (1);
}

void	*monitore(void *arg)
{
	t_philosopher	*p;

	p = (t_philosopher *)arg;
	while (!atleat_one_dead(p))
	{
		ft_usleep(p, 10);
		if (!check_end_simulation(p))
			break ;
		if (!check_last_meal(p))
			break ;
	}
	return (NULL);
}
