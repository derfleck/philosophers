/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleitner <mleitner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 16:39:36 by mleitner          #+#    #+#             */
/*   Updated: 2023/05/12 12:39:31 by mleitner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

//helper, only called when mutex init fails
static void	*init_error(pthread_mutex_t *forks)
{
	printf("Error initializing mutex\n");
	if (forks != NULL)
		free (forks);
	return (NULL);
}

//initializes philosophers struct values
//only last_eaten and tid are missing
//initialized in thread_start
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
pthread_mutex_t	*init_forks(t_rules *rules)
{
	int				i;
	pthread_mutex_t	*forks;

	i = 0;
	forks = malloc(sizeof(pthread_mutex_t) * rules->phil_n);
	if (!forks)
	{
		printf("Error allocating memory for forks");
		return (NULL);
	}
	while (i < rules->phil_n)
	{
		if (pthread_mutex_init(forks + i, NULL) != 0)
			return (init_error(forks));
		i++;
	}
	if (pthread_mutex_init(&rules->lock_eat, NULL) != 0 || \
		pthread_mutex_init(&rules->lock_print, NULL) != 0)
		return (init_error(forks));
	return (forks);
}

//creates philo structs and fork mutex array
//initializes all threads
//prints error messages and frees memory on failure
int	create_philos(t_rules *rules)
{
	rules->phil = malloc(sizeof(t_philo) * rules->phil_n);
	if (!rules->phil)
		return (0);
	rules->forks = init_forks(rules);
	if (!rules->forks)
	{
		free(rules->phil);
		return (1);
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
