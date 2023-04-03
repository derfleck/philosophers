/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleitner <mleitner@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 17:51:50 by mleitner          #+#    #+#             */
/*   Updated: 2023/04/03 19:30:02 by mleitner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philosophers.h"

typedef struct s_test {
	pthread_mutex_t	mutex;
	int				n;
}	t_test;

void	*test_thread(void *tmp)
{
	t_test	*arr;
	int		i;

	i = 0;
	arr = (t_test *) tmp;
	while (i < 100)
	{
		pthread_mutex_lock(&(arr->mutex));
		arr->n++;
		i++;
		printf("%d\n", arr->n);
		pthread_mutex_unlock(&(arr->mutex));
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	pthread_t	*threads;
	t_test		*mutex;
	int			i;

	i = 0;
	if (argc == 2)
	{
		threads = malloc(sizeof(pthread_t) * atoi(argv[1]));
		mutex = malloc(sizeof(t_test));
		pthread_mutex_init(&(mutex->mutex), NULL);
		while (i < atoi(argv[1]))
		{
			pthread_create(threads + i, NULL, test_thread, mutex);
			i++;
		}
	}
	pthread_join(threads[1], NULL);
	pthread_join(threads[2], NULL);
	return (0);
}
