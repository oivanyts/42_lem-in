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

int closestNeighbor(int current, t_Graph *pGraph)
{
	int	i;
	int min;
	int bestNext;

	i = 0;
	bestNext = pGraph->array[current]->Neighbor[0];
	min = pGraph->array[bestNext]->distance;
	while (i < pGraph->array[current]->links)
	{
		if (current != pGraph->array[current]->Neighbor[i] &&
			pGraph->array[pGraph->array[current]->Neighbor[i]]->distance < min)
		{
			bestNext = pGraph->array[current]->Neighbor[i];
			min = pGraph->array[bestNext]->distance;
		}
		i++;
	}
	return min == INT_MAX ? -1 : bestNext;
}

bool printShort(t_Graph *pGraph, bool **closedVert)
{
	int 		current;

	current = 0;

	if (pGraph->array[current]->distance == INT_MAX || gmoves - pGraph->array[current]->distance < 0)
		return (0);
	ft_printf("\tPATH = %d\t", gmoves - pGraph->array[current]->distance + 1);
	gresult += gmoves - pGraph->array[current]->distance + 1;
	while (current != pGraph->V - 1)
	{
		ft_printf("%s -> ", pGraph->array[current]->name);
		if ((current = closestNeighbor(current, pGraph)) == -1)
			return (0);
		(*closedVert)[current] = true;
	}
	ft_printf("{red}%s{eoc}\n", pGraph->array[current]->name);
	return (1);
}

void	signAllDist(t_Graph **pGraph, int dist)
{
	int	i = 0;
	while (i < (*pGraph)->V)
		(*pGraph)->array[i++]->distance = dist;
}

void	findParallel(t_Graph **pGraph)
{
	bool		*closedVert;

	closedVert = ft_memalloc((size_t)(*pGraph)->V);
	while (fillDistance(pGraph, &closedVert))
	{

		signAllDist(pGraph, INT_MAX);
		closedVert[(*pGraph)->V - 1] = false;
		closedVert[0] = false;
	}
	ft_printf("RESULT %d\n\n", gresult);
}

bool	fillDistance(t_Graph **pGraph, bool **closedVert)
{
	int			j, i, qSize;
	int			queue[(*pGraph)->V];
	t_Vertex	*tmp;
	bool		visitedVert[(*pGraph)->V];

	i = 0;
	ft_bzero(visitedVert, (size_t)(*pGraph)->V - 1);
	queue[0] = (*pGraph)->V - 1;
	(*pGraph)->array[queue[0]]->distance = 0;
	qSize = 1;
	while (i < qSize)
	{
		j = 0;
		tmp = (*pGraph)->array[queue[i]];
		while (j < tmp->links)
		{
			if ((*pGraph)->array[tmp->Neighbor[j]]->distance > tmp->distance + 1
				&& !(visitedVert)[tmp->Neighbor[j]] && !(*closedVert)[tmp->Neighbor[j]])
			{
				(*pGraph)->array[tmp->Neighbor[j]]->distance = tmp->distance + 1;
				queue[qSize++] = tmp->Neighbor[j];
			}
			j++;
		}
		visitedVert[queue[i]] = true;
		i++;
	}
	return !printShort(*pGraph, closedVert) ? false : true;
}



