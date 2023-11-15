/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 10:59:21 by misargsy          #+#    #+#             */
/*   Updated: 2023/10/24 17:39:07 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

bool	fdf_get_xy(char *file, int	*x, int *y)
{
	int		fd;
	int		wc;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (false);
	*x = 0;
	*y = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		wc = wordcount(line, ' ');
		(*x)++;
		if (wc > *y)
			*y = wc;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return (true);
}

void	fdf_freearr(t_data *data)
{
	int	i;

	i = 0;
	while (i < data -> x_max && data -> map[i] != NULL)
		free(data -> map[i++]);
	i = 0;
	while (i < data -> x_max && data -> color[i] != NULL)
		free(data -> color[i++]);
	free(data -> map);
	free(data -> color);
}

static int	fdf_hextoi(char	*point)
{
	int	color;
	int	i;

	while (*point != ',' && *point != '\0')
		point++;
	if (*point == '\0' || (ft_strncmp(point, ",0x", 3) != 0))
		return (0xFFFFFF);
	point += 3;
	color = 0;
	while (*point != '\0')
	{
		i = 0;
		while (BASEU[i] != *point && BASEL[i] != *point && i < 16)
			i++;
		if (i == 16)
			return (color);
		color *= 16;
		color += i;
		point++;
	}
	return (color);
}

static bool	fdf_get_map_helper(int fd, t_data *data, int i)
{
	char	*line;
	char	**split;
	int		j;

	line = get_next_line(fd);
	if (line == NULL)
		return (fdf_freearr(data), false);
	split = ft_split(line, ' ');
	free(line);
	if (split == NULL)
		return (fdf_freearr(data), false);
	j = 0;
	while (j < data -> y_max && split[j] != NULL)
	{
		data -> map[i][j] = ft_atoi(split[j]);
		data -> color[i][j] = fdf_hextoi(split[j]);
		free(split[j]);
		j++;
	}
	free(split[j]);
	free(split);
	return (true);
}

bool	fdf_get_map(t_data *data, char *file)
{
	int		fd;
	int		i;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (false);
	i = 0;
	while (i < data -> x_max)
	{
		if (!fdf_get_map_helper(fd, data, i))
		{
			free(data);
			close(fd);
			return (false);
		}
		i++;
	}
	close(fd);
	return (true);
}
