/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpogorel <vpogorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 19:51:17 by vpogorel          #+#    #+#             */
/*   Updated: 2025/05/13 14:09:55 by vpogorel         ###   ########.fr       */
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

int	alloc_all(t_philosopher *philos, pthread_t *philos_monitor, t_rules *rules)
{
	rules->each_philosopher_has_eaten = malloc(sizeof(int) * rules->number_of_philosophers);
	rules->dead = malloc(sizeof(int));
	rules->print = malloc(sizeof(pthread_mutex_t));
	rules->dead_lock = malloc(sizeof(pthread_mutex_t));
	rules->meal = malloc(sizeof(pthread_mutex_t));
	rules->forks = malloc(sizeof(pthread_mutex_t) * rules->number_of_philosophers);
	if (!rules->each_philosopher_has_eaten || !rules->dead || !philos 
		|| !philos_monitor || !rules->print || !rules->dead_lock
		|| !rules->meal || !rules->forks)
	{
		printf("Error allocation");
		free_all(rules, philos, philos_monitor);
		return (0);
	}
	memset(rules->each_philosopher_has_eaten, 0, sizeof(int) * rules->number_of_philosophers);
	*rules->dead = 0;
	return (1);
}

void    init_locks(t_rules *rules)
{
    pthread_mutex_init(rules->print, NULL);
    pthread_mutex_init(rules->dead_lock, NULL);
    pthread_mutex_init(rules->meal, NULL);
}

int	create_threads(t_rules *rules, t_philosopher *philos, pthread_t *philos_monitor)
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
		philos[i].rfork = &rules->forks[(i + rules->number_of_philosophers - 1) % rules->number_of_philosophers];
		if (pthread_create(&philos_monitor[i], NULL, monitore, (void *)&philos[i]) != 0 
			|| pthread_create(&philos[i].philo, NULL, routine, (void *)&philos[i]) != 0)
			{
				printf("Error creating threads!\n");
				destroy_all(rules, philos, philos_monitor);
				free_all(rules, philos, philos_monitor);
				return (0);
			}
		i++;
	}
	return (1);
}

int	join_all_threads(t_rules *rules, t_philosopher *philos, pthread_t *philos_monitor)
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
