/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleitner <mleitner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 12:55:29 by mleitner          #+#    #+#             */
/*   Updated: 2023/06/13 13:04:49 by mleitner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

static void	*monitor(void *arg)
{
	t_philo	*philo;
	t_rules	*rules;

	philo = (t_philo *)arg;
	rules = philo->rules;
	while (1)
	{
		sem_wait(rules->died);
		if (get_time() - philo->last_eaten >= (uint64_t)rules->die)
		{
			print_status(" died\n", philo);
			sem_wait(rules->print);
			exit (0);
		}
		sem_post(rules->died);
	}
	return (NULL);
}

static void	create_process(t_philo *philo)
{
	pthread_t	monitor_id;

	pthread_create(&monitor_id, NULL, monitor, (void *)philo);
	pthread_detach(monitor_id);
	do_philo(philo);
	exit(0);
}

static void	kill_processes(t_rules *rules)
{
	int		i;
	t_philo	*philo;

	philo = rules->philo;
	i = 0;
	while (i < rules->phil_n)
		kill(philo[i++].pid, SIGTERM);
}

static void	wait_processes(t_rules *rules)
{
	int	status;

	waitpid(-1, &status, 0);
	if (WIFEXITED(status) || WIFSIGNALED(status))
		kill_processes(rules);
}

int	process_start(t_rules *rules)
{
	int	i;

	i = 0;
	//if (rules->eat_n > 0)
	//	meal_checker(rules);
	rules->start_time = get_time();
	while (i < rules->phil_n)
	{
		rules->philo[i].last_eaten = rules->start_time;
		rules->philo[i].pid = fork();
		if (rules->philo[i].pid == -1)
			return (0);
		if (rules->philo[i].pid == 0)
			create_process(&rules->philo[i]);
		i++;
		ft_usleep(1);
	}
	wait_processes(rules);
	return (1);
}