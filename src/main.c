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
		if (ft_strchr(tmp, ' ') && *tmp != '#' && !ft_strchr(tmp, '-'))
		{
			if ((*input && !valid_vert(tmp, input)) || start_end_link[2])
				break ;
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
	|| start_end_link[2] <= 1 ? 0 : num_vert);
}

void			bonuses(char **param, int count)
{
	int i;

	i = 1;
	while (i < count)
	{
		if (ft_strnstr(param[i], "--", 2) && ft_strchr(param[i], 'c'))
			g_param[0] = true;
		if (ft_strnstr(param[i], "--", 2) && ft_strchr(param[i], 'r'))
			g_param[1] = true;
		if (ft_strnstr(param[i], "--", 2) && ft_strchr(param[i], 'e'))
			g_param[2] = true;
		if (ft_strnstr(param[i], "--", 2) && ft_strchr(param[i], 'p'))
			g_param[3] = true;
		i++;
	}
}

int				main(int argc, char **argv)
{
	int				count_vert;
	t_list			*links;
	t_list			*input_list;
	t_graph			*graph;

	input_list = NULL;
	if (argc > 1)
	{
		bonuses(argv, argc);
		if (!g_param[0] && !g_param[1] && !g_param[2] && !g_param[3])
			exit(ft_printf("{red}Usage: lem-in [--c] [--r] [--e] [--p]\n"
				"--c: colorise ants\n--r: output results\n--e: error detail\n"
	"--p: print paths{eoc}%c", '\n'));
	}
	if (!(count_vert = read_farm(&input_list)) ||
	!(new_graph(count_vert, &graph)) || !check_ants(input_list, graph))
		exit(FREE_EXIT && (g_param[2] ? ft_printf("bad input\n") : 1));
	links = parce(input_list, graph);
	graph->array[0]->ants = graph->total_ants;
	if (!link_vertex(links, graph) || !bild_and_run(graph, input_list))
		exit(FREE_EXIT && (g_param[2] ? ft_printf("linking fail\n") : 1));
	if (g_param[1])
		ft_printf("{cyan}\nlem-in:\t%d\nbest:\t%d{eoc}\n", g_result, g_iter);
	system("leaks -q lem-in");
	return (0);
}
