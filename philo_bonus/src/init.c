/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleitner <mleitner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 12:54:21 by mleitner          #+#    #+#             */
/*   Updated: 2023/06/13 15:03:56 by mleitner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

//creates semaphores with default names
int	create_semaphore(t_rules *rules)
{
	sem_unlink("/forks");
	sem_unlink("/eaten");
	sem_unlink("/print");
	sem_unlink("/died");
	sem_unlink("/barrier_mutex");
	rules->forks = sem_open("/forks", O_CREAT, 0664, rules->phil_n);
	rules->eaten = sem_open("/eaten", O_CREAT, 0664, 1);
	rules->print = sem_open("/print", O_CREAT, 0664, 1);
	rules->died = sem_open("/died", O_CREAT, 0664, 1);
	rules->barrier_mutex = sem_open("/barrier_mutex", O_CREAT, 0664, 1);
	if (!rules->forks || !rules->eaten || !rules->print || !rules->died)
		return (0);
	return (1);
}

//closes semaphores, in case of error or after execution
void	close_semaphore(t_rules *rules)
{
	if (rules->forks != NULL)
	{
		sem_close(rules->forks);
		sem_unlink("/forks");
	}
	if (rules->eaten != NULL)
	{
		sem_close(rules->eaten);
		sem_unlink("/eaten");
	}
	if (rules->print != NULL)
	{
		sem_close(rules->print);
		sem_unlink("/print");
	}
	if (rules->died != NULL)
	{
		sem_close(rules->died);
		sem_unlink("/died");
	}
	if (rules->barrier_mutex != NULL)
	{
		sem_close(rules->barrier_mutex);
		sem_unlink("/barrier_mutex");
	}
}
