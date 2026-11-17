/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlopez-g <xlopez-g@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/16 12:09:00 by xlopez-g          #+#    #+#             */
/*   Updated: 2026/11/16 12:10:32 by xlopez-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

size_t	ft_strlen(const char *a)
{
	size_t	counter;

	counter = 0;
	while (a[counter] != '\0')
	{
		counter++;
	}
	return (counter);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	ner;
	int		result;
	int		n;
	int		n2;

	ner = 0;
	n = ft_strlen(s1);
	n2 = ft_strlen(s2);
	if (n != n2)
		return (n - n2);
	while (ner < n)
	{
		if ((unsigned char)s1[ner] == (unsigned char) s2[ner])
			ner++;
		else
		{
			result = (unsigned char) s1[ner] - (unsigned char) s2[ner];
			return (result);
		}
	}
	return (0);
}

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

long	ft_atol(const char *nptr)
{
	long int	number;
	int			counter;
	int			sign;

	counter = 0;
	number = 0;
	sign = 1;
	while (nptr[counter] == ' ' || (nptr[counter] > 8 && nptr[counter] < 14))
		counter++;
	if (nptr[counter] == '-')
	{
		sign = sign * (-1);
		counter++;
	}
	else if (nptr[counter] == '+')
		counter++;
	while (ft_isdigit(nptr[counter]) == 1)
	{
		number = number * 10 + nptr[counter] - '0';
		counter++;
	}
	if (nptr[counter] != '\0')
		return (2147483649);
	number = number * sign;
	return (number);
}


int	ft_atoi(const char *nptr)
{
	int	number;
	int	counter;
	int	sign;

	counter = 0;
	number = 0;
	sign = 1;
	while (nptr[counter] == ' ' || (nptr[counter] > 8 && nptr[counter] < 14))
		counter++;
	if (nptr[counter] == '-')
	{
		sign = sign * (-1);
		counter++;
	}
	else if (nptr[counter] == '+')
		counter++;
	while (ft_isdigit(nptr[counter]) == 1)
	{
		number = number * 10 + nptr[counter] - '0';
		counter++;
	}
	number = number * sign;
	return (number);
}
