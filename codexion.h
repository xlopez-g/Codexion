/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlopez-g <xlopez-g@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 12:41:50 by xlopez-g          #+#    #+#             */
/*   Updated: 2026/11/16 12:48:19 by xlopez-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <threads.h>
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
//# include "./ft_printf/ft_printf.h"

/*Structs*/

typedef struct s_data
{
	int				number_of_coders;
	long			time_to_burnout;
	long			time_to_compile;
	long			time_to_debug;
	long			time_to_refactor;
	unsigned int	number_of_compiles_required;
	long			dongle_cooldown;
	char			*scheduler;

}	t_data;


typedef struct s_dongle
{
	pthread_mutex_t	*mutex;
	pthread_cond_t	*cond_var;
}	t_dongle;




typedef struct s_coder
{
	pthread_t	*thread;
	t_dongle	*left_dungle;
	t_dongle	*right_dongle;
}	t_coder;

typedef struct s_simulation
{
	t_data		t_data;
	t_coder		t_coder;
	t_dongle	t_dongle;
}	t_simulation;





long	ft_atol(const char *nptr);
int		ft_atoi(const char *nptr);
size_t	ft_strlen(const char *a);
int		ft_strcmp(const char *s1, const char *s2);


#endif
