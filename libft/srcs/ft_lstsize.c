/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantech <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 12:46:05 by gfantech          #+#    #+#             */
/*   Updated: 2022/10/06 12:46:06 by gfantech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_libft.h"

int	ft_lstsize(t_list *lst)
{
	int		i;
	t_list	*index;

	index = lst;
	i = 0;
	while (index != NULL)
	{
		index = index->next;
		i++;
	}
	return (i);
}
