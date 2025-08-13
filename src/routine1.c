/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpogorel <vpogorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:51:03 by vpogorel          #+#    #+#             */
/*   Updated: 2025/08/13 17:51:18 by vpogorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	grap_fork(t_philosopher *p, pthread_mutex_t *fork)
{
	pthread_mutex_lock(fork);
	print_message(p, "has taken a fork");
}

void	grap_forks(t_philosopher *p)
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
