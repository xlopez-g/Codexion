/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlopez-g <xlopez-g@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 12:41:50 by xlopez-g          #+#    #+#             */
/*   Updated: 2026/11/23 12:53:20 by xlopez-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <pthread.h>
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
//# include "./ft_printf/ft_printf.h"

/*Structs*/
/*
typedef enum e_scheduler
{
	FIFO,
	EDF
}	t_scheduler;
*/

typedef struct s_data
{
	int				number_of_coders;
	long			time_to_burnout;
	long			time_to_compile;
	long			time_to_debug;
	long			time_to_refactor;
	unsigned int	compiles_required;
	long			dongle_cooldown;
	char		    *scheduler;

}	t_data;

typedef struct s_simulation t_simulation;

typedef struct s_dongle
{
	int				dongle_id;
	pthread_mutex_t	dongle_mutex;
	pthread_cond_t	dongle_cond;
	int             available;
	long            last_release;
}	t_dongle;




typedef struct s_coder
{
	int             coder_id;
	pthread_t	    thread;
	t_dongle	    *left_dongle;
	t_dongle	    *right_dongle;
	pthread_mutex_t	coder_mutex;
	int             compile_number;
	long		    last_compile;
	t_simulation	*simulation;
}	t_coder;

typedef struct s_simulation
{
	pthread_t	    monitor_thread;
	int             end_simulation;
	pthread_mutex_t	end_mutex;
	long		    initial_time;
	t_data          data;
	t_coder         *coders;
	t_dongle	    *dongles;
}	t_simulation;



int    create_simulation(t_simulation *simulation);


long	ft_atol(const char *nptr);
int		ft_atoi(const char *nptr);
size_t	ft_strlen(const char *a);
int		ft_strcmp(const char *s1, const char *s2);


#endif
