/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpogorel <vpogorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 19:50:08 by vpogorel          #+#    #+#             */
/*   Updated: 2025/05/06 19:50:14 by vpogorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void thinking(t_philosopher *p)
{
    pthread_mutex_lock(p->rules->print);
    //printf("%d %d is thinking and last meal %d and eats=%d\n", cur_time(p), p->id, last_meal_time(p), *p->eats);
    printf("%d %d is thinking \n", cur_time(p), p->id);
    pthread_mutex_unlock(p->rules->print);
}

void sleep_time(t_philosopher *p)
{
    pthread_mutex_lock(p->rules->print);
    //printf("%d %d is sleeping and last meal %d and eats=%d\n", cur_time(p), p->id, last_meal_time(p), *p->eats);
    printf("%d %d is sleeping\n", cur_time(p), p->id);
    pthread_mutex_unlock(p->rules->print);
    ft_usleep(p->rules->time_to_sleep);
}

void eat(t_philosopher *p)
{
    pthread_mutex_lock(p->meals);
    *p->eats = 1;
    gettimeofday(&p->last_meal, NULL);
    p->rules->each_philosopher_has_eaten[p->id]++;
    pthread_mutex_unlock(p->meals);
    pthread_mutex_lock(p->rules->print);
    //printf("%d %d is eating and last meal %d and eats=%d\n", cur_time(p), p->id, last_meal_time(p), *p->eats);
    printf("%d %d is eating meals=%d\n", cur_time(p), p->id, p->rules->each_philosopher_has_eaten[p->id]);
    pthread_mutex_unlock(p->rules->print);

    ft_usleep(p->rules->time_to_eat);

    pthread_mutex_unlock(p->rfork);
    pthread_mutex_unlock(p->lfork);
    
    pthread_mutex_lock(p->meals);
    *p->eats = 0;
    pthread_mutex_unlock(p->meals);
}

void grap_fork(t_philosopher *p, pthread_mutex_t *fork)
{
    pthread_mutex_lock(fork);
    pthread_mutex_lock(p->rules->print);
    //printf("%d %d has taken a fork and last meal %d and eats=%d \n", cur_time(p), p->id, last_meal_time(p), *p->eats);
    printf("%d %d has taken a fork\n", cur_time(p), p->id);
    pthread_mutex_unlock(p->rules->print);
}

void grap_forks(t_philosopher *p)
{
    grap_fork(p, p->rfork);
    grap_fork(p, p->lfork);
}

void *routine(void *arg)
{
    t_philosopher *p;

    p = (t_philosopher *)arg;
    if (p->id % 2 == 0)
        ft_usleep(10);

    thinking(p);
    while (1)
    {
        grap_forks(p);
        eat(p);
        sleep_time(p);
        thinking(p);
    }
    return (NULL);
}