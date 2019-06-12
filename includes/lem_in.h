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

# define FREE_EXIT ft_printf("ERROR\n") && clean_on_exit(&graph, &input_list) && system("leaks -q lem-in")
# define ERR_VERT {ft_delarray((void **)arr);return (false);}

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

int				g_iter;
int				g_result;
bool			g_param[4];
bool			ft_delarray(void **arr);
t_list			*parce(t_list *input_list, t_graph *graph);
bool			link_vertex(t_list *list, t_graph *graph);
bool			check_ants(t_list *list, t_graph *graph);
bool			bild_and_run(t_graph *graph, t_list *input_list);
void			print_input(t_list *p_list);
void			run_all_path(t_list *all_path, t_graph *graph);
void			del_path(void *path, size_t size);
void			del_str_adress(void *obj, size_t size);
int				clean_on_exit(t_graph **graph, t_list **linked_list);

#endif
