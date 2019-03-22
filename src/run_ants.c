/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runAnts.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oivanyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 08:37:56 by oivanyts          #+#    #+#             */
/*   Updated: 2019/03/22 08:37:58 by oivanyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	print_move(t_graph *graph, int dest_vert)
{
	if (dest_vert == graph->v - 1)
		ft_printf("\033[38;05;%dm", 1);
	ft_printf("L%03d-%s ", graph->array[dest_vert]->ants,
			graph->array[dest_vert]->name);
	ft_printf("\033[m");
}

static void	one_path(t_path *curr_way, t_graph *graph, bool open_start)
{
	int mover;

	mover = curr_way->size;
	while (mover--)
	{
		if (mover && graph->array[curr_way->path[mover - 1]]->ants > -1)
		{
			if (mover == curr_way->size - 1)
				graph->array[curr_way->path[mover]]->ants++;
			else
				graph->array[curr_way->path[mover]]->ants =
						graph->array[curr_way->path[mover - 1]]->ants;
			print_move(graph, curr_way->path[mover]);
			graph->array[curr_way->path[mover - 1]]->ants = -1;
		}
	}
	while (open_start && graph->array[0]->ants > 0)
	{
		graph->array[curr_way->path[0]]->ants = graph->total_ants -
				graph->array[0]->ants + 1;
		print_move(graph, curr_way->path[0]);
		graph->array[0]->ants--;
		if (curr_way->size != 1)
			break ;
	}
}

static int	count_iteration(t_list *all_path, t_graph *graph, int *size)
{
	float	min_moves;
	t_path	*prev;
	int		diff;
	float	best;

	best = INT_MAX;
	diff = 0;
	while (all_path)
	{
		(*size)++;
		prev = *(t_path **)all_path->content;
		min_moves = (float)(graph->total_ants + diff + prev->size - 1) / *size;
		diff += (prev->size - 1);
		all_path = all_path->next;
		if (min_moves < best)
			best = min_moves;
		else
		{
			(*size)--;
			break ;
		}
	}
	return ((int)best * 100) == (int)(best * 100.0) ? (int)best : (int)best + 1;
}

void		run_all_path(t_list *all_path, t_graph *graph)
{
	int		i;
	int		j;
	int		n_path;
	t_list	*crawler;

	j = 0;
	n_path = 0;
	g_result = count_iteration(all_path, graph, &n_path);
	while (j < g_result)
	{
		i = 0;
		crawler = all_path;
		while (i < n_path)
		{
			one_path(*(t_path **)(crawler->content), graph,
					(j <= g_result - (*(t_path **)(crawler->content))->size));
			crawler = crawler->next;
			i++;
		}
		ft_printf("\n");
		j++;
	}
}
