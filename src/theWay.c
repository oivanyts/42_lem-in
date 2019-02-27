/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   theWay.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oivanyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 12:29:19 by oivanyts          #+#    #+#             */
/*   Updated: 2019/02/22 12:29:23 by oivanyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem-in.h"

void printShort(t_Graph *pGraph);

int closeNeighbor(int current, t_Graph *pGraph);

void fillDistance(t_Graph **pGraph)
{
	int			j, i, qSize;
	int			queue[100000];
	t_Vertex	*tmp;
	bool		closedVert[(*pGraph)->V];

	ft_bzero(closedVert, (size_t)(*pGraph)->V);
//	ft_bzero(queue, 100000);
	queue[0] = (*pGraph)->V - 1;
	(*pGraph)->array[(int)queue[0]]->distance = 0;
	i = 0;
	qSize = 1;
	while (i < qSize)
	{
		j = 0;
		tmp = (*pGraph)->array[queue[i]];
		while (j < tmp->links)
		{
			if ((*pGraph)->array[tmp->Neighbor[j]]->distance > tmp->distance + 1
			&& !closedVert[tmp->Neighbor[j]])
			{
				(*pGraph)->array[tmp->Neighbor[j]]->distance = tmp->distance + 1;
				queue[qSize++] = tmp->Neighbor[j];
			}
			j++;
		}
		closedVert[queue[i]] = (bool) 1;
		i++;
	}
	printShort(*pGraph);
}

void printShort(t_Graph *pGraph)
{
	int current;
//	int last;

	current = 0;
	ft_printf("\t\t");
	while (current != pGraph->V - 1)
	{
		ft_printf("%s -> ", pGraph->array[current]->name);
//		last = current;
		current = closeNeighbor(current, pGraph);
	}
	ft_printf("{red}%s{eoc}", pGraph->array[current]->name);
}

int closeNeighbor(int current, t_Graph *pGraph)
{
	int	i;
	int min;
	int bestNext;

	i = 0;
	bestNext = pGraph->array[current]->Neighbor[0];
	min = pGraph->array[bestNext]->distance;
//	ft_printf("\nmin - %d >%s<\n", min, pGraph->array[bestNext]->name);
	while (i < pGraph->array[current]->links)
	{
//		ft_printf("%s - %d\n", pGraph->array[pGraph->array[current]->Neighbor[i]]->name, pGraph->array[pGraph->array[current]->Neighbor[i]]->distance);
		if (current != pGraph->array[current]->Neighbor[i] &&
			pGraph->array[pGraph->array[current]->Neighbor[i]]->distance < min)
		{
			bestNext = pGraph->array[current]->Neighbor[i];
			min = pGraph->array[bestNext]->distance;
		}
		i++;
	}
//	ft_printf("last min - %d %s\n", min, pGraph->array[bestNext]->name);
	return (bestNext);
}



