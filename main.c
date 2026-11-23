/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlopez-g <xlopez-g@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/23 12:54:26 by xlopez-g          #+#    #+#             */
/*   Updated: 2026/11/23 13:33:56 by xlopez-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "codexion.h"

int	checknbr_str(char *str)
{
	int	counter;

	counter = 0;
	while (str[counter] == ' ' || (str[counter] > 8 && str[counter] < 14))
		counter++;
	if (str[counter] == '-' || str[counter] == '\0')
		return (0);
	while (str[counter] != '\0')
	{
		if (str[counter] < '0' || str[counter] > '9')
			return (0);
		counter++;
	}
	return (1);
}

int	general_parser(int argc, char **argv)
{
	int	i;

	if (argc != 9)
	{
		printf("Error: Expected 8 arguments");
		return (0);
	}
	if (ft_strcmp(argv[8], "fifo") != 0 && ft_strcmp(argv[8], "edf") != 0)
	{
		printf("Error: Scheduler needs to be 'edf' or 'fifo'");
		return (0);
	}
	i = 1;
	while (i < 8)
	{
		if (checknbr_str(argv[i]) == 0)
		{
			printf("Error: Argument %d need to be a valid integer", i);
			return (0);
		}
		i++;
	}
	return (1);
}

int	parser(t_data data)
{
	int	nbr;
	int	n_coders;

	n_coders = data.number_of_coders;
	nbr = data.compiles_required;
	if (n_coders == 1)
		printf("Error: Only one coder");
	else if (n_coders < 1)
		printf("Erros: Invalid number for number of coders");
	else if (n_coders >= __INT_MAX__)
	{
		printf("Coder numbers too high");
	}
	else if (nbr < 1 || nbr > __INT_MAX__)
	{
		printf("Error: Numbers of compiles must be a valid integer");
	}
	else
		return (1);
	return (0);
}

t_data	organizer(int argc, char **argv)
{
	t_data	data;

	data.number_of_coders = ft_atoi(argv[1]);
	data.time_to_burnout = ft_atol(argv[2]);
	data.time_to_compile = ft_atol(argv[3]);
	data.time_to_debug = ft_atol(argv[4]);
	data.time_to_refactor = ft_atol(argv[5]);
	data.compiles_required = ft_atoi(argv[6]);
	data.dongle_cooldown = ft_atoi(argv[7]);
	data.scheduler = argv[8];
	return (data);
}

void	printf_organizer(t_data data)
{
	printf("%d", data.number_of_coders);
	printf("\n%ld", data.time_to_burnout);
	printf("\n%ld", data.time_to_compile);
	printf("\n%ld", data.time_to_debug);
	printf("\n%ld", data.time_to_refactor);
	printf("\n%d", data.compiles_required);
	printf("\n%ld", data.dongle_cooldown);
	printf("\n%s\n", data.scheduler);
}

int	main(int argc, char **argv)
{
	t_data	data;
    t_simulation    *simulation;

	if (general_parser(argc, argv) == 0)
		return (0);
	data = organizer(argc, argv);
	if (parser(data) == 0)
		return (0);
    simulation = malloc(sizeof(t_simulation));
    if (simulation == NULL)
        return (1);
    simulation->data = data;
    printf_organizer(simulation->data);
    if (create_simulation(simulation) != 0)
		return (1);
	return (0);
}
