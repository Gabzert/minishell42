/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantech <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 14:36:22 by gfantech          #+#    #+#             */
/*   Updated: 2022/10/06 14:36:28 by gfantech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*index;
	t_list	*new;
	t_list	*back;

	new = ft_lstnew((*f)(lst->content));
	if (!new)
		return (NULL);
	index = new;
	back = lst->next;
	while (back != NULL)
	{
		index->next = ft_lstnew((*f)(back->content));
		if (!index->next)
		{
			ft_lstclear(&new, del);
			return (NULL);
		}
		index = index->next;
		back = back->next;
	}
	return (new);
}
