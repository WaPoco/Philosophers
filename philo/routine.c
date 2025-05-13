/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpogorel <vpogorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 19:50:08 by vpogorel          #+#    #+#             */
/*   Updated: 2025/05/13 16:51:24 by vpogorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	thinking(t_philosopher *p)
{
	print_message(p, "is thinking");
}

void	sleep_time(t_philosopher *p)
{
	print_message(p, "is sleeping");
	ft_usleep(p, p->rules->time_to_sleep);
}

void	eat(t_philosopher *p)
{
	print_message(p, "is eating");
	pthread_mutex_lock(p->meals);
	*p->eats = 1;
	gettimeofday(&p->last_meal, NULL);
	pthread_mutex_unlock(p->meals);
	pthread_mutex_lock(p->rules->meal);
	p->rules->each_philosopher_has_eaten[p->id]++;
	pthread_mutex_unlock(p->rules->meal);
	ft_usleep(p, p->rules->time_to_eat);
	pthread_mutex_unlock(p->rfork);
	pthread_mutex_unlock(p->lfork);
	pthread_mutex_lock(p->meals);
	*p->eats = 0;
	pthread_mutex_unlock(p->meals);
}

void	*routine(void *arg)
{
	t_philosopher	*p;

	p = (t_philosopher *)arg;
	if (p->rules->number_of_philosophers == 1)
		return (NULL);
	thinking(p);
	while (!atleat_one_dead(p))
	{
		grap_forks(p);
		eat(p);
		sleep_time(p);
		thinking(p);
	}
	return (NULL);
}
