/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleitner <mleitner@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 14:02:16 by mleitner          #+#    #+#             */
/*   Updated: 2023/04/05 16:50:22 by mleitner         ###   ########.fr       */
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
	uint64_t 		start_time;
	struct t_philo	*phil;
}	t_rules;

//state: dead 0, thinking 1, eating 2, sleeping 3
typedef struct s_philo{
	int 			num;
	pthread_t		tid;
	int				meals;
	uint64_t		last_eaten;
	int				state;
	t_rules			*rules;
	pthread_mutex_t *l_fork;
	pthread_mutex_t *r_fork;
}	t_philo;

//utils functions
long		ft_atoi(char *s);
t_rules		*set_rules(int argc, char **argv);
uint64_t	get_time(void);
int			ft_usleep(__useconds_t time);

//init functions
t_philo	*create_philos(t_rules *rules);
pthread_mutex_t *init_forks(t_rules *rules);
t_philo	init_philos(t_rules *rules, int n, pthread_mutex_t *forks);
void	*do_philo(void *arg);
void	take_fork(t_philo *philo);
void	drop_fork(t_philo *philo);


#endif