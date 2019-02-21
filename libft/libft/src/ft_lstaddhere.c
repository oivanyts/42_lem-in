/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstaddhere.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oivanyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 14:24:31 by oivanyts          #+#    #+#             */
/*   Updated: 2019/02/09 14:24:36 by oivanyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_lstaddhere(t_list **alst, t_list *new)
{
	t_list *crawler;

	if (new && *alst)
	{
		crawler = *alst;
		if (crawler->next)
			new->next = crawler->next;
		crawler->next = new;
	}
	else
		*alst = new;
}
