/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleitner <mleitner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 14:04:54 by mleitner          #+#    #+#             */
/*   Updated: 2023/06/13 13:02:29 by mleitner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

//modified atoi that only converts positive numbers
//illegal characters (no whitespace/number) returns -1
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
		return (-1);
	return (val);
}

//converts time from micro (millionth) to milliseconds (thousandth)
uint64_t	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == 0)
		return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
	else
		return (0);
}

//recodes usleep for more precision, sleeps for a tenth of ms time
void	ft_usleep(uint64_t time)
{
	uint64_t	start;

	start = get_time();
	usleep(time * 990);
	while (get_time() - start < time)
		usleep(time);
}
