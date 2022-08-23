/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouron <dbouron@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 15:03:58 by dbouron           #+#    #+#             */
/*   Updated: 2022/06/01 10:03:01 by dbouron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif
# if BUFFER_SIZE <= 0
#  error "NEGATIVE BUFFER SIZE"
# endif

# include <stdlib.h>/* pour malloc */
# include <unistd.h>/* pour read() */

char	*get_next_line(int fd);
int		ft_strchr_gnl(const char *s, char c);
char	*ft_strjoin_gnl(char *s1, char *s2);
char	*ft_substr_gnl(char *s, unsigned int start, size_t len, int mode);
size_t	ft_strlen(const char *s);

#endif