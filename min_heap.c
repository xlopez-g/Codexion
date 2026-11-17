/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_heap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlopez-g <xlopez-g@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/16 14:19:10 by xlopez-g          #+#    #+#             */
/*   Updated: 2026/11/17 13:00:29 by xlopez-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

/*
int	*organize_mean_heap(int *list, int len)
{
	int	i;
	int	j;
	int	temp;

	i = 0;
	while (i < len)
	{
		if (list[i] > list[2 * i + 1] && (2 * i + 1) < len)
		{
			temp = list[i];
			list[i] = list[2 * i + 1];
			list[2 * i + 1] = temp;
		}
		if (list[i] > list[2 * i + 2] && (2 * i + 2) < len)
		{
			temp = list[i];
			list[i] = list[2 * i + 2];
			list[2 * i + 2] = temp;
		}
		i++;
	}
	return (&list[0]);
}
*/

void heapify(int *heap, int len, int i)
{

}


int	pop_heap(int *list, int len)
{
	int	i;
	int	result;
	int	next_min;

	i = 0;
	result = list[0];
	if (list[2 * i + 1] <= list[2 * i + 2])
		next_min = 2 * i + 1;
	else
		next_min = 2 * i * 2;
}

int	*organize_mean_heap(int *list, int len)
{
    int index;
    int temp;
    int i;
    int left;
    int right;
    int j;

    index = len / 2 - 1;
    
	i = index;
	while (i >= 0)
	{
        left = list[2 * i + 1];
        right = list[2 * i + 2];
        j = 0;
		if (list[i] > left && right >= left)
		{
			temp = list[i];
			list[i] = list[2 * i + 1];
			list[2 * i + 1] = temp;
        }
		else if (list[i] > right && left > right)
		{
			temp = list[i];
			list[i] = list[2 * i + 2];
			list[2 * i + 2] = temp;
		}
		i--;
	}
	return (&list[0]);
}
int main(void)
{
    int *result;
    int list[] = {9, 4, 7, 1, 3, 8, 2};

    result = organize_mean_heap(&list[0], 7);
    int i= 0;
    while (i<7)
    {
        printf("%d\n", list[i]);
        i++;
    }
    return (0);
}
