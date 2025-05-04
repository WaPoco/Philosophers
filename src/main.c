/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpogorel <vpogorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:00:36 by vpogorel          #+#    #+#             */
/*   Updated: 2025/05/04 10:17:49 by vpogorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int last_meal_time(t_philosopher *p)
{
    struct timeval end;
    gettimeofday(&end, NULL);
    return (end.tv_sec - p->last_meal.tv_sec) * 1000
        + ((end.tv_usec - p->last_meal.tv_usec) / 1000);
}

int	get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int cur_time(t_philosopher *p)
{
    struct timeval end;
    gettimeofday(&end, NULL);
    return (end.tv_sec - p->rules->start.tv_sec) * 1000
        + ((end.tv_usec - p->rules->start.tv_usec) / 1000);
}

int	ft_usleep(int milliseconds)
{
	int	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(100);
	return (0);
}

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
    pthread_mutex_unlock(p->meals);

    pthread_mutex_lock(p->rules->print);
    //printf("%d %d is eating and last meal %d and eats=%d\n", cur_time(p), p->id, last_meal_time(p), *p->eats);
    printf("%d %d is eating\n", cur_time(p), p->id);
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
        ft_usleep(200);

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

void *monitore(void *arg)
{
    t_philosopher *p;

    p = (t_philosopher *)arg;
    while (1)
    {
        if ((last_meal_time(p) >= p->rules->time_to_die) && (*p->eats == 0))
        {
            pthread_mutex_lock(p->rules->print);
            printf("%d %d died\n", cur_time(p), p->id);
            pthread_mutex_unlock(p->rules->print);
            exit(1);
        }
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
    int i;
    int *time;
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
    if (!rules)
    {
        printf("Error!");
        return (philos);
    }
    init_forks(rules->forks, rules->number_of_philosophers);
    philos = malloc(sizeof(t_philosopher) * rules->number_of_philosophers);
    if (!philos)
        return (philos);
    philos_monitor = malloc(sizeof(pthread_t) * rules->number_of_philosophers);
    rules->print = malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init(rules->print, NULL);
    gettimeofday(&rules->start, NULL);
    while (i < rules->number_of_philosophers)
    {
        gettimeofday(&philos[i].start, NULL);
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
    return (philos);
}

int main(int arg0, char **args)
{
    t_philosopher *philos;

    if (arg0 == 5 || arg0 == 6)
        philos = init_philo(arg0, args);
    else
    {
        printf("Error arguments");
        return (1);
    }
    sleep(3000);
    return (0);
}
