/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpogorel <vpogorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:00:36 by vpogorel          #+#    #+#             */
/*   Updated: 2025/04/05 16:09:57 by vpogorel         ###   ########.fr       */
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

int main(int arg0, char **args)
{
    t_philosopher *p1;
    t_philosopher *p2;

    pthread_mutex_init(&mutex, NULL);
    // Create the thread
    p1 = malloc(sizeof(t_philosopher));
    p2 = malloc(sizeof(t_philosopher));
    pthread_create(&p1->philo, NULL, thread_function, (void *)p1);
    pthread_create(&p2->philo, NULL, thread_function, (void *)p2);
    pthread_join(p1->philo, NULL);
    sleep(1);
    gettimeofday(&p1->end, NULL);
    pthread_join(p2->philo, NULL);
    sleep(3);
    gettimeofday(&p2->end, NULL);
    printf("mails: %d\n", mails);
    printf("Time of Philo 1 %ld\n", p1->end.tv_sec - p1->start.tv_sec);
    printf("Time of Philo 2 %ld", p2->end.tv_sec - p2->start.tv_sec);
    pthread_mutex_destroy(&mutex);
    return (0);
}
