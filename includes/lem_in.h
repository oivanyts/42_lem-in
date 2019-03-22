/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oivanyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 15:52:23 by oivanyts          #+#    #+#             */
/*   Updated: 2019/02/04 15:52:34 by oivanyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# define ERROR exit (ft_printf("ERROR\n") && clean_before_exit(&graph, &input_list) && system("leaks -q lemin"))

# include "../libft/includes/libftprintf.h"
# include <stdbool.h>

typedef struct	s_coord
{
	int			x;
	int			y;
}				t_coord;

typedef struct	s_path
{
	int			size;
	int			*path;
}				t_path;

typedef struct	s_vertex
{
	void		*name;
	t_coord		*point;
	int			ants;
	int			dist;
	int			links;
	int			links_now;
	int			*link_v;
}				t_vertex;

typedef struct	s_graph
{
	int			v;
	int			total_ants;
	t_vertex	**array;
}				t_graph;

int				clean_before_exit(t_graph **graph, t_list **linked_list);
int				g_result;
bool			bild_and_run(t_graph *graph);
bool			link_vertex(t_list *list, t_graph *graph);
bool			fill_dist(t_graph *graph, bool **closed_v, t_list **all_path);
void			del_str_adress(void *obj, size_t size);
t_list			*parce(t_list *input_list, t_graph *graph);
void			run_all_path(t_list *all_path, t_graph *graph);

#endif