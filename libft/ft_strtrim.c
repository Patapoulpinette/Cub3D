/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouron <dbouron@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 16:06:15 by dbouron           #+#    #+#             */
/*   Updated: 2022/02/08 19:58:57 by dbouron          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_char_in_set(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;

	if (!s1)
		return (0);
	i = 0;
	j = ft_strlen(s1) - 1;
	while (ft_char_in_set(s1[i], set) == 1 && i < j)
		i++;
	while (ft_char_in_set(s1[j], set) == 1 && j > 0)
		j--;
	return (ft_substr(s1, i, j - i + 1));
}
