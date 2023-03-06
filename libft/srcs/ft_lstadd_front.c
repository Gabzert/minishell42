/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantech <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 11:22:53 by gfantech          #+#    #+#             */
/*   Updated: 2022/10/06 11:22:55 by gfantech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	void	*temp;

	temp = *lst;
	*lst = new;
	new->next = temp;
}
