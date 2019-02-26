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

//void comparePath(int *pVoid, size_t size);

void findDistance(t_Graph **pGraph);

int 	**matr_connection(int size)
{
	int		**matr;
	int		i;
	int		j;

	i = 0;
	if (!(matr = (int **)malloc(sizeof(int *) * size)))
		return (NULL);
	while (size > i)
	{
		j = 0;
		if (!(matr[i] = (int *)malloc(sizeof(int) * (size + 1))))
		{
			while (i--)
				free(matr[i]);
			free(matr);
		}
		while (j <= size)
			matr[i][j++] = 0;
		i++;
	}
	ft_printf(" <<< alocated %d matr\n", i);
	return (matr);
}

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

void PrintGraph(t_Graph *pGraph)
{
	int 		size, i;
	t_Vertex	*tmp;

	ft_printf("\nPRINTING GRAPH\n\t size - %d\n", pGraph->V);
	size = 0;
	while (size < pGraph->V)
	{
		tmp = pGraph->array[size];
		ft_printf("#%d\tNAME\t  >%s<\t<%d:%d>{cyan}\n\tDIST\t%d\t\t{green}LINKS\t%d{red}\t\t{",
				size, tmp->name, tmp->point->x, tmp->point->y,  tmp->distance, tmp->links);
		i = 0;
//		while (i < pGraph->array[size]->links)
//			ft_printf(" %s,", pGraph->array[pGraph->array[size]->Neighbor[i++]]->name);
		ft_printf("%c}\n{eoc}", ' ');
		size++;
	}
}

void countLinks(t_list *pList, t_Graph **pGraph)
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

int secondLink(t_Graph *pGraph, char *link, int i)
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

void linkVertex(t_list *pList, t_Graph **pGraph)
{
	int 	i;
	t_list	*crawler;

	i = (*pGraph)->V;
	while (--i >= 0)
		(*pGraph)->array[i]->Neighbor = malloc((*pGraph)->array[i]->links);
	while (++i < (*pGraph)->V - 1)
	{
		crawler = pList;
		while (crawler)
		{
			if (ft_strnstr(crawler->content, (*pGraph)->array[i]->name, crawler->content_size))
				(*pGraph)->array[i]->Neighbor[(*pGraph)->array[i]->linksAdded++]
				= secondLink(*pGraph, (char *)crawler->content, i);
			crawler = crawler->next;
		}
	}
}

void	printListInt(t_list *pList, t_Graph pGraph)
{
	int	i, counter = 0;
	int	*way;


	while (pList)
	{
		i = 0;
		way = (int *)pList->content;
		ft_printf("path size %d \t", pList->content_size/4);
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

void findAllPath(int current, bool *pBoolean, t_Graph *pGraph, t_Path *way)
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
		while (pGraph->array[current]->links > i)
		{
			if (!pBoolean[pGraph->array[current]->Neighbor[i]])
			{
				way->size++;
				way->path[way->size - 1] = current;
				pBoolean[current] = (bool)1;
				findAllPath(pGraph->array[current]->Neighbor[i], pBoolean, pGraph, way);
			}
			i++;
		}
	}
	pBoolean[current] = (bool)0;
	way->size -= 1;
}

void	allPath(t_Graph *pGraph)
{
	bool		visitedVert[pGraph->V];
	t_Path		*way;

	ft_bzero(visitedVert, pGraph->V);
	way = (t_Path *)malloc(sizeof(t_Path));
	way->path = malloc(1000 * sizeof(int));
	ft_bzero(way->path, 8000);
	way->size = 0;
//	gbestpath = 200;
	findAllPath(0, visitedVert, pGraph, way);
	printListInt(gAllPath, *pGraph);
//	comparePath(gAllPath->next->next->next->next->content, gAllPath->next->next->next->next->content_size);
}

//void comparePath(int *pVoid, size_t size)
//{
//	allPath()
//}
//

t_Graph	*signGraph(int size, t_list *rooms, t_list *pipes)
{
	t_Graph	*graph;
	int 	i = 0;

	if (!(graph = (t_Graph *)malloc(sizeof(t_Graph))) ||
	!(graph->array = (t_Vertex **)malloc(sizeof(t_Vertex *) * size)))
		ERROR;
	graph->V = size;
	while (i < size)
	{
		graph->array[i++] = (t_Vertex *)rooms->content;
		rooms = rooms->next;
	}
	countLinks(pipes, &graph);
	linkVertex(pipes, &graph);
//	findDistance(&graph);
	allPath(graph);

	return (graph);
}

void findDistance(t_Graph **pGraph)
{
	int			i, j, current;
	t_Vertex	*queue[(*pGraph)->V];
	int 		queueSize;

	ft_bzero(queue, (*pGraph)->V * 8);
	queueSize = 1;
	queue[0] = (*pGraph)->array[(*pGraph)->V - 1];
	i = 0;
	(*pGraph)->array[(*pGraph)->V - 1]->distance = 0;
	while (i < queueSize)
	{
		j = 0;
		while (j < (*pGraph) -> array[i] -> links)
		{
			current = (*pGraph) -> array[i] -> Neighbor[j];
			if ((*pGraph)->array[current]->distance < (*pGraph)->array[i]->distance + 1)
			{
				(*pGraph)->array[current]->distance = (*pGraph)->array[i]->distance + 1;
				queue[queueSize++] = (*pGraph)->array[current];
			}
			j++;
		}
		i++;
	}
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
	t_Vertex	*tmp;
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

int main(void)
{
	int				ants;
	t_list			*rooms;
	t_list			*pipes;
//	int				**links;
	int 			size_matr;
	struct s_Graph	*graph;

    if (!(fd = open(FILENAME, O_RDONLY)))
    	ERROR;
	ants = get_ants();
	ft_printf("%d - ants\n", ants);
	rooms = NULL;
	pipes = NULL;
	size_matr = parce(&rooms, &pipes);
//	links = matr_connectiron(size_matr);
//	PrintVertexList(rooms);
//	PrintList(pipes);
	graph = signGraph(size_matr, rooms, pipes);
//	PrintGraph(graph);
//	link_rooms(links, size_matr, pipes->next, rooms);
//	print_matr(links, size_matr);
//	path_finder(links, size_matr);
//	print_matr(links, size_matr);
//	PrintVertexList(rooms);
//	PrintVertexList(pipes);
//	system("leaks -q lemin > leaks.txt");
	return (1);
}
