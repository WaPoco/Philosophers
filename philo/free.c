/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpogorel <vpogorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 11:41:40 by vpogorel          #+#    #+#             */
/*   Updated: 2025/05/14 18:05:42 by vpogorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_after_meals(int i, t_rules *rules, t_philosopher *philos, 
		pthread_t *philos_monitor)
{
	free_philos_meals(i, philos);
	free_philos(rules, philos, philos_monitor);
}

void	free_after_eats(int i, t_rules *rules, t_philosopher *philos, 
		pthread_t *philos_monitor)
{
	free_philos_eats(i, philos);
	free_philos(rules, philos, philos_monitor);
}

void	free_philos_meals(int i, t_philosopher *philos)
{
	int	n;

	n = 0;
	while (n < i)
		free(philos[n++].meals);
}

void	free_philos_eats(int i, t_philosopher *philos)
{
	int	n;

	n = 0;
	while (n < i)
		free(philos[n++].eats);
}

void	free_philos(t_rules *rules, t_philosopher *philos, 
		pthread_t *philos_monitor)
{
	if (rules)
	{
		free(rules->each_philosopher_has_eaten);
		free(rules->dead);
		free(rules->print);
		free(rules->dead_lock);
		free(rules->meal);
		free(rules->forks);
		free(rules);
	}
	if (philos)
		free(philos);
	if (philos_monitor)
		free(philos_monitor);
}
