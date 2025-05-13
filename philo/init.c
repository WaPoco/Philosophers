/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpogorel <vpogorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 19:51:17 by vpogorel          #+#    #+#             */
/*   Updated: 2025/05/13 16:41:27 by vpogorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_forks(pthread_mutex_t *forks, int philo_num)
{
	int	i;

	i = 0;
	while (i < philo_num)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

void	init_locks(t_rules *rules)
{
	pthread_mutex_init(rules->print, NULL);
	pthread_mutex_init(rules->dead_lock, NULL);
	pthread_mutex_init(rules->meal, NULL);
}

t_philosopher	*init_philo(int arg0, char **args)
{
	t_philosopher	*philos;
	pthread_t		*philos_monitor;
	t_rules			*rules;

	rules = read_input(arg0, args);
	if (!rules)
	{
		printf("Error!");
		return (NULL);
	}
	philos = malloc(sizeof(t_philosopher) * rules->number_of_philosophers);
	philos_monitor = malloc(sizeof(pthread_t) * rules->number_of_philosophers);
	if (!philos || !philos_monitor)
		return (NULL);
	if (!alloc_all(philos, philos_monitor, rules))
		return (NULL);
	init_forks(rules->forks, rules->number_of_philosophers);
	init_locks(rules);
	gettimeofday(&rules->start, NULL);
	if (!create_threads(rules, philos, philos_monitor))
		return (NULL);
	if (!join_all_threads(rules, philos, philos_monitor))
		return (NULL);
	return (philos);
}
