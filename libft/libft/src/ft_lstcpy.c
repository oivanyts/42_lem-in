/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oivanyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 08:28:45 by oivanyts          #+#    #+#             */
/*   Updated: 2019/03/11 08:28:50 by oivanyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

t_list	*ft_lstcpy(t_list *src)
{
	t_list *result;

	if (src == NULL)
		return (NULL);
	result = ft_lstnew(src->content, src->content_size);
	result->next = ft_lstcpy(src->next);
	return (result);
}
