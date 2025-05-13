/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilis.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpogorel <vpogorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:09:41 by vpogorel          #+#    #+#             */
/*   Updated: 2025/05/13 16:57:13 by vpogorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	atleat_one_dead(t_philosopher *p)
{
	pthread_mutex_lock(p->rules->dead_lock);
	if (*p->rules->dead == 1)
		return (pthread_mutex_unlock(p->rules->dead_lock), 1);
	pthread_mutex_unlock(p->rules->dead_lock);
	return (0);
}

void	print_message(t_philosopher *p, char *text)
{
	if (!atleat_one_dead(p))
	{
		pthread_mutex_lock(p->rules->print);
		printf("%d %d %s\n", cur_time(p), p->id, text);
		pthread_mutex_unlock(p->rules->print);
	}
}

void	free_all(t_rules *rules, t_philosopher *philos, 
		pthread_t *philos_monitor)
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

void	destroy_all(t_rules *rules, t_philosopher *philos, 
			pthread_t *philos_monitor)
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

int	alloc_all(t_philosopher *philos, pthread_t *philos_monitor, t_rules *rules)
{
	rules->each_philosopher_has_eaten = malloc(sizeof(int) 
			* rules->number_of_philosophers);
	rules->dead = malloc(sizeof(int));
	rules->print = malloc(sizeof(pthread_mutex_t));
	rules->dead_lock = malloc(sizeof(pthread_mutex_t));
	rules->meal = malloc(sizeof(pthread_mutex_t));
	rules->forks = malloc(sizeof(pthread_mutex_t) 
			* rules->number_of_philosophers);
	if (!rules->each_philosopher_has_eaten || !rules->dead || !philos 
		|| !philos_monitor || !rules->print || !rules->dead_lock 
		|| !rules->meal || !rules->forks)
	{
		printf("Error allocation");
		free_all(rules, philos, philos_monitor);
		return (0);
	}
	memset(rules->each_philosopher_has_eaten, 0, sizeof(int) 
		* rules->number_of_philosophers);
	*rules->dead = 0;
	return (1);
}
