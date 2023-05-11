/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleitner <mleitner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 16:39:36 by mleitner          #+#    #+#             */
/*   Updated: 2023/05/11 18:54:00 by mleitner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

//initializes philosophers struct values
//only last_eaten and tid are missing
void	init_philos(t_rules *rules, pthread_mutex_t *forks)
{
	int	i;

	i = -1;
	while (++i < rules->phil_n)
	{
		rules->phil[i].num = i;
		rules->phil[i].meals = 0;
		rules->phil[i].rules = rules;
		rules->phil[i].l_fork = forks + (i % rules->phil_n);
		rules->phil[i].r_fork = forks + ((i + 1) % rules->phil_n);
	}
}

//initializes fork and rule write/print mutexes
//returns NULL if initialization fails
//TODO: add check for fail in mutex init
pthread_mutex_t	*init_forks(t_rules *rules)
{
	int				i;
	pthread_mutex_t	*forks;

	i = 0;
	forks = malloc(sizeof(pthread_mutex_t) * rules->phil_n);
	if (!forks)
		return (NULL);
	while (i < rules->phil_n)
	{
		if (pthread_mutex_init(forks + i, NULL) != 0)
			return (NULL);
		i++;
	}
	if (pthread_mutex_init(&rules->lock_eat, NULL) != 0 || \
		pthread_mutex_init(&rules->lock_print, NULL) != 0)
		return (NULL);
	return (forks);
}

int	create_philos(t_rules *rules)
{
	rules->phil = malloc(sizeof(t_philo) * rules->phil_n);
	if (!rules->phil)
		return (0);
	rules->forks = init_forks(rules);
	if (!rules->forks)
	{
		free(rules->phil);
		return (0);
	}
	init_philos(rules, rules->forks);
	if (!thread_start(rules->phil))
	{
		free(rules->phil);
		free(rules->forks);
		printf("Error when starting threads");
	}
	return (1);
}