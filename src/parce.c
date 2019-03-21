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

#include "lem-in.h"

t_vertex	*newVertex(char *str)
{
	t_vertex	*New;
	char 		*tmp;

	if (!(New = (t_vertex *)malloc(sizeof(t_vertex))))
		return (NULL);
	if (!(New->point = (t_coord *)malloc(sizeof(t_coord))))
		return (NULL);
	New->links = 0;
	New->ants = -1;
	New->linksAdded = 0;
	New->distance = INT_MAX;
	tmp = ft_strchr(str, ' ');
	New->name = ft_strndup(str, tmp - str);
	New->point->x = ft_atoi(tmp);
	New->point->y = ft_atoi(ft_strchr(tmp + 1, ' '));
	return (New);
}

void	delAdress(void *obj, size_t size)
{
	char *tmp;

	if (size && (tmp = *(char **)obj))
		free(tmp);
	free(obj);
	obj = NULL;
}

t_list	*parce(t_list **pipes, t_graph *pGraph)
{
	int 	room;
	char	*tmp;
	t_list	*crawler;

	room = 1;
	crawler = (*pipes)->next;
	pGraph->totalAnts = ft_atoi(*(char **)((*pipes)->content));
//	ft_lstdelone(pipes, delAdress);
	while (!ft_strchr(tmp = *(char **)(crawler->content), '-'))
	{
		if (!ft_strcmp(tmp, "##start") && (crawler = crawler->next))
			pGraph->array[0] = newVertex(*(char **)(crawler->content));
		else if (!ft_strcmp(tmp, "##end") && (crawler = crawler->next))
			pGraph->array[pGraph->V - 1] = newVertex(*(char **)(crawler->content));
		else if (ft_strchr(tmp, ' ') && *tmp != '#')
			pGraph->array[room++] = newVertex(tmp);
		crawler = crawler->next;
	}
	return (crawler);
}
