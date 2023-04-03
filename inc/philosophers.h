/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleitner <mleitner@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 14:02:16 by mleitner          #+#    #+#             */
/*   Updated: 2023/04/03 17:28:07 by mleitner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdint.h>

typedef struct s_rules{
	int				phil_n;
	int				die;
	int				eat;
	int				sleep;
	int				eat_n;
	struct t_philo	*phil;
}	t_rules;

//state: dead 0, thinking 1, eating 2, sleeping 3
typedef struct s_philo{
	pthread_t	tid;
	int			eaten;
	int			forks[2];
	uint64_t	last_eaten;
	int			state;
	t_rules		*rules;
}	t_philo;

//utils functions
long		ft_atoi(char *s);
t_rules		*set_rules(int argc, char **argv);
uint64_t	get_time(void);
int			ft_usleep(__useconds_t time);

#endif