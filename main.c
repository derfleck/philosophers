/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleitner <mleitner@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 18:25:11 by mleitner          #+#    #+#             */
/*   Updated: 2023/03/31 17:55:49 by mleitner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

typedef struct s_rules{
	int	phil;
	int	ttd;
	int	tte;
	int	tts;
	int	eat;
}	t_rules;

long	ft_atoi(char *s)
{
	unsigned int	i;
	long			val;

	i = 0;
	val = 0;
	while (s[i] && s[i] == 32)
		i++;
	while (s[i] >= '0' && s[i] <= '9' && s[i])
	{
		val *= 10;
		val += (s[i] - 48);
		i++;
		if (val > 2147483648)
			return (0);
	}
	while (s[i] && s[i] == 32)
		i++;
	if ((s[i] < '0' || s[i] > '9') && s[i])
		return (0);
	return (val);
}

t_rules	*set_rules(int argc, char **argv)
{
	t_rules			*rules;

	rules = malloc(sizeof(t_rules));
	rules->phil = ft_atoi(argv[1]);
	rules->ttd = ft_atoi(argv[2]);
	rules->tte = ft_atoi(argv[3]);
	rules->tts = ft_atoi(argv[4]);
	if (argc == 5)
		rules->eat = 0;
	else
		rules->eat = ft_atoi(argv[5]);
	if (rules->phil > 200 || !(rules->phil || \
	rules->ttd || rules->tte || rules->tts))
	{
		printf("Error: Exceeded range for values.\n");
		free (rules);
		return (NULL);
	}
	return (rules);
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
	printf("number of philosophers: %d\ntime to die: %d\ntime to eat: %d\ntime to sleep: %d\nnumber of times each philosopher must eat: %d\n", rules->phil, rules->ttd, rules->tte, rules->tts, rules->eat);
}
