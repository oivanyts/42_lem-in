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
		printf("[%d] ", tmp->size);
		while (i < tmp->size)
		{
			printf(" -> %s", (char *)pGraph->array[tmp->path[i]]->name);
			i++;
		}
		printf("\n");
		pList = pList->next;
	}
}
static int closestNeighbor1(int current, t_graph *pGraph, int dist)
{
	int	i;
	int min;
	int bestNext;

	i = pGraph->array[current]->links;
	bestNext = pGraph->array[current]->nextV[0];
	min = pGraph->array[bestNext]->distance;
	while (i--)
	{
		if (current != pGraph->array[current]->nextV[i] &&
			pGraph->array[pGraph->array[current]->nextV[i]]->distance == dist)
		{
			bestNext = pGraph->array[current]->nextV[i];
			min = pGraph->array[bestNext]->distance;
		}
	}
	return min == INT_MAX ? -1 : bestNext;
}

static bool signShortPath(t_graph *pGraph, bool **closedVert, t_list **allPath)
{
	int    current;
	int    i;
	t_path *tmp;

	i 		= 0;
	current = 0;
	if (pGraph->array[current]->distance == INT_MAX)
		return (0);
	tmp = malloc(sizeof(t_path));
	tmp->size = pGraph->array[current]->distance;
	tmp->path = ft_memalloc(sizeof(int) * tmp->size);
	while (current != pGraph->V - 1)
	{
		if ((current = closestNeighbor1(current, pGraph, tmp->size - i - 1)) == -1)
			return 0;
		tmp->path[i]         = current;
		(*closedVert)[current] = true;
//		if (closestNeighbor1(current, pGraph, tmp->size - i - 1) != -1)
//			;
		i++;
	}
	ft_lstaddback(allPath, ft_lstnew(&tmp, sizeof(t_path *)));
//	free(tmp->path);
//	free(tmp);
	return (1);
}

static void	signAllDist(t_graph **pGraph, int dist)
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
		if (!queue[i])
			break ;
		i++;
	}
	return !signShortPath(*pGraph, closedVert, allPath) ? false : true;
}

void	delPath(void *path, size_t size)
{
	t_path *tmp;

	tmp = *(t_path **)path;
	if (size)
	{
		free(tmp->path);
		free(tmp);
	}
	free(path);
}

void	findParallel(t_graph **pGraph)
{
	bool		*closedVert;
	t_list		*allPath;

	allPath = NULL;
	closedVert = ft_memalloc((size_t)(*pGraph)->V);
	while (fillDistance(pGraph, &closedVert, &allPath))
	{
		if (allPath && (*(t_path **)(allPath->content))->size == 1)
			break ;
		signAllDist(pGraph, INT_MAX);
		closedVert[(*pGraph)->V - 1] = false;
		closedVert[0] = false;
	}
	runAllPath(allPath, pGraph);
	ft_lstdel(&allPath, delPath);
	free(closedVert);
}







