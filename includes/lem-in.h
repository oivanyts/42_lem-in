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
//# define FILENAME "test1"
//# define FILENAME "test"
# include "../libft/includes/libftprintf.h"
# include <stdbool.h>

typedef struct			s_coord{
	int					x;
	int 				y;
} 						t_coord;

typedef struct			s_Path
{
	int					size;
	int 				*path;
}						t_Path;

typedef struct			s_Vertex
{
	char 				*name;
	t_coord				*point;
	int 				distance;
	int					links;
	int					linksAdded;
	int					*Neighbor;
}						t_Vertex;

typedef struct			s_Graph
{
	int 				V;
	t_Vertex			**array;
}						t_Graph;

int 				gbestpath;
void				fillDistance(t_Graph **pGraph);
t_list				*gAllPath;
int					parce(t_list **rooms, t_list **pipes);
int					fd;

void				PrintVertexList(t_list *pList);

#endif
