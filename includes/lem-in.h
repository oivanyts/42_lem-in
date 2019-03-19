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
//# define FILENAME "flow-one.txt"
//# define FILENAME "flow-1000.txt"
//# define FILENAME "big1.txt"
//# define FILENAME "big.uu"
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
	int 				ants;
	int 				distance;
	int					links;
	int					linksAdded;
	int					*nextV;
}						t_vertex;

typedef struct			s_graph
{
	int 				V;
	int 				totalAnts;
	t_vertex			**array;
}						t_graph;

int 				gresult;
int					gmoves;
void				findParallel(t_graph **pGraph);

bool				fillDistance(t_graph **pGraph, bool **closedVert,
		t_list **allPath);
void				findAllPath(int current, bool *pBoolean, t_graph *pGraph, t_path *way);

void				printAllPath(t_list *pList, t_graph *pGraph);
int					parce(t_list **rooms, t_list **pipes);
void PrintGraph(t_graph *pGraph);
void	find2(t_graph **pGraph);
t_list	*findParallel1(int start, t_graph **pGraph, t_list **allPath, bool *closedVert);

void				onePath(t_path *currWay, t_graph *pGraph, bool iter);
void				runAllPath(t_list *pAllPath, t_graph **pGraph);


int 				gants;
t_list				*gAllPath;
int					fd;
void				PrintVertexList(t_list *pList);

#endif
