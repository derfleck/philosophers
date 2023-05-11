/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleitner <mleitner@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 18:25:11 by mleitner          #+#    #+#             */
/*   Updated: 2023/05/11 17:59:09 by mleitner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_rules			rules;

	rules.stop = 0;
	if (argc < 5 || argc > 6)
	{
		printf("Error: Please provide four or five arguments.\n");
		return (0);
	}
	set_rules(&rules, argc, argv);
	if (!create_philos(&rules))
		printf("Error while allocating memory");
	return (0);
}
