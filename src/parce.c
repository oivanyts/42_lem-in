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

t_list **SignListPipes(char *pipe, t_list **pList);

t_Vertex	*newVertex(char *str)
{
	t_Vertex	*New;
	char 		*tmp;

	if (!(New = (t_Vertex *)malloc(sizeof(t_Vertex))) || !(New->point =
			(t_coord *)malloc(sizeof(t_coord))))
		return (NULL);
	New->links = 0;
	New->linksAdded = 0;
	New->distance = INT_MAX;
	tmp = ft_strchr(str, ' ');
	New->name = ft_strndup(str, tmp - str);
	New->point->x = ft_atoi(tmp);
	New->point->y = ft_atoi(ft_strchr(tmp + 1, ' '));
	free(str);
	return (New);
}

bool    comand(char *str, t_list **rooms)
{
	if (!ft_strncmp(&str[2], "start", 5))
	{
		free(str);
		if (get_next_line(fd, &str) == -1)
			ERROR;
		ft_lstadd(rooms, ft_lstnew(newVertex(str), sizeof(t_Vertex)));
	}
	else if (!ft_strncmp(&str[2], "end", 3))
	{
		free(str);
		if (get_next_line(fd, &str) == -1)
			ERROR;
		ft_lstaddback(rooms, ft_lstnew(newVertex(str), sizeof(t_Vertex)));
	}
	return (1);
}

int			parce(t_list **rooms, t_list **pipes)
{
	char		*tmp;
	int			count_rooms;

	count_rooms = 0;
	while (get_next_line(fd, &tmp) > 0)
	{
		if (tmp[0] == '#' && tmp[1] == '#' && ++count_rooms)
			comand(tmp, rooms);
		else if (tmp[0] == '#')
			free(tmp);
		else if (tmp[0] != 'L' && ft_strchr(tmp, ' ') && ++count_rooms)
		{
			ft_lstaddhere(rooms, ft_lstnew(newVertex(tmp), sizeof(t_Vertex)));
		}
		else if (ft_strchr(tmp, '-'))
		{
			ft_lstaddback(pipes, ft_lstnew(tmp, ft_strlen(tmp)));
		}
	}
	return (count_rooms);
}
