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

void PrintGraph(t_Graph *pGraph);


void linkVertex(t_list *pList, t_Graph **pGraph);


int 	**matr_connection(int size)
{
	int	**matr;
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
//
//void	PrintVertexList(t_list *lst)
//{
//	int num = 0;
//	if (!lst)
//		lst = lst->next;
//	while (lst)
//	{
//		ft_printf("n%d - %s\n", num++, lst->str);
//		lst = lst->next;
//	}
//}
//
//
//void	print_matr(int **matr, int size)
//{
//	int i = 0;
//	int j;
//	ft_printf("{blue} \t%d", 0);
//	while (size > ++i)
//		ft_printf(" %d", i);
//	ft_printf("{eoc}\t%d\n", i);
//	i = 0;
//	while (size > i)
//	{
//		j = 0;
//		ft_printf("%d\t", i);
//		while (j <= size)
//		{
//			if (matr[i][j])
//				ft_printf("{red}%d{eoc}\t", matr[i][j]);
//			else if (i == j)
//				ft_printf("{cyan}%c{eoc}\t", '\\');
//			else
//				ft_printf("%d\t", matr[i][j]);
//			j++;
//		}
//		ft_printf("\n");
//		i++;
//	}
//
//}


void PrintGraph(t_Graph *pGraph)
{
	int 		size;
	t_Vertex	*tmp;

	ft_printf("\nPRINTING GRAPH\n\t size - %d\n", pGraph->V);
	size = 0;
	while (size < pGraph->V)
	{
		tmp = pGraph->array[size];
		ft_printf("#%d\tNAME\t  %s\t<%d:%d>{cyan}\n\tDIST\t%d\n\t{green}LINKS\t%d{eoc}\n", size++, tmp->Name, tmp->point->x, tmp->point->y,  tmp->Distance, tmp->Links);
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
			if (ft_strstr(crawler->content, (*pGraph)->array[i]->Name))
				(*pGraph)->array[i]->Links++;
			i++;
		}
		crawler = crawler->next;
	}

}

void linkVertex(t_list *pList, t_Graph **pGraph)
{
	int 	i;
//	int 	res;
	char	*link1;
	char	*link2;

	t_list	*crawler;

	i = (*pGraph)->V;
	while (--i >= 0)
		(*pGraph)->array[i]->Neighbor = malloc((*pGraph)->array[i]->Links);
	crawler = pList;
	link1 = ft_strnew(100);
	link2 = ft_strnew(100);
	while (crawler)
	{
		i = 0;
		link2 = ft_strcpy(link2, ft_strchr(crawler->content, '-') + 1);
		link1 = ft_strncpy(link1, crawler->content, link2 - (char *)crawler->content - 1);
		crawler = crawler->next;
	}

}

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
	PrintGraph(graph);
	return (graph);
}

void PrintList(t_list *pList)
{
	ft_printf("\nOUTPUT LIST\n");
	while (pList)
	{
		ft_printf("%s\n", pList->content);
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
		ft_printf("#%d %s\n", i++, tmp->Name);
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

    if (!(fd = open("test", O_RDONLY)))
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
//	link_rooms(links, size_matr, pipes->next, rooms);
//	print_matr(links, size_matr);
//	path_finder(links, size_matr);
//	print_matr(links, size_matr);
//	PrintVertexList(rooms);
//	PrintVertexList(pipes);
	return (1);
}
