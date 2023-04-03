/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleitner <mleitner@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 14:02:16 by mleitner          #+#    #+#             */
/*   Updated: 2023/04/03 14:26:03 by mleitner         ###   ########.fr       */
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
	int	phil;
	int	ttd;
	int	tte;
	int	tts;
	int	eat;
}	t_rules;


//utils functions
long		ft_atoi(char *s);
t_rules		*set_rules(int argc, char **argv);
uint64_t	get_time(void);
int			ft_usleep(__useconds_t time);

#endif