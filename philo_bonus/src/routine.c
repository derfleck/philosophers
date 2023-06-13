/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleitner <mleitner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 13:00:14 by mleitner          #+#    #+#             */
/*   Updated: 2023/06/13 13:01:17 by mleitner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	print_status(char *str, t_philo *philo)
{
	sem_wait(philo->rules->print);
	printf("%ld %d %s", get_time() - philo->rules->start_time, \
		philo->num + 1, str);
	sem_post(philo->rules->print);
}

void	take_fork(t_philo *philo)
{
	sem_wait(philo->rules->forks);
	print_status("has taken a fork\n", philo);
	sem_wait(philo->rules->forks);
	print_status("has taken a fork\n", philo);
}

void	eat(t_philo *philo)
{
	t_rules *rules;

	rules = philo->rules;
	take_fork(philo);
	sem_wait(rules->died);
	print_status("is eating\n", philo);
	philo->last_eaten = get_time();
	philo->meals += 1;
	if (rules->eat_n > 0 && philo->meals >= philo->rules->eat_n)
		sem_post(rules->eaten);
	sem_post(rules->died);
	ft_usleep(rules->eat);
	sem_post(rules->forks);
	sem_post(rules->forks);
}

void	do_philo(t_philo *philo)
{
	while (1)
	{
		eat(philo);
		print_status("is sleeping\n", philo);
		ft_usleep(philo->rules->sleep);
		print_status("is thinking\n", philo);
	}
}
