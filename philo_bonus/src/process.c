/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleitner <mleitner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 12:55:29 by mleitner          #+#    #+#             */
/*   Updated: 2023/06/20 19:20:04 by mleitner         ###   ########.fr       */
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
		//sem_wait(rules->died);
		sem_wait(philo->philo_sem);
		if (get_time() - philo->last_eaten >= (uint64_t)rules->die)
		{
			print_status(" died\n", philo);
			sem_wait(rules->print);
			exit(0);
		}
		sem_post(philo->philo_sem);
		//sem_post(rules->died);
	}
	return (NULL);
}

static void create_tmp_sem(t_philo *philo)
{
	char *str;
	char *num;

	num = ft_itoa(philo->num);
	if (!num)
		return ;
	str = ft_strjoin("tmp_", num);
	free(num);
	if (!str)
		return ;
	philo->philo_sem = sem_open(str, O_CREAT, 0644, 1);
	philo->philo_str = str;
	sem_unlink(str);
}

static void	create_process(t_philo *philo)
{
	pthread_t	monitor_id;

	create_tmp_sem(philo);
	pthread_create(&monitor_id, NULL, monitor, (void *)philo);
	pthread_detach(monitor_id);
	do_philo(philo);
	if (philo->rules->philo)
		free(philo->rules->philo);
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

void	*meal_checker(void *arg)
{
	int		i;
	t_rules	*rules;

	rules = (void *)arg;
	i = 0;
	while (i < rules->phil_n)
	{
		sem_wait(rules->eaten);
		i++;
	}
	//sem_wait(rules->died);
	sem_wait(rules->print);
	exit(0);
}

//starts all processes by forking
//lifts barrier_mutex after initializing to synchronize start
int	process_start(t_rules *rules)
{
	int			i;
	pthread_t	meal_checker_id;

	i = 0;
	if (rules->eat_n > 0)
		pthread_create(&meal_checker_id, NULL, &meal_checker, (void *)rules);
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
	}
	i = 0;
	while (i++ < rules->phil_n)
		sem_post(rules->barrier_mutex);
	if (rules->eat_n > 0)
		pthread_join(meal_checker_id, NULL);
	wait_processes(rules);
	return (1);
}
