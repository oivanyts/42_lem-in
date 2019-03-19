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


void PrintList(t_list *pList)
{
	ft_printf("\nOUTPUT LIST\n");
	while (pList)
	{
		ft_printf("%.*s\n", ft_strlen(*(char **)pList->content), *(char **)pList->content);
		pList = pList->next;
	}
	ft_printf("END LIST\n");
}

t_vertex	*newVertex(char *str)
{
	t_vertex	*New;
	char 		*tmp;

	if (!(New = (t_vertex *)malloc(sizeof(t_vertex))) || !(New->point =
			(t_coord *)malloc(sizeof(t_coord))))
		return (NULL);
	New->links = 0;
	New->ants = -1;
	New->linksAdded = 0;
	New->distance = INT_MAX;
	tmp = ft_strchr(str, ' ');
	New->name = ft_strndup(str, tmp - str);
	New->point->x = ft_atoi(tmp);
	New->point->y = ft_atoi(ft_strchr(tmp + 1, ' '));
//	free(str);
	return (New);
}

bool    comand(char *str, t_list **rooms, t_list **input)
{
	ft_lstaddback(input, ft_lstnew(&str, 8));
	if (!ft_strncmp(&str[2], "start", 5))
	{
		if (get_next_line(fd, &str) == -1)
			ERROR;
		ft_lstadd(rooms, ft_lstnew(newVertex(str), sizeof(t_vertex)));
	}
	else if (!ft_strncmp(&str[2], "end", 3))
	{
//		free(str);
		if (get_next_line(fd, &str) == -1)
			ERROR;
		ft_lstaddback(rooms, ft_lstnew(newVertex(str), sizeof(t_vertex)));
	}
	return (1);
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

int			parce(t_list **rooms, t_list **pipes)
{
	char		*tmp;
	t_list		*input = NULL;
	int 		count_rooms = 0;

	if ((gants = get_ants()) <= 0)
		ERROR;
	while (get_next_line(fd, &tmp) == 1)
	{
		if (tmp[0] == '#' && tmp[1] == '#' && ++count_rooms)
			comand(tmp, rooms, &input);
		else if (tmp[0] == '#')
		{
			if (ft_strnstr(tmp, "#Here is the number of lines required", 37))
				gmoves = ft_atoi(tmp + 38);
			free(tmp);
		}
		else if (tmp[0] != 'L' && ft_strchr(tmp, ' ') && ++count_rooms)
			ft_lstaddhere(rooms, ft_lstnew(newVertex(tmp), sizeof(t_vertex)));
		else if (ft_strchr(tmp, '-'))
			ft_lstaddback(pipes, ft_lstnew(tmp, ft_strlen(tmp) + 1));
		ft_lstaddback(&input, ft_lstnew(&tmp, 8));
	}
	PrintList(input);
	return (count_rooms);
}
