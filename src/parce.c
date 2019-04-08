/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oivanyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 10:03:21 by oivanyts          #+#    #+#             */
/*   Updated: 2019/02/05 10:03:24 by oivanyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		ft_delarray(void **arr)
{
	char	**tmp;
	int		i;

	tmp = (char **)arr;
	i = 0;
	while (tmp[i])
		free(tmp[i++]);
	free(tmp);
}

static bool	alloc_vert(t_vertex **fresh, char *name, int x, int y)
{
	if (!(*fresh = ft_memalloc(sizeof(t_vertex))))
		return (false);
	if (!((*fresh)->point = ft_memalloc(sizeof(t_coord))))
		return (false);
	(*fresh)->dist = INT_MAX;
	(*fresh)->point->x = x;
	(*fresh)->point->y = y;
	if (!((*fresh)->name = ft_strdup(name)))
		return (false);
	return (true);
}

static bool	new_vertex(char *str, t_vertex **fresh)
{
	char	**arr;
	int		cord[2];

	if (!(arr = ft_strsplit(str, ' ')) || !arr[1] || !arr[2] || arr[3])
	{
		ft_delarray((void **)arr);
		return (false);
	}
	cord[0] = ft_atoi(arr[1]);
	cord[1] = ft_atoi(arr[2]);
	if (arr[3] || ft_strlen(arr[1]) != (size_t)ft_num_size(cord[0])
	|| ft_strlen(arr[2]) != (size_t)ft_num_size(cord[1])
	|| !ft_isdigit(arr[1][0]) || !ft_isdigit(arr[2][0]))
	{
		ft_delarray((void **)arr);
		return (false);
	}
	if (ft_strlen(arr[0]) + ft_strlen(arr[1]) + ft_strlen(arr[2]) !=
	ft_strlen(str) - 2 || !(alloc_vert(fresh, arr[0], cord[0], cord[1])))
	{
		ft_delarray((void **)arr);
		return (false);
	}
	ft_delarray((void **)arr);
	return (true);
}

static void	search_result(t_list *link)
{
	char	*str;

	str = *(char **)(link->content);
	if (ft_strstr(str, "#Here is the number of lines required:"))
		g_iter = ft_atoi(str + 38);
}

t_list		*parce(t_list *input_list, t_graph *graph)
{
	int		room;
	char	*tmp;
	t_list	*crawler;

	room = 1;
	search_result(crawler = input_list->next);
	while (!ft_strchr(tmp = *(char **)(crawler->content), '-'))
	{
		if (!ft_strcmp(tmp, "##start") && (crawler = crawler->next))
		{
			if (!(new_vertex(*(char **)(crawler->content), &graph->array[0])))
				exit(FREE_EXIT && g_param[2] ? ft_printf("room fail\n") : 1);
		}
		else if (!ft_strcmp(tmp, "##end") && (crawler = crawler->next))
		{
			if (!(new_vertex(*(char **)(crawler->content),
					&graph->array[graph->v - 1])))
				exit(FREE_EXIT && g_param[2] ? ft_printf("room fail\n") : 1);
		}
		else if (ft_strchr(tmp, ' ') && *tmp != '#')
			if (!(new_vertex(tmp, &graph->array[room++])))
				exit(FREE_EXIT && g_param[2] ? ft_printf("room fail\n") : 1);
		crawler = crawler->next;
	}
	return (crawler);
}
