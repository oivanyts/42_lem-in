/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oivanyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 04:48:26 by oivanyts          #+#    #+#             */
/*   Updated: 2019/03/22 04:48:35 by oivanyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			print_input(t_list *p_list)
{
	t_list	*tmp1;

	tmp1 = p_list;
	while (tmp1)
	{
		p_list = p_list->next;
		ft_printf("%.*s\n", ft_strlen(*(char **)tmp1->content),
				*(char **)tmp1->content);
		tmp1 = p_list;
	}
}

static t_graph	*new_graph(int vert)
{
	t_graph	*graph;

	if (!(graph = ft_memalloc(sizeof(t_graph))))
		return (NULL);
	graph->v = vert;
	graph->array = ft_memalloc(sizeof(t_vertex *) * graph->v);
	return (graph);
}

static bool		valid_vert(char *string, t_list **list)
{
	t_list	*crawler;
	size_t	name_size;
	void	*tmp;

	if (!*string || *string == ' ')
		return (false);
	name_size = ft_strchr(string, ' ') - string;
	crawler = (*list)->next;
	while (crawler)
	{
		tmp = *(void **)crawler->content;
		if (*(char *)tmp != '#' && (!ft_memcmp(string, tmp, name_size)
		|| !ft_strcmp(string + name_size, tmp + name_size)))
			return (false);
		crawler = crawler->next;
	}
	return (true);
}

static int		read_farm(t_list **input)
{
	char	*tmp;
	int		num_vert;
	int		start_end[2];

	num_vert = -1;
	ft_bzero(start_end, 2 * sizeof(int));
	while (get_next_line(0, &tmp) == 1)
	{
		if (!ft_strchr(tmp, '-') && *tmp != '#')
		{
			num_vert++;
			if (*input && !valid_vert(tmp, input))
			{
				free(tmp);
				return (0);
			}
		}
		else if (!ft_strcmp(tmp, "##end"))
			start_end[0] += 1;
		else if (!ft_strcmp(tmp, "##start"))
			start_end[1] += 1;
		ft_lstaddback(input, ft_lstnew(&tmp, 8));
	}
	free(tmp);
	return (start_end[0] != 1 || start_end[1] != 1 ? 0 : num_vert);
}

int				main(void)
{
	int				count_vert;
	t_list			*links;
	t_list			*input_list;
	t_graph			*graph;

	input_list = NULL;
	if (!(count_vert = read_farm(&input_list)))
		ERROR;
	if (!(graph = new_graph(count_vert)))
		ERROR;
	links = parce(input_list, graph);
	graph->array[0]->ants = graph->total_ants;
	if (!link_vertex(links, graph))
		ERROR;
	print_input(input_list);
	if (!bild_and_run(graph))
		ERROR;
	ft_printf("result = %d\n", g_result);
	return (g_result);
}
