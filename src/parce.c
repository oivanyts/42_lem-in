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

bool    comand(char *str, char **start, char **end)
{
	if (!ft_strncmp(&str[2], "start", 5))
	{
		free(str);
		if (get_next_line(fd, &str) == -1)
			ERROR;
		*start = str;
	}
	else if (!ft_strncmp(&str[2], "end", 3))
	{
		free(str);
		if (get_next_line(fd, &str) == -1)
			ERROR;
		*end = str;
	}
	return (1);
}




t_strlink	*add_link(char *string, t_strlink *list)
{
	t_strlink	*new;
	if (!(new = (t_strlink *)malloc(sizeof(t_strlink))))
		return (NULL);
	new->next = NULL;
	new->str = string;
	list->next = new;
	return (new);
}

int    parce(t_strlink	*rooms, t_strlink	*pipes)
{
	char		*tmp;
	t_strlink	*crawler1;
	char		*start;
	char		*end;
	int			count_rooms;

	count_rooms = 0;
	crawler1 = rooms;
	while (get_next_line(fd, &tmp) > 0)
	{
		if (tmp[0] == '#' && tmp[1] == '#' && ++count_rooms)
			comand(tmp, &start, &end);
		else if (tmp[0] == '#')
		{
			free(tmp);
			continue ;
		}
		else if (tmp[0] != 'L' && ft_strchr(tmp, ' ') && ++count_rooms)
			crawler1 = add_link(tmp, crawler1);
		else if (ft_strchr(tmp, '-'))
			pipes = add_link(tmp, pipes);
	}
	add_link(end, crawler1);
	rooms->str = start;
    return (count_rooms);
}