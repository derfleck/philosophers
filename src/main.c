/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleitner <mleitner@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 18:25:11 by mleitner          #+#    #+#             */
/*   Updated: 2023/04/03 14:31:33 by mleitner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
	printf("number of philosophers: %d\ntime to die: \
	%d\ntime to eat: %d\ntime to sleep: %d\nnumber of \
	times each philosopher must eat: %d\n", rules->phil, \
	rules->ttd, rules->tte, rules->tts, rules->eat);
}
