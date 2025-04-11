/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpogorel <vpogorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:00:36 by vpogorel          #+#    #+#             */
/*   Updated: 2025/04/11 19:09:58 by vpogorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int mails = 0;
pthread_mutex_t mutex;

void *thread_function(void *arg)
{
    int             i;
    t_philosopher *p;

    i = 0;
    p = (t_philosopher *)arg;
    gettimeofday(&p->start, NULL);
    while (i++ < 1000000)
    {
        pthread_mutex_lock(&mutex);
        mails++;
        pthread_mutex_unlock(&mutex);
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
    if (!rules || !time)
        return (NULL);
    i = 0;
    while (++i < arg0)
    {
        if (check_number(args[i]) == 1)
            time[i] = atoi(args[i]);
        else
            return (free(time), free(rules), NULL);
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
        return (philos);
    rules = read_input(arg0, args);
    philos = malloc(sizeof(t_philosopher) * rules->number_of_philosophers);
    if (!philos)
        return (philos);
    while (i < rules->number_of_philosophers)
    {
        philos->id = i;
        philos->rules = rules;
        i++;
    }
    return (philos);
}

int main(int arg0, char **args)
{
    t_philosopher   *philos;

    philos = init_philo(arg0, args);
    printf("Hello, I'am philosopher number %d \n", philos[2].id);
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
