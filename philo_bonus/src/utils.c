/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleitner <mleitner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 14:04:54 by mleitner          #+#    #+#             */
/*   Updated: 2023/06/13 17:16:22 by mleitner         ###   ########.fr       */
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

static size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len1;
	size_t	len2;
	size_t	i;
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	str = malloc((sizeof(char *) * (len1 + len2)) + 1);
	if (!str)
		return (0);
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[i - len1] != '\0')
	{
		str[i] = s2[i - len1];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static int	ft_checklen(int n)
{
	int		len;

	len = 0;
	if (n < 0)
	{
		len++;
		n = -n;
	}
	else if (n == 0)
		return (1);
	while (n > 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

static char	*ft_except(char *s, int n)
{
	char	*str;
	int		i;

	i = 0;
	str = malloc((sizeof(char) * (n + 1)));
	while (s[i] != '\0')
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static int	ft_sign(int n, char *str)
{
	if (n < 0)
	{
		*str = '-';
		return (-n);
	}
	return (n);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;
	int		div;

	if (n == -2147483648)
		return (ft_except("-2147483648", 11));
	else if (n == 0)
		return (ft_except("0", 1));
	div = n;
	len = ft_checklen(n);
	str = malloc((sizeof(char) * (len + 1)));
	if (!str)
		return (0);
	n = ft_sign(n, str);
	str[len] = '\0';
	while (n > 0)
	{
		div = n % 10;
		n = n / 10;
		str[--len] = div + 48;
	}
	return (str);
}
