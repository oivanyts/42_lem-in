/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oivanyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 07:03:46 by oivanyts          #+#    #+#             */
/*   Updated: 2019/03/22 07:03:50 by oivanyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static bool	count_links(t_list *in_lst, t_graph *graph)
{
	int		i;
	int		count;
	char	**arr;

	while (in_lst && (i = graph->v))
	{
		if (**(char **)in_lst->content == '#' && (in_lst = in_lst->next) >= 0)
			continue ;
		count = 0;
		if (!(arr = ft_strsplit(*(char **)in_lst->content, '-')) || !arr[0] ||
		!arr[1] || arr[2] || ft_strlen(arr[0]) + ft_strlen(arr[1]) + 1 !=
		ft_strlen(*(char **)in_lst->content))
		{
			ft_delarray((void **)arr);
			return (false);
		}
		while (i--)
			if ((ft_strequ(arr[0], graph->array[i]->name)
			|| ft_strequ(arr[1], graph->array[i]->name)) && ++count)
				graph->array[i]->links++;
		ft_delarray((void **)arr);
		if ((in_lst = in_lst->next) && count != 2)
			return (false);
	}
	return (true);
}

static int	second_vert(t_graph *graph, char *link, int i)
{
	int j;

	j = 0;
	while (j < graph->v)
	{
		if (i != j && ft_strstr(link, graph->array[j]->name))
			return (j);
		j++;
	}
	return (-1);
}

static int	delete_graph(t_graph **graph)
{
	int	i;

	i = (*graph)->v;
	while (i--)
	{
		if ((*graph)->array[i])
		{
			if ((*graph)->array[i]->name)
				ft_memdel(&(*graph)->array[i]->name);
			if ((*graph)->array[i]->link_v)
				ft_memdel((void **)&(*graph)->array[i]->link_v);
			if ((*graph)->array[i]->point)
				ft_memdel((void **)&(*graph)->array[i]->point);
			ft_memdel((void **)&(*graph)->array[i]);
		}
	}
	ft_memdel((void **)&(*graph)->array);
	ft_memdel((void **)&(*graph));
	return (true);
}

bool		link_vertex(t_list *list, t_graph *graph)
{
	int		i;
	t_list	*crawler;

	if (!count_links(list, graph))
		return (false);
	i = graph->v;
	while (--i >= 0)
		if (!(graph->array[i]->link_v = ft_memalloc(graph->array[i]->links *
				sizeof(int))))
			return (false);
	while (++i <= graph->v - 1)
	{
		crawler = list;
		while (crawler)
		{
			if (ft_strnstr(*(char **)crawler->content, graph->array[i]->name,
					ft_strlen(*(char **)crawler->content)))
				graph->array[i]->link_v[graph->array[i]->links_now++] =
						second_vert(graph, *(char **)crawler->content, i);
			crawler = crawler->next;
		}
	}
	return (true);
}

int			clean_on_exit(t_graph **graph, t_list **linked_list)
{
	ft_lstdel(linked_list, del_str_adress);
	if (*graph)
		delete_graph(graph);
	return (true);
}
