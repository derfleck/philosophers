/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleitner <mleitner@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 14:02:16 by mleitner          #+#    #+#             */
/*   Updated: 2023/05/11 18:52:02 by mleitner         ###   ########.fr       */
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

typedef struct s_philo	t_philo;

typedef struct s_rules{
	long			phil_n;
	long			die;
	long			eat;
	long			sleep;
	long			eat_n;
	int				stop;
	int 			all_eat;
	uint64_t		start_time;
	t_philo			*phil;
	pthread_mutex_t	lock_print;
	pthread_mutex_t	lock_eat;
	pthread_mutex_t	*forks;
}	t_rules;

typedef struct s_philo{
	unsigned int	num;
	unsigned int	meals;
	pthread_t		tid;
	uint64_t		last_eaten;
	t_rules			*rules;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
}	t_philo;

//utils functions
long			ft_atoi(char *s);
void			set_rules(t_rules *rules, int argc, char **argv);
uint64_t		get_time(void);
int				ft_usleep(__useconds_t time);

//init functions
int				create_philos(t_rules *rules);
pthread_mutex_t	*init_forks(t_rules *rules);
void			init_philos(t_rules *rules, pthread_mutex_t *forks);

//thread functions
void			status_check(t_philo *philo, t_rules *rules);
void			thread_kill(t_philo *philo, t_rules *rules);
int				thread_start(t_philo *philo);

//routine functions
void			print_status(char *str, t_philo *philo, int status);
void			take_fork(t_philo *philo);
void			eat(t_philo *philo);
void			*do_philo(void *arg);

#endif