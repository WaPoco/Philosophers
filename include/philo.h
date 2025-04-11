/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpogorel <vpogorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 12:41:23 by vpogorel          #+#    #+#             */
/*   Updated: 2025/04/11 15:16:35 by vpogorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <stdio.h>
#include <pthread.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct rules
{
	int	number_of_philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_of_times_each_philosopher_must_eat;
} t_rules;

typedef struct philosopher 
{
	int	id;
    int	lfork;
	int	rfork;
	int eat;
	int wait;
	struct timeval start;
	struct timeval end;
	pthread_t philo;
	t_rules	*rules;
} t_philosopher;
