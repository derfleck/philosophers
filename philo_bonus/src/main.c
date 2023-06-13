/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleitner <mleitner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:49:12 by mleitner          #+#    #+#             */
/*   Updated: 2023/06/13 15:31:18 by mleitner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

//creates philo structs
//initializes all threads
//prints error messages and frees memory on failure
static int	create_philos(t_rules *rules)
{
	int	i;
	
	i = -1;
	rules->philo = malloc(sizeof(t_philo) * rules->phil_n);
	if (!rules->philo)
		return (0);
	while (++i < rules->phil_n)
	{
		rules->philo[i].num = i;
		rules->philo[i].meals = 0;
		rules->philo[i].rules = rules;
	}
	return (1);
}

//fills the t_rules struct with values passed as arguments
//exits if too many philosophers or negative values
static void	check_rules(t_rules *rules, int argc, char **argv)
{
	rules->phil_n = ft_atoi(argv[1]);
	rules->die = ft_atoi(argv[2]);
	rules->eat = ft_atoi(argv[3]);
	rules->sleep = ft_atoi(argv[4]);
	if (argc == 5)
		rules->eat_n = 0;
	else
		rules->eat_n = ft_atoi(argv[5]);
	if (rules->phil_n > 200 || !(rules->phil_n || \
	rules->die || rules->eat || rules->sleep) || \
	(rules->phil_n < 0 || rules->die < 0 || rules->eat < 0 \
	|| rules->sleep < 0 || rules->eat_n < 0))
	{
		printf("Error: At least one value is out of range.\n");
		exit(1);
	}
}

static void	print_err(int status, t_rules *rules)
{
	if (status == SEM)
	{
		printf("Error creating semaphore\n");
		close_semaphore(rules);
	}
	else if (status == PHI)
	{
		printf("Error initializing philosophers\n");
		close_semaphore(rules);
		if (rules->philo)
			free(rules->philo);
	}
	else if (status == ARG)
	{
		printf("Error: Please provide four or five arguments: ");
		printf("./philo [number of philosophers] [time to die] ");
		printf("[time to eat] [time to sleep] [optional: number of times");
		printf(" each philosopher must eat]\n");
	}
	exit (1);
}

int	main(int argc, char **argv)
{
	t_rules			rules;

	if (argc < 5 || argc > 6)
		print_err(ARG, &rules);
	check_rules(&rules, argc, argv);
	if (!create_semaphore(&rules))
		print_err(SEM, &rules);
	if (!create_philos(&rules))
		print_err(PHI, &rules);
	if (!process_start(&rules))
		print_err(PRO, &rules);
	close_semaphore(&rules);
	if (rules.philo)
		free(rules.philo);
	return (0);
}
