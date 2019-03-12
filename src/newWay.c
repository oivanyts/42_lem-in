/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newWay.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oivanyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 08:45:57 by oivanyts          #+#    #+#             */
/*   Updated: 2019/03/11 08:46:02 by oivanyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem-in.h"
//
//static void	closeUsedVert(bool   *closedVert, t_path	*tmpPath)
//{
//	int 	i;
//
//	i = 0;
//	while (i < tmpPath->size)
//		closedVert[tmpPath->path[i++]] = true;
//}
////static int	closestNeighborR(int current, t_graph *pGraph, int dist)
////{
////	int	i;
////	int min;
////	int bestNext;
////
////	i = 0;
////	bestNext = pGraph->array[current]->nextV[0];
////	min = pGraph->array[bestNext]->distance;
////	while (i < pGraph->array[current]->links)
////	{
////		if (current != pGraph->array[current]->nextV[i] &&
////			pGraph->array[pGraph->array[current]->nextV[i]]->distance == dist)
////		{
////			bestNext = pGraph->array[current]->nextV[i];
////			min = pGraph->array[bestNext]->distance;
////		}
////		i++;
////	}
////	i = pGraph->array[current]->links;
////	return min == INT_MAX ? -1 : bestNext;
////}
//static int countClosest(int current, t_graph *pGraph, int dist)
//{
//	int counter, i;
//
//	counter = 0;
//	i       = pGraph->array[current]->links;
//	while (i--)
//		if (pGraph->array[pGraph->array[current]->nextV[i]]->distance == dist)
//			counter++;
//	return (counter);
//}
//
//static int	closestNeighborL(int current, t_graph *pGraph, int dist)
//{
//	int	i;
//	int min;
//	int bestNext;
//
//	i = pGraph->array[current]->links;
//	bestNext = pGraph->array[current]->nextV[0];
//	min = pGraph->array[bestNext]->distance;
//	while (i--)
//	{
//		if (current != pGraph->array[current]->nextV[i] &&
//			pGraph->array[pGraph->array[current]->nextV[i]]->distance == dist)
//		{
//			bestNext = pGraph->array[current]->nextV[i];
//			min = pGraph->array[bestNext]->distance;
//		}
//	}
//	i = pGraph->array[current]->links;
//	return min == INT_MAX ? -1 : bestNext;
//}
//
//static t_list *signShortPath(int current, t_graph **pGraph, bool *closedVert, t_list **allPath)
//{
//	int		i;
//	t_list	*curPath;
//	t_path	*tmp;
//	int 	closest;
//
//	i 		= 0;
//	current = 0;
//	if ((*pGraph)->array[current]->distance == INT_MAX && allPath != NULL)
//		return (NULL);
//	tmp = malloc(sizeof(t_path));
//	tmp->size = (*pGraph)->array[current]->distance;
//	tmp->path = ft_memalloc(sizeof(int) * tmp->size);
//	while (current != (*pGraph)->V - 1)
//	{
//		if (!(closest = countClosest(current, *pGraph, tmp->size - i - 1)))
//			return (NULL);
//		else
//			while (closest--)
//			{
//			}
//			tmp->path[i] = current;
////		if (closestNeighborL(current, *pGraph, tmp->size - i - 1) != -1)
////		{
////			ft_lstaddback(allPath, findParallel1(, pGraph, allPath, closedVert));
////		}
//		i++;
//	}
//	closeUsedVert(closedVert, tmp);
//	ft_lstaddback(&curPath, ft_lstnew(tmp, sizeof(t_path)));
//	free(tmp->path);
//	free(tmp);
//	return (curPath);
//}
//
////static void finishPath(int closest, t_graph **pGraph, bool *pBoolean, t_list **pList)
////{
////
////}
//
//static void	fillDistance1(t_graph **pGraph, bool *closedVert)
//{
//	int			i, j, qSize;
//	int			queue[(*pGraph)->V];
//	t_vertex	*tmp;
//	bool		visitedVert[(*pGraph)->V];
//
//	i = 0;
//	ft_bzero(visitedVert, (size_t)(*pGraph)->V - 1);
//	queue[0] = (*pGraph)->V - 1;
//	(*pGraph)->array[queue[0]]->distance = 0;
//	qSize = 1;
//	while (i < qSize)
//	{
//		j = 0;
//		tmp = (*pGraph)->array[queue[i]];
//		while (j < tmp->links)
//		{
//			if ((*pGraph)->array[tmp->nextV[j]]->distance > tmp->distance + 1
//				&& !(visitedVert)[tmp->nextV[j]] && !closedVert[tmp->nextV[j]])
//			{
//				(*pGraph)->array[tmp->nextV[j]]->distance = tmp->distance + 1;
//				queue[qSize++] = tmp->nextV[j];
//			}
//			j++;
//		}
//		visitedVert[queue[i]] = true;
//		if (queue[i])
//			break ;
//		i++;
//	}
//}
//
//static void	signAllDist(t_graph **pGraph, int dist)
//{
//	int	i = 0;
//	while (i < (*pGraph)->V)
//		(*pGraph)->array[i++]->distance = dist;
//}
//
//int	*runToEnd()
//{
//
//}
//
//t_list	*findParallel1(int start, t_graph **pGraph, t_list **allPath, bool *closedVert)
//{
//	int		crawler, counter = 0;
//	t_list	*newPath = NULL;
//	bool 	*closedNew;
//	t_path	*currentPath;
//
//	closedNew = ft_memalloc((*pGraph)->V);
//	ft_memcpy(closedNew, closedVert, (*pGraph)->V);
//	while (1)
//	{
//		crawler = 0;
//		fillDistance1(pGraph, closedNew);
//		if ((*pGraph)->array[0]->distance == INT_MAX)
//			break ;
//		currentPath = ft_memalloc(sizeof(t_path));
//		currentPath->size = (*pGraph)->array[crawler]->distance;
//		currentPath->path = ft_memalloc(currentPath->size * sizeof(int));
//		while (crawler != (*pGraph)->V - 1)
//		{
//			ft_printf("%s -> ", (*pGraph)->array[crawler]->name);
//			currentPath->path[counter++] = crawler;
//
//		}
//		ft_memmove(currentPath->path, tmp, counter * sizeof(int));
//		signAllDist(pGraph, INT_MAX);
//		closedNew[(*pGraph)->V - 1] = false;
//		closedNew[0]                = false;
//		start = 0;
//	}
//	free(closedNew);
//	closedNew = NULL;
//	return newPath;
//}

