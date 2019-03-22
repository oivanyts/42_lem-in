/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   theWay.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oivanyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 12:29:19 by oivanyts          #+#    #+#             */
/*   Updated: 2019/02/22 12:29:23 by oivanyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	best_link(int current, t_graph *graph, int dist)
{
	int	i;
	int min;
	int best_next;

	i = graph->array[current]->links;
	best_next = graph->array[current]->link_v[0];
	min = graph->array[best_next]->dist;
	while (i--)
	{
		if (current != graph->array[current]->link_v[i] &&
			graph->array[graph->array[current]->link_v[i]]->dist == dist)
		{
			best_next = graph->array[current]->link_v[i];
			min = graph->array[best_next]->dist;
		}
	}
	return (min == INT_MAX ? -1 : best_next);
}

static bool	shortest_path(t_graph *graph, bool **closed_vert, t_list **all_path)
{
	int		current;
	int		i;
	t_path	*tmp;

	i = 0;
	current = 0;
	if (graph->array[current]->dist == INT_MAX)
		return (0);
	tmp = malloc(sizeof(t_path));
	tmp->size = graph->array[current]->dist;
	tmp->path = ft_memalloc(sizeof(int) * tmp->size);
	while (current != graph->v - 1)
	{
		if ((current = best_link(current, graph, tmp->size - i - 1)) == -1)
			return (0);
		tmp->path[i] = current;
		(*closed_vert)[current] = true;
		i++;
	}
	ft_lstaddback(all_path, ft_lstnew(&tmp, sizeof(t_path *)));
	return (1);
}

static void	set_max_dist(t_graph *graph, bool *visited_v)
{
	int	i;

	i = 0;
	while (i < graph->v - 1)
	{
		if (graph->array[i]->dist != INT_MAX)
			graph->array[i]->dist = INT_MAX;
		i++;
	}
	graph->array[graph->v - 1]->dist = 0;
	ft_bzero(visited_v, (size_t)graph->v);
}

bool		fill_dist(t_graph *graph, bool **closed_v, t_list **all_path)
{
	t_coord		c;
	int			queue[graph->v];
	int			q_size;
	t_vertex	*tmp;
	bool		visit_v[graph->v];

	c.x = 0;
	q_size = 1;
	set_max_dist(graph, visit_v);
	queue[0] = graph->v - 1;
	while (c.x < q_size && (tmp = graph->array[queue[c.x]]))
	{
		c.y = 0;
		while (c.y < graph->array[queue[c.x]]->links)
		{
			if (!(visit_v)[tmp->link_v[c.y]] && !(*closed_v)[tmp->link_v[c.y]])
				if (graph->array[tmp->link_v[c.y]]->dist > tmp->dist + 1
				&& (queue[q_size++] = tmp->link_v[c.y]) > -1)
					graph->array[tmp->link_v[c.y]]->dist = tmp->dist + 1;
			c.y++;
		}
		if ((visit_v[queue[c.x]] = true) && !queue[c.x++])
			break ;
	}
	return (!shortest_path(graph, closed_v, all_path) ? false : true);
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

bool		bild_and_run(t_graph *graph)
{
	bool		*closed_vert;
	t_list		*all_path;

	all_path = NULL;
	if (!(closed_vert = ft_memalloc((size_t)graph->v)))
		return (0);
	while (fill_dist(graph, &closed_vert, &all_path))
	{
		if (all_path && (*(t_path **)(all_path->content))->size == 1)
			break ;
		closed_vert[graph->v - 1] = false;
		closed_vert[0] = false;
	}
	if (!all_path)
		return (0);
	run_all_path(all_path, graph);
	ft_lstdel(&all_path, del_path);
	ft_memdel((void **)&closed_vert);
	return (1);
}
