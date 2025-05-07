/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpogorel <vpogorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 19:51:17 by vpogorel          #+#    #+#             */
/*   Updated: 2025/05/07 18:55:36 by vpogorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

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

t_philosopher *init_philo(int arg0, char **args)
{
    t_philosopher *philos;
    pthread_t *philos_monitor;
    t_rules *rules;
    int i;

    i = 0;
    rules = read_input(arg0, args);
    rules->each_philosopher_has_eaten = malloc(sizeof(int) * rules->number_of_philosophers);
    memset(rules->each_philosopher_has_eaten, 0, sizeof(int) * rules->number_of_philosophers);
    if (!rules)
    {
        printf("Error!");
        return (philos);
    }
    rules->dead = malloc(sizeof(int));
    *rules->dead = 0;
    init_forks(rules->forks, rules->number_of_philosophers);
    philos = malloc(sizeof(t_philosopher) * rules->number_of_philosophers);
    if (!philos)
        return (philos);
    philos_monitor = malloc(sizeof(pthread_t) * rules->number_of_philosophers);
    rules->print = malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init(rules->print, NULL);
    gettimeofday(&rules->start, NULL);
    rules->dead_lock = malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init(rules->dead_lock, NULL);
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
        pthread_create(&philos_monitor[i], NULL, monitore, (void *)&philos[i]);
        pthread_create(&philos[i].philo, NULL, routine, (void *)&philos[i]);
        i++;
    }
    i = 0;
    while (i < rules->number_of_philosophers)
    {
        pthread_join(philos_monitor[i], NULL);
        pthread_join(philos[i].philo, NULL);
        i++;
    }
    return (philos);
}