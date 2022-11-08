/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouron <dbouron@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 15:37:54 by dbouron           #+#    #+#             */
/*   Updated: 2022/11/08 13:46:02 by dbouron          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

size_t	ft_tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

void	ft_error(void)
{
	perror("");
	exit (-1);
}

int	ft_atoi(const char *str)
{
	int			nbr;
	long int	result;

	nbr = 0;
	result = 0;
	while (str[nbr] >= 48 && str[nbr] <= 57)
	{
		result = result * 10 + (str[nbr] - 48);
		nbr++;
	}
	return (result);
}
