/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleitner <mleitner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 16:39:36 by mleitner          #+#    #+#             */
/*   Updated: 2023/05/11 18:23:28 by mleitner         ###   ########.fr       */
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
		rules->phil[i].state = 1;
		rules->phil[i].rules = rules;
		rules->phil[i].l_fork = forks + (i % rules->phil_n);
		rules->phil[i].r_fork = forks + ((i + 1) % rules->phil_n);
	}
}

//initializes fork and rule write/print mutexes
//returns NULL if initialization fails
pthread_mutex_t	*init_forks(t_rules *rules)
{
	int				i;
	pthread_mutex_t	*forks;

	i = 0;
	forks = malloc(sizeof(pthread_mutex_t) * rules->phil_n);
	if (!forks)
		return (NULL);
	rules->forks = forks;
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

t_philo	*create_philos(t_rules *rules)
{
	t_philo			*philo;
	pthread_mutex_t	*forks;

	philo = malloc(sizeof(t_philo) * rules->phil_n);
	if (!philo)
		return (NULL);
	rules->phil = philo;
	forks = init_forks(rules);
	if (!forks)
	{
		free(philo);
		return (NULL);
	}
	init_philos(rules, forks);
	if (!thread_start(philo))
	{
		free(philo);
		free(forks);
		printf("Error when starting threads");
		exit (0);
	}
	return (philo);
}