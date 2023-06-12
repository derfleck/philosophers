/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleitner <mleitner@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 18:25:11 by mleitner          #+#    #+#             */
/*   Updated: 2023/05/12 12:50:22 by mleitner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	main(int argc, char **argv)
{
	t_rules			rules;

	rules.stop = 0;
	rules.all_eat = 0;
	if (argc < 5 || argc > 6)
	{
		printf("Error: Please provide four or five arguments: ");
		printf("./philo [number of philosophers] [time to die] ");
		printf("[time to eat] [time to sleep] [optional: number of times");
		printf(" each philosopher must eat]\n");
		return (0);
	}
	set_rules(&rules, argc, argv);
	if (!create_philos(&rules))
		printf("Error while allocating memory\n");
	return (0);
}
