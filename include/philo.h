/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpogorel <vpogorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 12:41:23 by vpogorel          #+#    #+#             */
/*   Updated: 2025/04/05 15:49:01 by vpogorel         ###   ########.fr       */
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
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
} t_rules;

typedef struct philosopher 
{
    int	fork;
	struct timeval start;
	struct timeval end;
	pthread_t philo;
} t_philosopher;
