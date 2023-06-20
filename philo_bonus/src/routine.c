/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleitner <mleitner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 13:00:14 by mleitner          #+#    #+#             */
/*   Updated: 2023/06/20 19:10:12 by mleitner         ###   ########.fr       */
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

//calculates think time based of remaining time to survive
void	think(t_philo *philo)
{
	time_t 	think_time;
	t_rules	*rules;
	time_t	live_time;

	rules = philo->rules;
	sem_wait(philo->philo_sem);
	live_time = (time_t)(get_time() - philo->last_eaten);
	think_time = (rules->die - live_time - rules->eat) / 2;
	sem_post(philo->philo_sem);
	if (think_time <= 0)
		think_time = 0 ;
	else if (think_time > 600)
		think_time = 200;
	print_status("is thinking\n", philo);
	ft_usleep(think_time);
}

//philo takes forks and puts it back
//also increases eaten mutex if required
void	eat(t_philo *philo)
{
	t_rules *rules;

	rules = philo->rules;
	take_fork(philo);
	//sem_wait(rules->died);
	sem_wait(philo->philo_sem);
	print_status("is eating\n", philo);
	philo->last_eaten = get_time();
	philo->meals += 1;
	sem_post(philo->philo_sem);
	//sem_post(rules->died);
	ft_usleep(rules->eat);
	sem_post(rules->forks);
	sem_post(rules->forks);
	sem_wait(philo->philo_sem);
	if (rules->eat_n > 0 && philo->meals >= philo->rules->eat_n)
		sem_post(rules->eaten);
	sem_post(philo->philo_sem);
}

void	do_philo(t_philo *philo)
{
	sem_wait(philo->rules->barrier_mutex);
	if (philo->rules->phil_n > 1 && (philo->num + 1) % 2)
	{
		print_status("is thinking\n", philo);
		ft_usleep(philo->rules->eat);
	}
	while (1)
	{
		eat(philo);
		print_status("is sleeping\n", philo);
		ft_usleep(philo->rules->sleep);
		think(philo);
	}
}
