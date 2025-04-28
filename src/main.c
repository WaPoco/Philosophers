/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpogorel <vpogorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:00:36 by vpogorel          #+#    #+#             */
/*   Updated: 2025/04/28 18:53:52 by vpogorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

float   last_meal_time(t_philosopher *p, struct timeval end)
{
    float   time;
    
    gettimeofday(&end, NULL);   
    time = (end.tv_sec - p->last_meal.tv_sec) + ((end.tv_usec - p->last_meal.tv_usec) / 1000000.0);
    return (time);
}

float cur_time(t_philosopher *p, struct timeval end)
{
    float   time;
    
    gettimeofday(&end, NULL);
    time = (end.tv_sec - p->rules->start.tv_sec) + ((end.tv_usec - p->rules->start.tv_usec) / 1000000.0);
    return (time);
}

void    thinking(t_philosopher *p)
{
    pthread_mutex_lock(p->rules->print);
    printf("%f %d is thinking\n", cur_time(p, p->end), p->id);
    pthread_mutex_unlock(p->rules->print);
}

void    sleep_time(t_philosopher *p)
{
    pthread_mutex_lock(p->rules->print);
    printf("%f %d is sleeping\n", cur_time(p, p->end), p->id);
    pthread_mutex_unlock(p->rules->print);
    usleep(p->rules->time_to_sleep * 1000);
}

void    eat(t_philosopher *p)
{
    pthread_mutex_lock(p->rules->print);
    gettimeofday(&p->last_meal, NULL);
    *p->eats = 1;
    printf("%f %d is eating\n", cur_time(p, p->end), p->id);
    pthread_mutex_unlock(p->rules->print);
    usleep(p->rules->time_to_eat * 1000);
    gettimeofday(&p->last_meal, NULL);
    *p->eats = 0;
    pthread_mutex_unlock(p->rfork);
    pthread_mutex_unlock(p->lfork);
    /*
    if (p->rules->number_of_times_each_philosopher_must_eat == 0)
    {
        printf("Enough food! \n");
        exit(1);
    }*/
}

void    grap_fork(t_philosopher *p, pthread_mutex_t *fork)
{
    pthread_mutex_lock(fork);
    pthread_mutex_lock(p->rules->print);
    printf("%f %d has taken a fork\n", cur_time(p, p->end), p->id);
    pthread_mutex_unlock(p->rules->print);
}

void    grap_forks(t_philosopher *p)
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
    t_philosopher   *p;

    p = (t_philosopher *)arg;
    while (1)
    {
        grap_forks(p);
        eat(p);
        sleep_time(p);
        thinking(p);
    }
    return (NULL);
}

void    *monitore(void *arg)
{
    t_philosopher   *p;

    p = (t_philosopher *)arg;
    while (*p->eats == 0)
    {
        if ((int) (last_meal_time(p, p->end) * 1000) >= p->rules->time_to_die)
        {
            printf("%f \n", last_meal_time(p, p->end) * 1000);
            usleep(10000);
            pthread_mutex_lock(p->rules->print);
            printf("%f %d died \n", cur_time(p, p->end), p->id);
            pthread_mutex_unlock(p->rules->print);
            exit(1);
        }
        if (*p->eats == 1)
        {
            
        }
        while (*p->eats == 1)
            usleep(1000);
    }
    return (NULL);   
}

int check_number(char *arg)
{
    int i;

    i = 0;
    if (arg == NULL)
        return (0);
    while (arg[i])
    {
        if (arg[i] > '9' || arg[i] < '0')
            return (0);
        i++;
    }
    return (1);
}

t_rules *read_input(int arg0, char **args)
{
    int     i;
    int     *time;
    t_rules *rules;

    time = malloc((arg0 - 1) * sizeof(int));
    rules = malloc(sizeof(t_rules));
    rules->number_of_times_each_philosopher_must_eat = 1;
    if (!rules || !time)
        return (NULL);
    i = 1;
    while (i < arg0)
    {
        if (check_number(args[i]) == 1)
            time[i - 1] = atoi(args[i]);
        else
            return (free(time), free(rules), NULL);
        i++;
    }
    rules->number_of_philosophers = time[0];
    rules->time_to_die = time[1];
    rules->time_to_eat = time[2];
    rules->time_to_sleep = time[3];
    rules->number_of_times_each_philosopher_must_eat = time[4] * time[0];
    rules->forks = malloc(sizeof(pthread_mutex_t) * time[0]);
    free(time);
    return (rules);
}

t_philosopher   *init_philo(int arg0, char **args)
{
    t_philosopher   *philos;
    pthread_t       *philos_monitor;
    t_rules         *rules;
    int             i;

    i = 0;
    rules = malloc(sizeof(t_rules));
    if (!rules)
    {
        printf("Error!");
        return (philos);
    }
    rules = read_input(arg0, args);
    philos = malloc(sizeof(t_philosopher) * rules->number_of_philosophers);
    if (!philos)
        return (philos);
    philos_monitor = malloc(sizeof(pthread_t) * rules->number_of_philosophers);
    rules->meals = malloc(sizeof(pthread_mutex_t));
    rules->print = malloc(sizeof(pthread_mutex_t));
    gettimeofday(&rules->start, NULL);
    while (i < rules->number_of_philosophers)
    {
        gettimeofday(&philos[i].start, NULL);
        philos[i].last_meal = rules->start;
        philos[i].id = i;
        philos[i].rules = rules;
        philos[i].eats = malloc(sizeof(int));
        *philos[i].eats = 0;
        if (i == 0)
        {
            philos[i].lfork = &philos->rules->forks[rules->number_of_philosophers - 1];
            philos[i].rfork = &philos->rules->forks[0];
        }
        else
        {
            philos[i].lfork = &philos->rules->forks[i - 1];
            philos[i].rfork = &philos->rules->forks[i % rules->number_of_philosophers];
        }
            pthread_create(&philos[i].philo, NULL, routine, (void *) &philos[i]);
            pthread_create(&philos_monitor[i], NULL, monitore, (void *) &philos[i]);
        i++;
    }
    return (philos);
}

int main(int arg0, char **args)
{
    t_philosopher   *philos;
    int             time;

    time = 0;
    if (arg0 == 5 || arg0 == 6)
        philos = init_philo(arg0, args);
    else
    {
        printf("Error arguments");   
        return (1);
    }
    sleep(300);
    return (0);
}
