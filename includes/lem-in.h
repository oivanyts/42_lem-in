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

# define ERROR exit (ft_printf(">>f - %s l - %d\n", __func__, __LINE__))
//# define FILENAME "flow_one.txt"
//# define FILENAME "flow-1000.txt"
//# define FILENAME "big.txt"
# define FILENAME "big_s.txt"
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
	int 				distance;
	int					links;
	int					linksAdded;
	int					*nextV;
}						t_vertex;

typedef struct			s_graph
{
	int 				V;
	t_vertex			**array;
}						t_graph;

int 				gresult;
int					gmoves;
void				findParallel(t_graph **pGraph);
bool				fillDistance(t_graph **pGraph, bool **closedVert,
		t_path **path);
t_list				*gAllPath;
int					parce(t_list **rooms, t_list **pipes);
int					fd;

void				PrintVertexList(t_list *pList);

#endif
