/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouron <dbouron@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 17:09:11 by dbouron           #+#    #+#             */
/*   Updated: 2022/02/08 18:58:46 by dbouron          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t type_size)
{
	void	*result;

	result = malloc(count * type_size);
	if (!result)
		return (NULL);
	ft_bzero (result, count * type_size);
	return (result);
}
