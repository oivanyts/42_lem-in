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

static t_vertex	*new_vertex(char *str)
{
	t_vertex	*fresh;
	char		*tmp;

	if (!(fresh = (t_vertex *)malloc(sizeof(t_vertex)))
	|| !(fresh->point = (t_coord *)malloc(sizeof(t_coord))) || *str == '#'
	|| *str == ' ')
		return (NULL);
	fresh->links = 0;
	fresh->ants = -1;
	fresh->links_now = 0;
	fresh->dist = INT_MAX;
	tmp = ft_strchr(str, ' ');
	fresh->name = ft_strndup(str, tmp - str);
	fresh->point->x = ft_atoi(tmp);
	fresh->point->y = ft_atoi(ft_strchr(tmp + 1, ' '));
	return (fresh);
}

void			del_str_adress(void *obj, size_t size)
{
	char *tmp;

	if (size && (tmp = *(char **)obj))
		free(tmp);
	free(obj);
	obj = NULL;
}

t_list			*parce(t_list *input_list, t_graph *graph)
{
	int		room;
	char	*tmp;
	t_list	*crawler;

	room = 1;
	graph->total_ants = ft_atoi(*(char **)(input_list->content));
	crawler = input_list->next;
	while (!ft_strchr(tmp = *(char **)(crawler->content), '-'))
	{
		if (!ft_strcmp(tmp, "##start") && (crawler = crawler->next))
		{
			if (!(graph->array[0] = new_vertex(*(char **)(crawler->content))))
				ERROR;
		}
		else if (!ft_strcmp(tmp, "##end") && (crawler = crawler->next))
		{
			if (!(graph->array[graph->v - 1] = new_vertex(*(char **)(crawler->content))))
				ERROR;
		}
		else if (ft_strchr(tmp, ' ') && *tmp != '#')
			if (!(graph->array[room++] = new_vertex(tmp)))
				ERROR;
		crawler = crawler->next;
	}
	return (crawler);
}
