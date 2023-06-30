/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleitner <mleitner@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 18:24:22 by mleitner          #+#    #+#             */
/*   Updated: 2023/06/30 14:07:14 by mleitner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

//helper to check if philo have eaten all meals
//(if specified as argument)
static void	eat_check(t_philo *philo, t_rules *rules)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&rules->lock_eat);
	while (rules->eat_n && i < rules->phil_n && \
			philo[i].meals >= rules->eat_n)
		i++;
	pthread_mutex_unlock(&rules->lock_eat);
	if (i == rules->phil_n)
	{
		pthread_mutex_lock(&philo->rules->lock_stop_all_eat);
		rules->all_eat = 1;
		pthread_mutex_unlock(&philo->rules->lock_stop_all_eat);
	}
}

static int	status_helper(t_rules *rules)
{
	int	i;

	i = rules->stop;
	pthread_mutex_unlock(&rules->lock_stop_all_eat);
	return (i);
}

//checks continuously if threads are alive or have eaten as required
void	status_check(t_philo *philo, t_rules *rules)
{
	int	i;

	while (!rules->all_eat)
	{
		i = 0;
		pthread_mutex_lock(&rules->lock_stop_all_eat);
		while (i < rules->phil_n && !rules->stop)
		{
			pthread_mutex_unlock(&rules->lock_stop_all_eat);
			pthread_mutex_lock(&rules->lock_eat);
			if ((get_time() - philo[i].last_eaten) >= (uint64_t) rules->die)
			{
				print_status("died\n", philo + i, 0);
				rules->stop = 1;
			}
			pthread_mutex_unlock(&rules->lock_eat);
			i++;
			pthread_mutex_lock(&rules->lock_stop_all_eat);
		}
		if (status_helper(rules))
			break ;
		eat_check(philo, rules);
	}
}

//spins down all threads, destroys mutexes and frees structs
void	thread_kill(t_philo *philo, t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->phil_n)
	{
		pthread_join(philo[i].tid, NULL);
		i++;
	}
	while (i < rules->phil_n)
		pthread_mutex_destroy(&rules->forks[i++]);
	pthread_mutex_destroy(&rules->lock_eat);
	pthread_mutex_destroy(&rules->lock_print);
	pthread_mutex_destroy(&rules->lock_stop_all_eat);
	free(philo);
	free(rules->forks);
	free(rules->forks_val);
}

//starts all threads, initializes status check, which runs
//until one philosopher dies or all have eaten and then exits
//all threads, returns 1 on success, 0 on failure
int	thread_start(t_philo *philo)
{
	int	i;

	i = 0;
	philo->rules->start_time = get_time();
	while (i < philo->rules->phil_n)
	{
		philo[i].last_eaten = philo->rules->start_time;
		if (pthread_create(&philo[i].tid, NULL, \
		do_philo, &philo[i]))
			return (0);
		i++;
	}
	status_check(philo, philo->rules);
	pthread_mutex_unlock(&philo->rules->lock_print);
	thread_kill(philo, philo->rules);
	return (1);
}
