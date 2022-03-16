/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aregenia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 17:08:35 by aregenia          #+#    #+#             */
/*   Updated: 2021/10/10 19:50:26 by aregenia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;

	if (!*lst)
	{
		lst = NULL;
		return ;
	}
	while (*lst)
	{
		tmp = (*lst)->next;
		if ((*lst)->content)
			del((*lst)->content);
		if ((*lst)->amb_data)
			del((*lst)->amb_data);
		(*lst)->content = NULL;
		del(*lst);
		*lst = NULL;
		*lst = tmp;
	}
	lst = NULL;
}
