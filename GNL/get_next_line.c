/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouron <dbouron@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 15:03:23 by dbouron           #+#    #+#             */
/*   Updated: 2022/06/01 10:11:22 by dbouron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	reading(int fd, char **backup)
{
	ssize_t	size;
	char	buffer[BUFFER_SIZE + 1];

	size = read(fd, buffer, BUFFER_SIZE);
	if (size == -1)
		return (-1);
	if (size == 0)
		return (0);
	buffer[size] = '\0';
	*backup = ft_strjoin_gnl(*backup, buffer);
	if (!backup)
		return (-1);
	return (1);
}

char	*get_next_line(int fd)
{
	static char	*backup;
	char		*result;
	char		*tmp;
	int			check_reading;

	while (ft_strchr_gnl(backup, '\n') == -1)
	{
		check_reading = reading(fd, &backup);
		if (check_reading == -1)
			return (NULL);
		if (check_reading == 0)
		{
			result = ft_substr_gnl(backup, 0, ft_strlen(backup), 1);
			backup = NULL;
			return (result);
		}
	}
	result = ft_substr_gnl(backup, 0, ft_strchr_gnl(backup, '\n') + 1, 0);
	if (!result)
		return (NULL);
	tmp = backup;
	backup = ft_substr_gnl(backup, ft_strchr_gnl(backup, '\n') + 1, \
			ft_strlen(backup) - ft_strchr_gnl(backup, '\n') - 1, 0);
	free (tmp);
	return (result);
}
