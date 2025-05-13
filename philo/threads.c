/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpogorel <vpogorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:41:05 by vpogorel          #+#    #+#             */
/*   Updated: 2025/05/13 16:57:48 by vpogorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_monitors_philos(t_rules *rules, t_philosopher *philos, 
		pthread_t *philos_monitor, int i)
{
	if (pthread_create(&philos_monitor[i], NULL, 
			monitore, (void *)&philos[i]) != 0 
		|| pthread_create(&philos[i].philo, NULL, 
			routine, (void *)&philos[i]) != 0)
	{
		printf("Error creating threads!\n");
		destroy_all(rules, philos, philos_monitor);
		free_all(rules, philos, philos_monitor);
		return (0);
	}
	return (1);
}

int	create_threads(t_rules *rules, t_philosopher *philos, 
		pthread_t *philos_monitor)
{
	int	i;

	i = 0;
	while (i < rules->number_of_philosophers)
	{
		philos[i].last_meal = rules->start;
		philos[i].id = i;
		philos[i].rules = rules;
		philos[i].eats = malloc(sizeof(int));
		philos[i].meals = malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(philos[i].meals, NULL);
		*philos[i].eats = 0;
		philos[i].lfork = &rules->forks[i];
		philos[i].rfork = &rules->forks[(i + rules->number_of_philosophers - 1) 
			% rules->number_of_philosophers];
		if (!create_monitors_philos(rules, philos, philos, i))
			return (0);
		i++;
	}
	return (1);
}

int	join_all_threads(t_rules *rules, t_philosopher *philos, 
	pthread_t *philos_monitor)
{
	int		i;

	i = 0;
	while (i < rules->number_of_philosophers)
	{
		if (pthread_join(philos_monitor[i], NULL) != 0
			|| pthread_join(philos[i].philo, NULL) != 0)
		{
			printf("Error joining threads!\n");
			return (0);
		}
		i++;
	}
	destroy_all(rules, philos, philos_monitor);
	free_all(rules, philos, philos_monitor);
	return (1);
}
