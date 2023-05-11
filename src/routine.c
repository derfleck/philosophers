/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleitner <mleitner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 18:26:18 by mleitner          #+#    #+#             */
/*   Updated: 2023/05/11 18:26:22 by mleitner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

//locks environment for philosopher, so only one can print status at a time
//if status is set to 0, no philosopher can print anymore
//(only used when philo died)
void	print_status(char *str, t_philo *philo, int status)
{
	pthread_mutex_lock(&philo->rules->lock_print);
	if (!philo->rules->stop)
		printf("%ld %d %s", get_time() - philo->rules->start_time, philo->num, str);
	if (status)
		pthread_mutex_unlock(&philo->rules->lock_print);
}

void	take_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	print_status("has taken a fork\n", philo, 1);
	pthread_mutex_lock(philo->r_fork);
	print_status("has taken a fork\n", philo, 1);
}

void	eat(t_philo *philo)
{
	take_fork(philo);
	pthread_mutex_lock(&philo->rules->lock_eat);
	print_status("is eating\n", philo, 1);
	philo->last_eaten = get_time();
	pthread_mutex_unlock(&philo->rules->lock_eat);
	ft_usleep(philo->rules->eat);
	philo->meals++;
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}

//routine for thread, only stops if philosopher dies
//or if all required meals are eaten
void	*do_philo(void *arg)
{
	t_philo		*philo;
	t_rules		*rules;

	philo = (t_philo *) arg;
	rules = philo->rules;
	if (philo->num % 2 && rules->phil_n > 1)
		ft_usleep(rules->eat / 100);
	while (!rules->stop)
	{
		eat(philo);
		print_status("is sleeping \n", philo, 1);
		ft_usleep(rules->sleep);
		print_status("is thinking\n", philo, 1);
	}
	return (NULL);
}