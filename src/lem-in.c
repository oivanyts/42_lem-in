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

void	print_list(t_strlink *lst)
{
	int num = 0;
	if (!lst)
		lst = lst->next;
	while (lst)
	{
		ft_printf("n%d - %s\n", num++, lst->str);
		lst = lst->next;
	}
}

void	link_rooms(int **matr, int size, t_strlink *pipes, t_strlink *rooms)
{
	struct s_point	tmp;
	t_strlink		*crawler;
	int 			i;
	char			*room1;
	char			*room2;

	while (pipes)
	{
		i = 0;
		tmp.x = -1;
		tmp.y = -1;
		crawler = rooms;
		room1 = pipes->str;
		room2 = ft_strchr(room1, '-') + 1;
		while (crawler && (tmp.x < 0 || tmp.y < 0) && size)
		{
			if (!ft_strncmp(crawler->str, room1, room2 - room1 - 1))
				tmp.x = i;
			if (ft_strnstr(crawler->str, room2, ft_strlen(room2)))
				tmp.y = i;
			crawler = crawler->next;
			i++;
		}
		matr[tmp.x][tmp.y] = 11;
		ft_swap(&tmp.x, &tmp.y);
		matr[tmp.x][tmp.y] = 11;
		pipes = pipes->next;
	}
}

void	print_matr(int **matr, int size)
{
	int i = 0;
	int j;
	ft_printf("{blue} \t%d", 0);
	while (size > ++i)
		ft_printf(" %d", i);
	ft_printf("{eoc}\t%d\n", i);
	i = 0;
	while (size > i)
	{
		j = 0;
		ft_printf("%d\t", i);
		while (j <= size)
		{
			if (matr[i][j])
				ft_printf("{red}%d{eoc}\t", matr[i][j]);
			else if (i == j)
				ft_printf("{cyan}%c{eoc}\t", '\\');
			else
				ft_printf("%d\t", matr[i][j]);
			j++;
		}
		ft_printf("\n");
		i++;
	}

}

//void	path_finder(int	**matr, int size)
//{
//	int i[1000];
//
//
//}

void	ft_for()
{

}

struct s_Graph	*newGraph(int	size, t_strlink head, t_strlink tail)
{
	struct s_Graph	*graph;

	graph = (struct s_Graph *)malloc(sizeof(struct s_Graph));
	graph->V = size;

	graph->array = (struct s_Vertex *)malloc(sizeof(struct s_Vertex) * size);
	while (size--)
		graph->array[size].Name = NULL;
	return (graph);
}


int main(void)
{
	int				ants;
	t_strlink		*rooms;
	t_strlink		*pipes;
	int				**links;
	int 			size_matr;
	struct s_Graph	graph;


	if(!(rooms = (t_strlink *)malloc(sizeof(t_strlink))))
		ERROR;
	if(!(pipes = (t_strlink *)malloc(sizeof(t_strlink))))
		ERROR;
    if (!(fd = open("test", O_RDONLY)))
    	ERROR;
	ants = get_ants();
	size_matr = parce(rooms, pipes);
	links = matr_connection(size_matr);
	link_rooms(links, size_matr, pipes->next, rooms);
	print_matr(links, size_matr);
//	path_finder(links, size_matr);
	print_matr(links, size_matr);

//	print_list(rooms);
//	print_list(pipes);
	ft_printf("%d - ants\n", ants);
	return (1);
}