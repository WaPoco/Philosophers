/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpogorel <vpogorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:00:36 by vpogorel          #+#    #+#             */
/*   Updated: 2025/04/20 21:20:47 by vpogorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/*
int mails = 0;
pthread_mutex_t mutex;
*/

void *routine(void *arg)
{
    t_philosopher   *p;

    p = (t_philosopher *)arg;
    if (p->id % 2 == 0)
    {
        pthread_mutex_lock(p->rfork);
        printf("Philo %d  picked up the right fork\n", p->id);
        pthread_mutex_lock(p->lfork);
        printf("Philo %d  picked up the left fork\n", p->id);
    }
    else
    {
        pthread_mutex_lock(p->lfork);
        pthread_mutex_lock(p->rfork);
    }
    sleep(3);
    pthread_mutex_unlock(p->rfork);
    pthread_mutex_unlock(p->lfork);
    printf("Philo %d  has droped the forks\n", p->id);
    /*
    while (1)
    {
        sleep(1);
        gettimeofday(&p->rules->time_to_eat, NULL);
        time = philos[1].end.tv_sec - philos[1].rules->start.tv_sec;
        printf("time %d \n", time);
        if (philos[1].rules->time_to_die == time)
            break ;
    }
    
    while (i < p->rules->number_of_philosophers)
    {
        while (d < 2)
        {
            pthread_mutex_lock(&mutex);
            if (p->id % 2 == 0)
            {
                if (d == 0)
                    p->rules->forks[(p->id + 1) % p->rules->number_of_philosophers] = p->id;
                else if (d == 1 && p->id == 0)
                    p->rules->forks[p->rules->number_of_philosophers - 1] = p->id;
                else if (d == 1 && p->id > 0)
                    p->rules->forks[p->id - 1] = p->id;
            }
            else
            {
                if (d == 1)
                    p->rules->forks[(p->id + 1) % p->rules->number_of_philosophers] = p->id;
                else if (d == 0 && p->id == 0)
                    p->rules->forks[p->rules->number_of_philosophers - 1] = p->id;
                else if (d == 0 && p->id > 0)
                    p->rules->forks[p->id - 1] = p->id;
            }
            pthread_mutex_unlock(&mutex);
        }
        i++;
    }*/
/*    while (i++ < 10)
    {
        pthread_mutex_lock(&mutex);
        mails++;
        pthread_mutex_unlock(&mutex);
    }
    return (NULL);
*/
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
    rules->number_of_times_each_philosopher_must_eat = time[4];
    free(time);
    return (rules);
}

t_philosopher   *init_philo(int arg0, char **args)
{
    t_philosopher   *philos;
    t_rules         *rules;
    int             *input_philo;
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
    gettimeofday(&rules->start, NULL);
    while (i < rules->number_of_philosophers)
    {
        philos[i].id = i;
        philos[i].rules = rules;
        pthread_create(&philos[i].philo, NULL, routine, (void *)philos[i].philo);
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
    printf("Hello, I'am philosopher number %d and I will die in %d seconds\n", philos[1].id, philos[1].rules->time_to_die);
    while (1)
    {
        sleep(1);
        gettimeofday(&philos[1].end, NULL);
        time = philos[1].end.tv_sec - philos[1].rules->start.tv_sec;
        printf("time %d \n", time);
        if (philos[1].rules->time_to_die == time)
            break ;
    }
    gettimeofday(&philos[1].end, NULL);
    pthread_join(philos[1].philo, NULL);
    printf("Time of Philo 1 %ld seconds\n", (philos[1].end.tv_sec - philos[1].rules->start.tv_sec));
    //printf("%d \n", mails);
    /*
    t_philosopher *p1;
    t_philosopher *p2;

    pthread_mutex_init(&mutex, NULL);
    // Create the thread
    p1 = malloc(sizeof(t_philosopher));
    p2 = malloc(sizeof(t_philosopher));
    pthread_create(&p1->philo, NULL, thread_function, (void *)p1);
    pthread_create(&p2->philo, NULL, thread_function, (void *)p2);
    pthread_join(p1->philo, NULL);
    sleep(3);
    gettimeofday(&p1->end, NULL);
    pthread_join(p2->philo, NULL);
    sleep(3);
    gettimeofday(&p2->end, NULL);
    printf("mails: %d\n", mails);
    printf("Time of Philo 1 %ld\n", p1->end.tv_sec - p1->start.tv_sec);
    printf("Time of Philo 2 %ld\n", p2->end.tv_sec - p2->start.tv_sec);
    pthread_mutex_destroy(&mutex);
    */
    return (0);
}
