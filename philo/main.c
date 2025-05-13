/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpogorel <vpogorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:00:36 by vpogorel          #+#    #+#             */
/*   Updated: 2025/05/13 16:42:38 by vpogorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_number(char *arg)
{
	int	i;

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

t_rules	*read_input(int arg0, char **args)
{
	int			i;
	int			*time;
	t_rules		*rules;

	time = malloc(5 * sizeof(int));
	rules = malloc(sizeof(t_rules));
	if (!rules || !time)
		return (NULL);
	i = 1;
	memset(time, -1, 5 * sizeof(int));
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
	return (free(time), rules);
}

int	main(int arg0, char **args)
{
	t_philosopher	*philos;

	if (arg0 == 5 || arg0 == 6)
		philos = init_philo(arg0, args);
	else
		printf("Error arguments");
	return (0);
}
