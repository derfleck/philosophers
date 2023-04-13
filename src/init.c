/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleitner <mleitner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 16:39:36 by mleitner          #+#    #+#             */
/*   Updated: 2023/04/12 10:02:54 by mleitner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	thread_start(t_philo *philo)
{
	int	i;

	i = 0;
	philo->rules->start_time = get_time();
	while (i < philo->rules->phil_n)
	{
		pthread_create(&philo[i].tid, NULL, &do_philo, &philo[i]);
		philo[i].last_eaten = philo->rules->start_time;
		i++;
		//ft_usleep(1);
	}
	i = 0;
	while (i < philo->rules->phil_n)
	{
		pthread_join(philo[i].tid, NULL);
		i++;
	}
}

void	take_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	printf("%ld %d has taken a fork\n", get_time() - philo->rules->start_time, philo->num);
	pthread_mutex_lock(philo->l_fork);
	printf("%ld %d has taken a fork\n", get_time() - philo->rules->start_time, philo->num);
}

void	drop_fork(t_philo *philo)
{
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_lock(&philo->lock);
	philo->state = 3;
	pthread_mutex_unlock(&philo->lock);
	printf("%ld %d is sleeping\n", get_time() - philo->rules->start_time, philo->num);
	ft_usleep(philo->rules->sleep);
}

void	eat(t_philo *philo)
{
	if (philo->state && get_time() <= philo->last_eaten + philo->rules->die)
	{
		take_fork(philo);
		pthread_mutex_lock(&philo->lock);
		philo->state = 2;
		pthread_mutex_unlock(&philo->lock);
		philo->last_eaten = get_time();
		printf("%ld %d is eating\n", philo->last_eaten - philo->rules->start_time, philo->num);
		ft_usleep(philo->rules->eat);
		drop_fork(philo);
	}
}

void	*lifeguard(void *arg)
{
	t_philo		*philo;

	philo = (t_philo*) arg;
	pthread_mutex_lock(&philo->lock);
	while (philo->state && get_time() < philo->last_eaten + philo->rules->die)
	{
		//printf("P%d: state %d\n", philo->num, philo->state);
		if (get_time() >= (philo->last_eaten + philo->rules->die) && philo->state != 2)
		{
			//pthread_mutex_lock(&philo->lock);
			philo->state = 0;
			//pthread_mutex_unlock(&philo->lock);
			printf("%ld %d died\n", get_time() - philo->rules->start_time, philo->num);
			return NULL;
		}
		ft_usleep(1);
	}
	pthread_mutex_unlock(&philo->lock);
	return NULL;
}

void	*do_philo(void *arg)
{
	t_philo 		*philo;
	pthread_t	*t2;

	philo = (t_philo*) arg;
	t2 = malloc(sizeof(pthread_t));
	pthread_create(t2, NULL, lifeguard, philo);
	while (philo->state > 0)
	{
		//if (get_time() > (philo->last_eaten + philo->rules->die))
		//{
		//	printf("%ld %d died\n", get_time() - philo->rules->start_time, philo->num);
		//	break ;
		//}
		if (philo->state > 0 && get_time() < philo->last_eaten + philo->rules->die)
		{
			printf("%ld %d is thinking\n", get_time() - philo->rules->start_time, philo->num);
			pthread_mutex_lock(&philo->lock);
			philo->state = 1;
			pthread_mutex_unlock(&philo->lock);
			eat(philo);
		}
	}
	pthread_join(*t2, NULL);
	return NULL;
}

t_philo	init_philos(t_rules *rules, int n, pthread_mutex_t *forks)
{
	t_philo	tmp;

	tmp.num = n;
	tmp.meals = 0;
	tmp.rules = rules;
	tmp.state = 1;
	tmp.r_fork = forks + (n % rules->phil_n);
	tmp.l_fork = forks + ((n + 1) % rules->phil_n);
	tmp.last_eaten = get_time();
	pthread_mutex_init(&tmp.lock, NULL);
	return (tmp);
}

pthread_mutex_t *init_forks(t_rules *rules)
{
	int 			i;
	pthread_mutex_t	*forks;

	i = 0;
	forks = malloc(sizeof(pthread_mutex_t) * rules->phil_n);
	if (!forks)
		return (NULL);
	while (i < rules->phil_n)
	{
		pthread_mutex_init(forks + i, NULL);
		i++;
	}
	return (forks);
}

t_philo	*create_philos(t_rules *rules)
{
	t_philo			*philo;
	pthread_mutex_t *forks;
	int				i;

	i = 0;
	philo = malloc(sizeof(t_philo) * rules->phil_n);
	forks = init_forks(rules);
	while (i < rules->phil_n)
	{
		philo[i] = init_philos(rules, i, forks);
		i++;
	}
	thread_start(philo);
	return (philo);
}