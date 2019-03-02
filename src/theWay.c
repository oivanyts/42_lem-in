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

bool printShort(t_graph *pGraph, bool **closedVert, t_path **path)
{
	int 	current, i = 0;
	current = 0;

	if (pGraph->array[current]->distance == INT_MAX || gmoves - pGraph->array[current]->distance < 0)
		return (0);
	//	ft_printf("\tPATH = %d\t", gmoves - pGraph->array[current]->distance + 1);
	*path = malloc(sizeof(t_path));
	(*path)->size = pGraph->array[current]->distance;
	(*path)->path = malloc(sizeof(int *) * (*path)->size);
	gresult += gmoves - pGraph->array[current]->distance + 1;
	while (current != pGraph->V - 1)
	{
		(*path)->path[i++] = current;
//		ft_printf("%s -> ", pGraph->array[current]->name);
		if ((current = closestNeighbor(current, pGraph)) == -1)
			return (0);
		(*path)->path[i++] = current;
		(*closedVert)[current] = true;
	}
//	ft_printf("%s\n", pGraph->array[current]->name);
	return (1);
}

void	signAllDist(t_graph **pGraph, int dist)
{
	int	i = 0;
	while (i < (*pGraph)->V)
		(*pGraph)->array[i++]->distance = dist;
}

void	findParallel(t_graph **pGraph)
{
	bool		*closedVert;
	t_list		*allPath;
	t_path		*path;

	closedVert = ft_memalloc((size_t)(*pGraph)->V);
	while (fillDistance(pGraph, &closedVert, &path))
	{
		ft_lstaddback(&allPath, ft_lstnew(path, sizeof(path)));
		signAllDist(pGraph, INT_MAX);
		closedVert[(*pGraph)->V - 1] = false;
		closedVert[0] = false;
	}
	ft_printf("RESULT %d\n\n", gresult);
}

bool	fillDistance(t_graph **pGraph, bool **closedVert, t_path **path)
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
	return !printShort(*pGraph, closedVert, path) ? false : true;
}



