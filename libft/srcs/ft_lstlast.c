/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantech <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 12:52:07 by gfantech          #+#    #+#             */
/*   Updated: 2022/10/06 12:52:12 by gfantech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*index;

	index = lst;
	if (index == NULL)
		return (NULL);
	while (index->next != NULL)
		index = index->next;
	return (index);
}
