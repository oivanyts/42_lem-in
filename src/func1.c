/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oivanyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 06:13:27 by oivanyts          #+#    #+#             */
/*   Updated: 2019/03/26 06:13:37 by oivanyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

bool		check_ants(t_list *list, t_graph *graph)
{
	char	*string;
	int		i;

	string = *(char **)list->content;
	graph->total_ants = ft_atoi(string);
	i = 0;
	while (string[i])
		if (!ft_isdigit(string[i++]))
			return (false);
	if (!graph->total_ants
		|| ft_num_size(graph->total_ants) != (int)ft_strlen(string))
		return (false);
	return (true);
}

void		del_path(void *path, size_t size)
{
	t_path *tmp;

	tmp = *(t_path **)path;
	if (size)
	{
		free(tmp->path);
		free(tmp);
	}
	free(path);
}

void		print_input(t_list *p_list)
{
	t_list	*tmp1;

	tmp1 = p_list;
	ft_printf("\n");
	while (tmp1)
	{
		p_list = p_list->next;
		ft_printf("%.*s\n", ft_strlen(*(char **)tmp1->content),
				  *(char **)tmp1->content);
		tmp1 = p_list;
	}
}

void		del_str_adress(void *obj, size_t size)
{
	char *tmp;

	if (size && (tmp = *(char **)obj))
		free(tmp);
	free(obj);
	obj = NULL;
}
