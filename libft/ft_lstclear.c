/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouron <dbouron@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 14:30:03 by dbouron           #+#    #+#             */
/*   Updated: 2022/02/08 16:01:11 by dbouron          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*next_element;

	while (*lst != NULL)
	{
		next_element = (*lst)->next;
		(*del)((*lst)->content);
		free(*lst);
		*lst = next_element;
	}
	return ;
}
