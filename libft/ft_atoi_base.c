/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouron <dbouron@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 20:20:43 by dbouron           #+#    #+#             */
/*   Updated: 2022/10/21 11:52:30 by dbouron          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_check_base(char *base)
{
	int		i;
	int		j;

	i = 0;
	if (base[0] == '\0' || base[1] == '\0')
		return (0);
	while (base[i])
	{
		j = 0;
		while (base[j])
		{
			if (base[i] == base[j] && (i != j))
				return (0);
			j++;
		}
		if ((base[i] >= 9 && base[i] <= 13) || base[i] == ' '
			|| base[i] == '+' || base[i] == '-')
			return (0);
		i++;
	}
	return (i);
}

int	ft_convert_base(char c, char *base)
{
	int		i;

	i = 0;
	while (base[i] != c)
		i++;
	return (i);
}

int	ft_char_in_base(char c, char *base)
{
	int		i;

	i = 0;
	while (base[i])
	{
		if (base[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	ft_atoi_base(char *str, char *base)
{
	int		i;
	int		len;
	int		neg;
	int		result;

	i = 0;
	neg = 1;
	result = 0;
	len = ft_check_base(base);
	if (ft_check_base(base) == 0)
		return (0);
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	while (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			neg *= -1;
		i++;
	}
	while (str[i] && ft_char_in_base(str[i], base))
	{
		result = result * len + ft_convert_base(str[i], base);
		i++;
	}
	return (neg * result);
}
