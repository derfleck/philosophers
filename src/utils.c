/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleitner <mleitner@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 14:04:54 by mleitner          #+#    #+#             */
/*   Updated: 2023/04/03 17:27:16 by mleitner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
	rules->phil_n = ft_atoi(argv[1]);
	rules->die = ft_atoi(argv[2]);
	rules->eat = ft_atoi(argv[3]);
	rules->sleep = ft_atoi(argv[4]);
	if (argc == 5)
		rules->eat_n = 0;
	else
		rules->eat_n = ft_atoi(argv[5]);
	if (rules->phil_n > 200 || !(rules->phil_n || \
	rules->die || rules->eat || rules->sleep))
	{
		printf("Error: Exceeded range for values.\n");
		free (rules);
		return (NULL);
	}
	return (rules);
}

//converts time from micro (thousandth) to milliseconds (millionth)
uint64_t	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == 0)
		return ((tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / 1000));
	else
		return (0);
}

//recodes usleep for more precision, sleeps for a tenth of ms time
int	ft_usleep(__useconds_t time)
{
	uint64_t	start;

	start = get_time();
	while (get_time() - start < time)
	{
		usleep(time / 10);
	}
	return (0);
}
