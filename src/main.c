/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleitner <mleitner@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 18:25:11 by mleitner          #+#    #+#             */
/*   Updated: 2023/04/03 17:33:56 by mleitner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*print_test(void *tmp)
{
	(void)tmp;
	printf("test");
	return (NULL);
}

t_philo	init_philos(t_rules *rules, int n)
{
	t_philo	tmp;

	tmp.eaten = 0;
	tmp.rules = rules;
	tmp.state = 1;
	if (n % 2 == 0)
	{
		tmp.forks[0] = 1;
		tmp.forks[1] = 1;
	}
	else
	{
		tmp.forks[0] = 0;
		tmp.forks[0] = 0;
	}
	tmp.last_eaten = get_time();
	pthread_create(&tmp.tid, NULL, print_test, NULL);
	return (tmp);
}

t_philo	*create_philos(t_rules *rules)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = malloc(sizeof(t_philo) * rules->phil_n);
	while (i < rules->phil_n)
	{
		philo[i] = init_philos(rules, i + 1);
		i++;
	}
	return (philo);
}

int	main(int argc, char **argv)
{
	t_rules			*rules;

	if (argc < 5 || argc > 6)
	{
		printf("Error: Please provide four or five arguments.\n");
		return (0);
	}
	rules = set_rules(argc, argv);
	if (!rules)
		return (0);
	create_philos(rules);
	//printf("number of philosophers: %d\ntime to die: \
	//%d\ntime to eat: %d\ntime to sleep: %d\nnumber of \
	//times each philosopher must eat: %d\n", rules->phil_n, \
	//rules->ttd, rules->tte, rules->tts, rules->eat);
	return (0);
}
