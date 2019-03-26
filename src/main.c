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

static bool		new_graph(int vert, t_graph **graph)
{
	if (!(*graph = ft_memalloc(sizeof(t_graph))))
		return (false);
	(*graph)->v = vert;
	if (!((*graph)->array = ft_memalloc(sizeof(t_vertex *) * (*graph)->v)))
	{
		ft_memdel((void **)graph);
		return (false);
	}
	return (true);
}

static bool		valid_vert(char *string, t_list **list)
{
	t_list	*crawler;
	size_t	name_size;
	void	*tmp;

	if (!*string || *string == ' '
	|| !ft_strchr(string, ' ') || !(name_size = ft_strchr(string, ' ') - string)
	|| *string == 'L')
		return (false);
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
	int		start_end_link[3];

	num_vert = 0;
	ft_bzero(start_end_link, 3 * sizeof(int));
	while (get_next_line(0, &tmp) == 1)
	{
		if (ft_strchr(tmp, ' ') && *tmp != '#')
		{
			if (*input && !valid_vert(tmp, input) && !start_end_link[2])
			{
				break ;
			}
			num_vert++;
		}
		else if (!ft_strcmp(tmp, "##end"))
			start_end_link[0] += 1;
		else if (!ft_strcmp(tmp, "##start"))
			start_end_link[1] += 1;
		else if (ft_strchr(tmp, '-'))
			start_end_link[2] += 1;
		ft_lstaddback(input, ft_lstnew(&tmp, 8));
	}
	free(tmp);
	return (start_end_link[0] != 1 || start_end_link[1] != 1
	|| start_end_link[2] < 1 ? 0 : num_vert);
}

int				main(int argc, char **argv)
{
	int				count_vert;
	int 			res_out;
	t_list			*links;
	t_list			*input_list;
	t_graph			*graph;

	input_list = NULL;
	res_out = 0;
	if (argc > 1 && ft_strnstr(argv[1], "--", 2))
	{
		g_color = ft_strchr(argv[1], 'c') ? true : false;
		res_out = ft_strchr(argv[1], 't') ? true : false;
	}
	if (!(count_vert = read_farm(&input_list)) ||
	!(new_graph(count_vert, &graph)) || !check_ants(input_list, graph))
		ERROR;
	links = parce(input_list, graph);
	graph->array[0]->ants = graph->total_ants;
	if (!link_vertex(links, graph) || !bild_and_run(graph, input_list))
		ERROR;
	if (res_out)
		ft_printf("{cyan}my = %d{red}\ngenerate = %d{eoc}\n", g_result, g_iter);
	system("leaks -q lem-in");
	return (0);
}
