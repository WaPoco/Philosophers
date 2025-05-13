/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilis.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpogorel <vpogorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:09:41 by vpogorel          #+#    #+#             */
/*   Updated: 2025/05/13 12:33:24 by vpogorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_all(t_rules *rules, t_philosopher *philos, pthread_t *philos_monitor)
{
	if (!rules->each_philosopher_has_eaten)
		free(rules->each_philosopher_has_eaten);
	if (!rules->dead)
		free(rules->dead);
	if (!philos->eats)
		free(philos->eats);
	if (!philos)
		free(philos);
	if (!philos_monitor)
		free(philos_monitor);
	if (!rules->print)
		free(rules->print);
	if (!rules->dead_lock)
		free(rules->dead_lock);
	if (!rules->meal)
		free(rules->meal);
	if (!rules->forks)
		free(rules->forks);
	if (!rules)
		free(rules);
}

void	destroy_all(t_rules *rules, t_philosopher *philos, pthread_t *philos_monitor)
{
	int	i;

	i = 0;
	while (i < rules->number_of_philosophers)
		pthread_mutex_destroy(philos[i++].meals);
	pthread_mutex_destroy(rules->forks);
	pthread_mutex_destroy(rules->dead_lock);
	pthread_mutex_destroy(rules->meal);
	pthread_mutex_destroy(rules->print);
}
