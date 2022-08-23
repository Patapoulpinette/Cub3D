/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouron <dbouron@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 17:29:19 by dbouron           #+#    #+#             */
/*   Updated: 2022/02/08 19:00:16 by dbouron          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*result;

	result = malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!result)
		return (NULL);
	ft_strlcpy(result, s1, sizeof(char) * (ft_strlen(s1) + 1));
	return (result);
}
