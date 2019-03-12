/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oivanyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 15:50:59 by oivanyts          #+#    #+#             */
/*   Updated: 2019/02/04 15:52:05 by oivanyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem-in.h"

void sortList(t_list *pList);

int get_ants(void)
{
	char	*str;
	int 	ant;
	if (get_next_line(fd, &str) <= 0)
		ERROR;
	ant = ft_atoi(str);
	free(str);
	return (ant);
}

void PrintGraph(t_graph *pGraph)
{
	int 		size, i;
	t_vertex	*tmp;

	ft_printf("\nPRINTING GRAPH\n\t size - %d\n", pGraph->V);
	size = 0;
	while (size < pGraph->V)
	{
		tmp = pGraph->array[size];
		ft_printf("#%d\tNAME\t  >%s<\t<%d:%d>{cyan}\n\tDIST\t%d\t\t{green}LINKS\t%d{red}\t\t{",
				size, tmp->name, tmp->point->x, tmp->point->y,  tmp->distance, tmp->links);
		i = 0;
		while (i < pGraph->array[size]->links)
		{
			ft_printf(" %s,", pGraph->array[pGraph->array[size]->nextV[i]]->name);
			i++;
		}
		ft_printf("%c}\n{eoc}", ' ');
		size++;
	}
}

void countLinks(t_list *pList, t_graph **pGraph)
{
	t_list	*crawler;
	int		i;

	crawler = pList;
	while (crawler)
	{
		i = 0;
		while (i < (*pGraph)->V)
		{
			if (ft_strstr(crawler->content, (*pGraph)->array[i]->name))
				(*pGraph)->array[i]->links++;
			i++;
		}
		crawler = crawler->next;
	}

}

int secondLink(t_graph *pGraph, char *link, int i)
{
	int j;

	j = 0;
	while (j < pGraph->V)
	{
		if (i != j && ft_strstr(link, pGraph->array[j]->name))
			return (j);
		j++;
	}
	return (-1);
}

void linkVertex(t_list *pList, t_graph **pGraph)
{
	int 	i;
	t_list	*crawler;

	i = (*pGraph)->V;
	while (--i >= 0)
		(*pGraph)->array[i]->nextV = malloc((*pGraph)->array[i]->links * sizeof(int));
	while (++i <= (*pGraph)->V - 1)
	{
		crawler = pList;
		while (crawler)
		{
			if (ft_strnstr(crawler->content, (*pGraph)->array[i]->name, crawler->content_size))
				(*pGraph)->array[i]->nextV[(*pGraph)->array[i]->linksAdded++]
				= secondLink(*pGraph, (char *)crawler->content, i);
			crawler = crawler->next;
		}
	}
}

void	printListInt(t_list *pList, t_graph pGraph)
{
	int	i, counter = 0;
	int	*way;


	while (pList)
	{
		i = 0;
		way = (int *)pList->content;
		ft_printf("{green}path size %d {white}\t", pList->content_size/4);
		while ((i * sizeof(int)) < pList->content_size)
		{
			ft_printf("%s -> ", pGraph.array[way[i++]]->name);
		}
		ft_printf("\n");//, pGraph.array[way[i]]->name, way[i + 1]);
		pList = pList->next;
		counter++;
	}
	ft_printf("#paths %d", counter);
}

void findAllPath(int current, bool *pBoolean, t_graph *pGraph, t_path *way)
{
	int i;

	i = 0;
	if (current == pGraph->V - 1)
		{
			way->size++;
			way->path[way->size - 1] = current;
			ft_lstadd(&gAllPath, ft_lstnew(way->path, ((size_t)way->size) * sizeof(int)));
			way->path[way->size - 1] = 0;
			way->size--;
		}
	else
	{
		while (i < pGraph->array[current]->links && way->size < 100)
		{
			if (!pBoolean[pGraph->array[current]->nextV[i]])
			{
				way->size++;
				way->path[way->size - 1] = current;
				pBoolean[current] = (bool)1;
				findAllPath(pGraph->array[current]->nextV[i], pBoolean, pGraph, way);
			}
			i++;
		}
	}
	pBoolean[current] = (bool)0;
	way->size -= 1;
}

void	allPath(t_graph *pGraph)
{
	bool		visitedVert[pGraph->V];
	t_path		*way;
//	t_list		*endList;
//	int 		listSize = 0;

	ft_bzero(visitedVert, pGraph->V);
	way = (t_path *)malloc(sizeof(t_path));
	way->path = malloc(1000 * sizeof(int));
	ft_bzero(way->path, 1000 * sizeof(int));
	way->size = 0;
//	gbestpath = 200;
	findAllPath(0, visitedVert, pGraph, way);
//	endList = gAllPath;
//	while (++listSize && endList->next)
//		endList = endList->next;
	sortList(gAllPath);
	printListInt(gAllPath, *pGraph);
//	comparePath(gAllPath->next->next->next->next->content, gAllPath->next->next->next->next->content_size);
}

void sortList(t_list *pList)
{
	t_list	*crawler = pList;

	while (crawler->next)
	{
		if (crawler->content_size > crawler->next->content_size)
		{
			ft_swap(crawler->content, crawler->next->content);
			ft_swap((int *)&(crawler->content_size), (int *)&(crawler->next->content_size));
			crawler = pList;
		}
		else
			crawler = crawler->next;
	}
}

t_graph	*signGraph(int size, t_list *rooms, t_list *pipes)
{
	t_graph	*graph;
	int 	i = 0;

	if (!(graph = (t_graph *)malloc(sizeof(t_graph))) ||
	!(graph->array = (t_vertex **)malloc(sizeof(t_vertex *) * size)))
		ERROR;
	graph->V = size;
	while (i < size)
	{
		graph->array[i++] = (t_vertex *)rooms->content;
		rooms = rooms->next;
	}
	countLinks(pipes, &graph);
	linkVertex(pipes, &graph);
	return (graph);
}

void PrintList(t_list *pList)
{
	ft_printf("\nOUTPUT LIST\n");
	while (pList)
	{
		ft_printf("%.*s\n", pList->content_size, (char *)pList->content);
		pList = pList->next;
	}
	ft_printf("END LIST\n");
}


void PrintVertexList(t_list *pList)
{
	t_vertex	*tmp;
	int 		i;

	i = 0;
	ft_printf("\nOUTPUT VERTEX LIST\n");
	while (pList)
	{
		tmp = pList->content;
		ft_printf("#%d %s\n", i++, tmp->name);
		pList = pList->next;
	}
	ft_printf("END VERTEX LIST\n");
}

int cutOff(t_list **pRooms, t_list **pPipes)
{
	t_list		*crawlerRoom;
	t_list		*crawlerPipe;
	t_list		*lastRoom;
	t_list		*beforeDeletedPipe;
	t_vertex	*tmp;
	int			count, res = 0;

	lastRoom = *pRooms;
	crawlerRoom = (*pRooms);
	while (crawlerRoom)
	{
		count = 0;
		crawlerPipe = *pPipes;
		tmp = crawlerRoom->content;
		beforeDeletedPipe = NULL;
		while (crawlerPipe)
		{
			if (ft_strnstr(crawlerPipe->content, tmp->name, crawlerPipe->content_size))
				count++;
			else if (count == 0)
				beforeDeletedPipe = crawlerPipe;
			crawlerPipe = crawlerPipe->next;
		}
		if (count == 1 && crawlerRoom != *pRooms && crawlerRoom->next)
		{
			if (beforeDeletedPipe)
			{
				free(beforeDeletedPipe->next->content);
				beforeDeletedPipe->next = beforeDeletedPipe->next->next;
			}
			else
			{
				beforeDeletedPipe = *pPipes;
				*pPipes = (*pPipes)->next;
				free(beforeDeletedPipe);
			}
			lastRoom->next = crawlerRoom->next;
			free(crawlerRoom->content);  // add here f that can delete t_vertex
			free(crawlerRoom);
			res++;
			crawlerRoom = lastRoom->next;
			continue ;
		}
		else
			tmp->links = count;
		lastRoom = crawlerRoom;
		crawlerRoom = crawlerRoom->next;
	}
	if (res != 0)
		return (res + cutOff(pRooms, pPipes));
	return (res);
}

int main(void)
{
	int				ants;
	t_list			*rooms;
	t_list			*pipes;
	int 			size_matr;
	struct s_graph	*graph;
//	t_list 			*allPath;
//	bool			*closedVert;

//    if (!(fd = open(FILENAME, O_RDONLY)))
//    	ERROR;
	fd = 0;
	ants = get_ants();
	rooms = NULL;
	pipes = NULL;
	size_matr = parce(&rooms, &pipes);
	printf("\n");
//	PrintVertexList(rooms);
//	size_matr -= cutOff(&rooms, &pipes);
//	PrintList(pipes);
//	PrintVertexList(rooms);
	graph = signGraph(size_matr, rooms, pipes);
	graph->totalAnts = ants;
//	allPath(graph);
//	PrintGraph(graph);
	findParallel(&graph);
//	allPath	= NULL;
//	closedVert = ft_memalloc((size_t)(graph->V));
//	ft_lstaddback(&allPath, findParallel1(0, &graph, &allPath, closedVert));
//	printAllPath(allPath->content, graph);

//	find2(&graph);
//	sortList(gAllPath);
//	printListInt(gAllPath, *graph);
//	ft_printf(ants <= gresult ? "{green}SUCCESS{eoc}%c" : "{red}FAIL{eoc}%c", '\n');
//	printAllPath(allPath, *pGraph);
	printf("\n#2 %d < %d [%d]", gmoves, gresult, ants);
	return gmoves >= gresult ? 1 : 0;
//	link_rooms(links, size_matr, pipes->next, rooms);
//	print_matr(links, size_matr);
//	path_finder(links, size_matr);
//	print_matr(links, size_matr);
//	PrintVertexList(rooms);
//	PrintVertexList(pipes);
//	system("leaks -q lemin > leaks.txt");
}
