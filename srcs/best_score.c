/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviel <cviel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 15:15:43 by cviel             #+#    #+#             */
/*   Updated: 2026/04/26 18:14:22 by cviel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wkw.h"

int	read_score(void)
{
	int		fd = open(SCORE_FILENAME, O_RDONLY);
	int		ret = 1;
	int		score = 0;
	char	buf;

	if (fd <= 2)
		return (0);
	while (ret > 0)
	{
		ret = read(fd, &buf, 1);
		if (buf < '0' || buf > '9')
			return (0);
		if (ret > 0)
			score = score * 10 + (buf - '0');
	}
	close(fd);
	if (ret < 0)
		return (0);
	return (score);
}

void	save_score(int score)
{
	int	len = intlen(score);
	int	digit, power;
	int fd = open(SCORE_FILENAME, O_WRONLY | O_TRUNC | O_CREAT, S_IRWXU);
	char	buf;

	if (fd <= 2 || score == 0)
		return ;
	while (len > 0)
	{
		power = ft_pow(10, len);
		digit = score / power;
		buf = digit + '0';
		write(fd, &buf, 1);
		score = score - (digit * power);
		len--;
	}
	close(fd);
}
