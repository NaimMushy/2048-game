/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibady <ibady@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 10:17:59 by ibady             #+#    #+#             */
/*   Updated: 2025/11/27 17:11:02 by ibady            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

# define FD_MAX 1024

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>

typedef struct s_rest
{
	char	buf[BUFFER_SIZE];
	int		index;
	int		len;
}	t_rest;

typedef struct s_line
{
	char	*buf;
	int		len;
	int		index;
}	t_line;

char	*get_next_line(int fd);

#endif
