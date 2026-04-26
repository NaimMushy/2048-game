/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibady <ibady@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 10:17:48 by ibady             #+#    #+#             */
/*   Updated: 2025/11/29 11:12:54 by ibady            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	add_to_line(t_line *line, int bytes_read, int index)
{
	char	*temp;

	if (!line->buf)
	{
		line->len = bytes_read;
		line->buf = malloc(sizeof(char) * line->len);
		return ;
	}
	while (line->len < bytes_read)
		line->len *= 2;
	temp = malloc(sizeof(char) * line->len);
	if (temp)
	{
		while (--index >= 0)
			temp[index] = line->buf[index];
	}
	free(line->buf);
	line->buf = temp;
	return ;
}

static int	get_remaining(t_rest *rest, t_line *line, int bytes_read)
{
	if (!line->buf || line->len < bytes_read)
		add_to_line(line, bytes_read, line->index);
	rest->len = -1;
	while (line->buf && line->index < bytes_read)
	{
		line->buf[line->index] = rest->buf[rest->index++];
		if (line->buf[line->index++] == '\n')
		{
			while (rest->len + line->index < bytes_read)
				rest->len++;
			return (1);
		}
	}
	if (!line->buf)
		return (0);
	rest->index = 0;
	return (1);
}

static char	*ft_return(t_line *line, t_rest *rest)
{
	char	*dup;

	dup = NULL;
	while (line->index >= 0 && line->buf && rest->len != -1)
	{
		if (rest->len == 0)
			rest->index = 0;
		dup = malloc(sizeof(char) * (line->index + 1));
		if (!dup)
			break ;
		dup[line->index] = '\0';
		while (--line->index >= 0)
			dup[line->index] = line->buf[line->index];
	}
	if (line->buf)
		free(line->buf);
	return (dup);
}

char	*get_next_line(int fd)
{
	static t_rest	rest = {0};
	t_line			line;
	int				bytes_read;
	int				error;

	if (BUFFER_SIZE <= 0 || fd < 0 || fd >= FD_MAX)
		return (NULL);
	bytes_read = 0;
	if (rest.len > 0)
		bytes_read = rest.len;
	rest.len = -1;
	line = (t_line){0};
	error = 1;
	while (error)
	{
		if (bytes_read)
			error = get_remaining(&rest, &line, bytes_read);
		if (rest.len >= 0 || !error)
			break ;
		rest.len = read(fd, rest.buf, BUFFER_SIZE);
		if (rest.len < 1)
			break ;
		bytes_read += rest.len;
	}
	return (ft_return(&line, &rest));
}

/*
int	main(int ac, char **av)
{
	char	*testfile;
	int	fd;

	if (ac == 1)
		fd = 0;
	else
		fd = open(av[1], O_RDONLY);
	testfile = calloc(1, 1);
	while (testfile)
	{
		free(testfile);
		testfile = get_next_line(fd);
		__builtin_printf("%s", testfile);
	}
	close(fd);
	return (0);
}
*/
