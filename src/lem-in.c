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

void PrintList(t_list *pList)
{
	t_list	*tmp1;

	tmp1 = pList;
	while (tmp1)
	{
		pList = pList->next;
		ft_printf("%.*s\n", ft_strlen(*(char **)tmp1->content), *(char **)tmp1->content);
		tmp1 = pList;
	}
}

int deleteGraph(t_graph **pGraph);

bool validVert(char *string, t_list **pList);

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

bool	countLinks(t_list *pList, t_graph *pGraph)
{
	t_list	*crawler;
	int		i;
	int 	count;

	crawler = pList;
	while (crawler)
	{
		i = 0;
		count = 0;
		while (i < pGraph->V)
		{
			if (ft_strstr(*(char **)crawler->content, pGraph->array[i]->name) && ++count)
				pGraph->array[i]->links++;
			i++;
		}
		if (!count)
			return (false);
		crawler = crawler->next;
	}
	return (true);
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

bool linkVertex(t_list *pList, t_graph **pGraph)
{
	int 	i;
	t_list	*crawler;

	i = (*pGraph)->V;
	while (--i >= 0)
		if (!((*pGraph)->array[i]->nextV = ft_memalloc((*pGraph)->array[i]->links * sizeof(int))))
			return (false);
	while (++i <= (*pGraph)->V - 1)
	{
		crawler = pList;
		while (crawler)
		{
			if (ft_strnstr(*(char **)crawler->content, (*pGraph)->array[i]->name, ft_strlen(*(char **)crawler->content)))
				(*pGraph)->array[i]->nextV[(*pGraph)->array[i]->linksAdded++]
				= secondLink(*pGraph, *(char **)crawler->content, i);
			crawler = crawler->next;
		}
	}
	return (true);
}

void	printListInt(t_list *pList, t_graph pGraph)
{
	int i;
	int counter;
	int	*way;

	counter = 0;
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

int	readFarm(t_list **input)
{
	char	*tmp;
	int 	numVert = -1;
	int 	startEnd[2];

	ft_bzero(startEnd, 2 * sizeof(int));
	while (get_next_line(fd, &tmp) == 1)
	{
		if (!ft_strchr(tmp, '-') && *tmp != '#')
		{
			numVert++;
			if (*input && !validVert(tmp, input) )
				ERROR;
		}
		else if (!ft_strcmp(tmp, "##end"))
			startEnd[0] += 1;
		else if (!ft_strcmp(tmp, "##start"))
			startEnd[1] += 1;
		ft_lstaddback(input, ft_lstnew(&tmp, 8));
		if (startEnd[0] > 1 || startEnd[1] > 1)
			ERROR;
	}
	free(tmp);
	if (startEnd[0] != 1 || startEnd[1] != 1)
		ERROR;
	PrintList(*input);
	return (numVert);
}

bool validVert(char *string, t_list **pList)
{
	t_list	*crawler;
	size_t	nameSize;
	void	*tmp;

	nameSize = ft_strchr(string, ' ') - string;
	crawler = (*pList)->next;
	while (crawler)
	{
		tmp = *(void **)crawler->content;
		if (*(char *)tmp != '#' && (!ft_memcmp(string, tmp, nameSize) ||
				!ft_strcmp(string + nameSize, tmp + nameSize)))
			return (false);
		crawler = crawler->next;
	}
	return (true);
}

int deleteGraph(t_graph **pGraph)
{
	int	i = (*pGraph)->V;

	while (i--)
	{
		if ((*pGraph)->array[i])
		{
			if ((*pGraph)->array[i]->name)
				ft_memdel(&(*pGraph)->array[i]->name);
			if ((*pGraph)->array[i]->nextV)
				ft_memdel((void **)&(*pGraph)->array[i]->nextV);
			if ((*pGraph)->array[i]->point)
				ft_memdel((void **)&(*pGraph)->array[i]->point);
			ft_memdel((void **)&(*pGraph)->array[i]);
		}
	}
	ft_memdel((void **)&(*pGraph)->array);
	ft_memdel((void **)&(*pGraph));
	return (true);
}

int main(void)
{
	int				Vert;
	t_list			*rooms;
	t_list			*pipes;
	t_graph			*graph;

    if (!(fd = open(FILENAME, O_RDONLY)))
    	ERROR;
//	fd = 0;
	pipes = NULL;
	Vert = readFarm(&pipes);
	graph = ft_memalloc(sizeof(t_graph));
	graph->V = Vert;
	graph->array = ft_memalloc(sizeof(t_vertex *) * graph->V);
	rooms = parce(&pipes, graph);
	graph->array[0]->ants = graph->totalAnts;
	if (!countLinks(rooms, graph) && !linkVertex(rooms, &graph))
		ERROR;
	ft_lstdel(&pipes, delAdress);
//	PrintGraph(graph);
	findParallel(&graph);
	deleteGraph(&graph);
	system("leaks lemin -q");
	ft_printf("result = %d\n", gresult);
	return gmoves >= gresult ? 1 : 0;
}
