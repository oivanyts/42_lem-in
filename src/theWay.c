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

void printAllPath(t_list *pList, t_graph *pGraph)
{
	t_path	*tmp;
	int 	i;

	while (pList)
	{
		i = 0;
		tmp = *(t_path **)(pList->content);
		ft_printf("{blue}[%d] {eoc} ", tmp->size);
		while (i < tmp->size)
		{
			ft_printf(" -> %s", pGraph->array[tmp->path[i]]->name);
			i++;
		}
		ft_printf("\n");
		pList = pList->next;
	}
}

int closestNeighbor(int current, t_graph *pGraph)
{
	int	i;
	int min;
	int bestNext;

	i = 0;
	bestNext = pGraph->array[current]->nextV[0];
	min = pGraph->array[bestNext]->distance;
	while (i < pGraph->array[current]->links)
	{
		if (current != pGraph->array[current]->nextV[i] &&
			pGraph->array[pGraph->array[current]->nextV[i]]->distance < min)
		{
			bestNext = pGraph->array[current]->nextV[i];
			min = pGraph->array[bestNext]->distance;
		}
		i++;
	}
	return min == INT_MAX ? -1 : bestNext;
}

bool signShortPath(t_graph *pGraph, bool **closedVert, t_list **allPath)
{
	int    current;
	int    i;
	t_path *tmp;

	i = 0;
	current = 0;
//	ft_printf("%d <> %d\n\n", pGraph->totalAnts, pGraph->array[current]->distance);
	if (pGraph->array[current]->distance == INT_MAX)
//	|| (pGraph->array[current]->distance > pGraph->totalAnts && *allPath))
		return (0);
	tmp = malloc(sizeof(t_path));
	tmp->size = pGraph->array[current]->distance;
	tmp->path = ft_memalloc(sizeof(int) * tmp->size);
//	gresult += gmoves - pGraph->array[current]->distance + 1;
	while (current != pGraph->V - 1)
	{
		if ((current = closestNeighbor(current, pGraph)) == -1)
			return (0);
		tmp->path[i++] = current;
		(*closedVert)[current] = true;
	}
	ft_lstaddback(allPath, ft_lstnew(&tmp, sizeof(t_path *)));
	return (1);
}

void	signAllDist(t_graph **pGraph, int dist)
{
	int	i = 0;
	while (i < (*pGraph)->V)
		(*pGraph)->array[i++]->distance = dist;
}

bool	fillDistance(t_graph **pGraph, bool **closedVert, t_list **allPath)
{
	int			i, j, qSize;
	int			queue[(*pGraph)->V];
	t_vertex	*tmp;
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
			if ((*pGraph)->array[tmp->nextV[j]]->distance > tmp->distance + 1
				&& !(visitedVert)[tmp->nextV[j]] && !(*closedVert)[tmp->nextV[j]])
			{
				(*pGraph)->array[tmp->nextV[j]]->distance = tmp->distance + 1;
				queue[qSize++] = tmp->nextV[j];
			}
			j++;
		}
		visitedVert[queue[i]] = true;
		i++;
	}
	return !signShortPath(*pGraph, closedVert, allPath) ? false : true;
}

void	findParallel(t_graph **pGraph)
{
	bool		*closedVert;
	t_list		*allPath;

	allPath = NULL;
	closedVert = ft_memalloc((size_t)(*pGraph)->V);
	while (fillDistance(pGraph, &closedVert, &allPath))
	{
		signAllDist(pGraph, INT_MAX);
		closedVert[(*pGraph)->V - 1] = false;
		closedVert[0] = false;
	}
	printAllPath(allPath, *pGraph);
//	ft_printf("RESULT %d\n\n", gresult);
	runAllPath(allPath, pGraph);
}





