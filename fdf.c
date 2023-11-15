/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 11:03:16 by misargsy          #+#    #+#             */
/*   Updated: 2023/10/24 18:27:18 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

bool	fdf_ishotkey(int key)
{
	return ((
			(123 <= key && key <= 126)
			|| (0 <= key && key <= 2)
			|| key == 24 || key == 27
			|| key == 30 || key == 33
			|| key == 13));
}

int	fdf_key(int key, t_data *data)
{
	bool	update;

	if (key == 53)
		fdf_close(data);
	update = fdf_ishotkey(key);
	data -> x_trans += ((key == 125 || key == 1)
			- (key == 126 || key == 13)) * 10;
	data -> y_trans += ((key == 124 || key == 2)
			- (key == 123 || key == 0)) * 10;
	data -> scale += ((key == 24) - (key == 27));
	data -> factor += (key == 30) - (key == 33);
	if (data -> scale < 0)
		data -> scale = 0;
	if (update)
		fdf_render(data);
	return (0);
}

bool	fdf_readfile(t_data *data, char *file)
{
	int	i;

	if (!fdf_get_xy(file, &data -> x_max, &data -> y_max))
		return (false);
	data -> map = (int **)malloc(data -> x_max * sizeof(int *));
	data -> color = (int **)malloc(data -> x_max * sizeof(int *));
	if (data -> x_max <= 0 || data -> y_max <= 0
		|| data -> map == NULL || data -> color == NULL)
		return (free(data -> map), free(data -> color), false);
	i = 0;
	while (i < data -> x_max)
	{
		data -> map[i] = (int *)ft_calloc(data -> y_max, sizeof(int));
		data -> color[i] = (int *)ft_calloc(data -> y_max, sizeof(int));
		if (data -> map[i] == NULL || data -> color[i] == NULL)
			return (fdf_freearr(data), false);
		i++;
	}
	if (!fdf_get_map(data, file))
		return (false);
	return (true);
}

bool	fdf_data_init(t_data *data)
{
	data -> scale = 20;
	data -> factor = 1;
	data -> x_trans = 500;
	data -> y_trans = 500;
	data -> mlx = mlx_init();
	data -> win = mlx_new_window(data -> mlx, 1000, 1000, "fdf");
	return (true);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc != 2 || open(argv[1], O_RDONLY) == -1)
		return (1);
	data = (t_data *)malloc(sizeof(t_data));
	if (!fdf_readfile(data, argv[1]))
		return (1);
	fdf_data_init(data);
	if (data -> mlx == NULL || data -> win == NULL)
	{
		fdf_freearr(data);
		free(data);
		return (1);
	}
	fdf_render(data);
	mlx_key_hook(data -> win, fdf_key, data);
	mlx_hook(data -> win, 17, 0, fdf_close, data);
	mlx_loop(data -> mlx);
	fdf_freearr(data);
	mlx_destroy_image(data -> mlx, data -> img_p);
	mlx_destroy_window(data -> mlx, data -> win);
	free(data);
	exit(0);
}
