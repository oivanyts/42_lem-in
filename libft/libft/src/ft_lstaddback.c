/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstaddback.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oivanyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 11:47:17 by oivanyts          #+#    #+#             */
/*   Updated: 2019/02/05 11:47:20 by oivanyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_lstaddback(t_list **alst, t_list *new)
{
	t_list *crowler;

	if (new && *alst)
	{
		crowler = *alst;
		while (crowler->next)
			crowler = crowler->next;
		crowler->next = new;
	}
	else
		*alst = new;
}
