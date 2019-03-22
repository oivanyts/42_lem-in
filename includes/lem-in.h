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

# define ERROR exit (ft_printf("ERROR\n line %d in %s()\n", __LINE__, __func__) && clean_before_exit(&graph, &input_list) && system("leaks -q lemin"))
//# define FILENAME "flow-one.txt"
//# define FILENAME "flow-1000.txt"
//# define FILENAME "big1.txt"
# define FILENAME "big.uu"
//# define FILENAME "big_s.txt"
//# define FILENAME "test"
# include "../libft/includes/libftprintf.h"
# include <stdbool.h>

typedef struct			s_coord
{
	int					x;
	int 				y;
} 						t_coord;

typedef struct			s_path
{
	int					size;
	int 				*path;
}						t_path;

typedef struct			s_vertex
{
	void 				*name;
	t_coord				*point;
	int 				ants;
	int 				dist;
	int					links;
	int					linksAdded;
	int					*link_v;
}						t_vertex;

typedef struct			s_graph
{
	int 				V;
	int 				totalAnts;
	t_vertex			**array;
}						t_graph;

int					clean_before_exit(t_graph **graph, t_list **linked_list);
int 				gresult;

bool bild_and_run(t_graph *graph);
bool link_vertex(t_list *list, t_graph *graph);

bool				fill_distance(t_graph *graph, bool **closed_v, t_list **all_path);
void				findAllPath(int current, bool *pBoolean, t_graph *pGraph, t_path *way);
void				del_str_adress(void *obj, size_t size);

void				printAllPath(t_list *pList, t_graph *pGraph);
t_list				*parce(t_list *input_list, t_graph *graph);
void PrintGraph(t_graph *pGraph);
void	find2(t_graph **pGraph);
t_list	*findParallel1(int start, t_graph **pGraph, t_list **allPath, bool *closedVert);

void				run_all_path(t_list *all_path, t_graph *graph);
//void				delstr(void *toFree, size_t size);

int 				gants;
t_list				*gAllPath;
int					fd;
void				PrintVertexList(t_list *pList);

#endif
