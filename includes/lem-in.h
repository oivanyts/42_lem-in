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

# include "../libft/includes/libftprintf.h"
# include <stdbool.h>

typedef struct			s_point{
	int					x;
	int 				y;
} 						t_cord;

typedef struct			s_Vertex
{
	char 				*Name;
	int 				Distance;
	int					Links;
	int					*Neighbor;
}						t_Vertex;

struct					s_Graph
{
	int 				V;
	struct s_Vertex		*array;
};

int					parce(t_list **rooms, t_list **pipes);
int					fd;

void				PrintVertexList(t_list *pList);

#endif
