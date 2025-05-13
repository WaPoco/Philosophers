/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpogorel <vpogorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 19:50:08 by vpogorel          #+#    #+#             */
/*   Updated: 2025/05/09 17:03:17 by vpogorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int    atleat_one_dead(t_philosopher *p)
{
    pthread_mutex_lock(p->rules->dead_lock);
    if (*p->rules->dead == 1)
        return (pthread_mutex_unlock(p->rules->dead_lock), 1);
    pthread_mutex_unlock(p->rules->dead_lock);
    return (0);
}

void    print_message(t_philosopher *p, char *text)
{
    if (!atleat_one_dead(p))
    {
        pthread_mutex_lock(p->rules->print);
        printf("%d %d %s\n", cur_time(p), p->id, text);
        pthread_mutex_unlock(p->rules->print);
    }
}

void thinking(t_philosopher *p)
{
    print_message(p, "is thinking");
}

void sleep_time(t_philosopher *p)
{
    print_message(p, "is sleeping");
    ft_usleep(p, p->rules->time_to_sleep);
}

void eat(t_philosopher *p)
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

void grap_fork(t_philosopher *p, pthread_mutex_t *fork)
{
    pthread_mutex_lock(fork);
    print_message(p, "has taken a fork");
}

void grap_forks(t_philosopher *p)
{
    if (p->id % 2 == 0)
    {
        grap_fork(p, p->rfork);
        grap_fork(p, p->lfork);
    }
    else
    {
        grap_fork(p, p->lfork);
        grap_fork(p, p->rfork);   
    }
}

void *routine(void *arg)
{
    t_philosopher *p;

    p = (t_philosopher *)arg;
    if (p->id % 2 == 0)
        ft_usleep(p, 1);
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
