/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlopez-g <xlopez-g@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/16 12:03:20 by xlopez-g          #+#    #+#             */
/*   Updated: 2026/11/27 11:52:59 by xlopez-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "codexion.h"


int	create_dongles(t_simulation *simulation)
{
	int			i;
	int			number_of_coders;
	t_dongle	*dongles;

	number_of_coders = simulation->data.number_of_coders;
	dongles = malloc(sizeof(t_dongle) * number_of_coders);
	if (!dongles)
		return (1);
	i = 0;
	while (i < number_of_coders)
	{
		dongles[i].dongle_id = i;
		dongles[i].available = 0;
		dongles[i].last_release = 0;
		i++;
	}
	simulation->dongles = dongles;
	return (0);
}

int	take_left_dongle(t_coder *coder)
{
	if (coder->left_dongle->available == 0)
	{
		pthread_mutex_lock(&coder->left_dongle->dongle_mutex);
		coder->left_dongle->available = 1;
		printf("%d has taken a dongle id %d\n", coder->coder_id, coder->left_dongle->dongle_id);
	}
		return (0);
}

int	take_right_dongle(t_coder *coder)
{
	if (coder->right_dongle->available == 0)
	{
		pthread_mutex_lock(&coder->right_dongle->dongle_mutex);
		coder->right_dongle->available = 1;
		printf("%d has taken a dongle id %d\n", coder->coder_id, coder->right_dongle->dongle_id);
	}
	return (0);

}

int	take_dongles(t_coder *coder)
{
	if ((coder->coder_id - 1) % 2 == 0)
	{
		//sleep(1);
		take_right_dongle(coder);
		//sleep(1);
		take_left_dongle(coder);
	}
	else
	{
		//sleep(1);
		take_left_dongle(coder);
		//sleep(1);
		take_right_dongle(coder);
	}

	return(0);
}

int	compile(t_coder *coder)
{
	printf("%d is compiling\n", coder->coder_id);
	return(0);
	pthread_mutex_unlock(&coder->left_dongle->dongle_mutex);

}

int	debug(t_coder *coder)
{
	printf("%d is debugging\n", coder->coder_id);
	return(0);
	pthread_mutex_unlock(&coder->left_dongle->dongle_mutex);

}

int	refactor(t_coder *coder)
{
	printf("%d is refactorizing\n", coder->coder_id);
	return(0);
	pthread_mutex_unlock(&coder->left_dongle->dongle_mutex);

}
int	release_dongles(t_coder *coder)
{
	coder->left_dongle->available = 0;
	coder->right_dongle->available = 0;
	pthread_mutex_unlock(&coder->left_dongle->dongle_mutex);
	pthread_mutex_unlock(&coder->right_dongle->dongle_mutex);
}

void	*coder_routine(void *in_coder)
{
	t_coder	*coder;
	int		compiles_required;

	coder = (t_coder *)in_coder;
	compiles_required = coder->simulation->data.compiles_required;
	if (coder->simulation->end_simulation == 1)
		pthread_cond_broadcast(&coder->simulation->monitor_cond);
	while (coder->compile_number != compiles_required)
	{
		take_dongles(coder);
		compile(coder);
		sleep(1);
		//coder->compile_number++;
		//debug(coder);
		//refactor(coder);
		release_dongles(coder);
	}
	if (coder->simulation->end_simulation == 1)
		pthread_cond_broadcast(&coder->simulation->monitor_cond);
	debug(coder);
	
	if (coder->simulation->end_simulation == 1)
		pthread_cond_broadcast(&coder->simulation->monitor_cond);
	refactor(coder);
}

int	initialize_coder(t_coder *coder)
{
	int	i;	

	if(pthread_mutex_init(&coder->coder_mutex, NULL) != 0)
		return(1);

	if(pthread_create(&coder->thread, NULL, (void *)coder_routine, (void *)coder) != 0)
		return(1);
	return (0);
}

int	right_dongle(int i, int numbers_of_coders)
{
	int	right;

	if (i != numbers_of_coders - 1)
		right = i + 1;
	else
		right = 0;
	return (right);
}

int	create_coders(t_simulation *simulation)
{
	int		i;
	int		right;

	i = 0;
	//printf("numbers: %d\n", simulation->data.number_of_coders);
	simulation->coders = malloc(sizeof(t_coder) * simulation->data.number_of_coders);
	if (simulation->coders == NULL)
		return (1);
	while (i < simulation->data.number_of_coders)
	{
		right = right_dongle(i, simulation->data.number_of_coders);
		simulation->coders[i].coder_id = i + 1;
		simulation->coders[i].compile_number = 0;
		simulation->coders[i].last_compile = 0;
		simulation->coders[i].left_dongle = &simulation->dongles[i];
		simulation->coders[i].right_dongle = &simulation->dongles[right];
		simulation->coders[i].simulation = simulation;
		if (initialize_coder(&simulation->coders[i]) != 0)
			return (2);
		i++;
	}	
	i = 0;
	while (i < simulation->data.number_of_coders)
	{
		pthread_join(simulation->coders[i].thread, NULL);
		pthread_mutex_destroy(&simulation->coders[i].coder_mutex);
		i++;
	}
	return (0);
}

void	*monitor_routine(void *in_data)
{
	t_simulation	*simulation;

	simulation = (t_simulation *)in_data;
	pthread_mutex_lock(&simulation->end_mutex);
	while (simulation->end_simulation == 0)
	{
		pthread_cond_wait(&simulation->monitor_cond, &simulation->end_mutex);
		printf("b\n");
		sleep(5);
		//simulation->end_simulation++;
	}
	printf("end!");
	pthread_mutex_unlock(&simulation->end_mutex);
	
}

int    create_simulation(t_simulation *simulation)
{
	pthread_t       monitor_thread;
	int				res;

	simulation->end_simulation = 0;
	pthread_mutex_init(&simulation->end_mutex, NULL);
	pthread_cond_init(&simulation->monitor_cond, NULL);
	pthread_create(&monitor_thread, NULL, monitor_routine, (void *)simulation);
	create_dongles(simulation);

	res = create_coders(simulation);
	printf("res: %d\n", res);
	pthread_join(monitor_thread, NULL);
	pthread_cond_destroy(&simulation->monitor_cond);
	pthread_mutex_destroy(&simulation->end_mutex);
	printf("d\n");
	return (0);
}
/*
int main(void)
{
	t_simulation    simulation;
	
	if (create_simulation(&simulation) != 0)
	return (1);
	
	return (0);
}
*/
