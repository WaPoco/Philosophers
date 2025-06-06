/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpogorel <vpogorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 12:41:23 by vpogorel          #+#    #+#             */
/*   Updated: 2025/05/07 18:18:07 by vpogorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <stdio.h>
#include <pthread.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

typedef struct rules
{
	int	number_of_philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_of_times_each_philosopher_must_eat;
	int	*each_philosopher_has_eaten;
	int	*dead;
	struct timeval start;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*print;
	pthread_mutex_t *dead_lock;
} t_rules;

typedef struct philosopher 
{
	int	id;
	pthread_mutex_t	*lfork;
	pthread_mutex_t	*rfork;
	pthread_mutex_t	*meals;
	struct timeval end;
	struct timeval last_meal;
	pthread_t philo;
	t_rules	*rules;
	int	*eats;
} t_philosopher;



// time 
int last_meal_time(t_philosopher *p);
int	get_current_time(void);
int cur_time(t_philosopher *p);
int	ft_usleep(t_philosopher *p, int milliseconds);

// routine 
void thinking(t_philosopher *p);
void sleep_time(t_philosopher *p);
void eat(t_philosopher *p);
void grap_fork(t_philosopher *p, pthread_mutex_t *fork);
void grap_forks(t_philosopher *p);
void *routine(void *arg);
int  atleat_one_dead(t_philosopher *p);
void print_message(t_philosopher *p, char *text);

// monitore 
int  check_and_simulation(t_philosopher *p);
void *monitore(void *arg);

// check and read input
t_rules *read_input(int arg0, char **args);
int check_number(char *arg);

// init philos
void	init_forks(pthread_mutex_t *forks, int philo_num);
t_philosopher *init_philo(int arg0, char **args);




