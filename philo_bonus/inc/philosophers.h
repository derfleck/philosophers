/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleitner <mleitner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 14:02:16 by mleitner          #+#    #+#             */
/*   Updated: 2023/06/13 16:12:16 by mleitner         ###   ########.fr       */
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
# include <string.h>
# include <semaphore.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/wait.h>

# define SEM 0
# define PHI 1
# define PRO 2
# define ARG 3

typedef struct s_philo	t_philo;

typedef struct s_rules{
	long			phil_n;
	long			die;
	long			eat;
	long			sleep;
	long			eat_n;
	uint64_t		start_time;
	t_philo			*philo;
	sem_t			*forks;
	sem_t			*print;
	sem_t			*eaten;
	sem_t			*died;
	sem_t			*barrier_mutex;
}	t_rules;

typedef struct s_philo{
	unsigned int	num;
	unsigned int	meals;
	pid_t			pid;
	uint64_t		last_eaten;
	t_rules			*rules;
	sem_t			*philo_sem;
	char			*philo_str;
}	t_philo;

//utils functions
long		ft_atoi(char *s);
uint64_t	get_time(void);
void		ft_usleep(uint64_t time);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_itoa(int n);

//init functions
int			create_semaphore(t_rules *rules);
void		close_semaphore(t_rules *rules);

//process functions
int			process_start(t_rules *rules);

//routine functions
void		print_status(char *str, t_philo *philo);
void		take_fork(t_philo *philo);
void		eat(t_philo *philo);
void		do_philo(t_philo *philo);

#endif