/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 13:26:01 by misargsy          #+#    #+#             */
/*   Updated: 2023/10/24 18:25:41 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fdf_isoproj(float *x, float *y, int z, float angle)
{
	float	x_temp;
	float	y_temp;

	x_temp = *x;
	y_temp = *y;
	*x = (x_temp - y_temp) * cos(angle);
	*y = (x_temp + y_temp) * sin(angle) - z;
}

void	fdf_convert(float **line, int *z, float angle, t_data *data)
{
	float	x0;
	float	y0;
	float	x1;
	float	y1;

	x0 = (*line)[0];
	y0 = (*line)[1];
	x1 = (*line)[2];
	y1 = (*line)[3];
	x0 *= data -> scale;
	y0 *= data -> scale;
	x1 *= data -> scale;
	y1 *= data -> scale;
	z[0] *= data -> scale;
	z[1] *= data -> scale;
	fdf_isoproj(&y0, &x0, z[0], angle);
	fdf_isoproj(&y1, &x1, z[1], angle);
	x0 += data -> x_trans;
	y0 += data -> y_trans;
	x1 += data -> x_trans;
	y1 += data -> y_trans;
	(*line)[0] = x0;
	(*line)[1] = y0;
	(*line)[2] = x1;
	(*line)[3] = y1;
}

void	fdf_render_line(float *line, t_data *data)
{
	float	max;
	int		z[2];
	int		color;
	float	dx;
	float	dy;

	z[0] = data -> map[(int)line[0]][(int)line[1]] * data -> factor;
	z[1] = data -> map[(int)line[2]][(int)line[3]] * data -> factor;
	color = data -> color[(int)line[0]][(int)line[1]];
	fdf_convert(&line, z, atan(1 / sqrt(3)), data);
	dx = line[2] - line[0];
	dy = line[3] - line[1];
	max = fmaxf(fabsf(dx), fabsf(dy));
	dx /= max;
	dy /= max;
	while (((int)(line[0] - line[2]) != 0 || (int)(line[1] - line[3]) != 0))
	{
		if (0 <= line[0] && line[0] < 1000 && 0 <= line[1] && line[1] < 1000)
					*(int *)(data -> img_d
					+ (int)line[0] * data -> size_line
					+ (int)line[1] * data -> bpp / 8) = color;
		line[0] += dx;
		line[1] += dy;
	}
}

void	fdf_render(t_data *data)
{
	int		x;
	int		y;
	float	*line;

	data -> img_p = mlx_new_image(data -> mlx, 1000, 1000);
	data -> img_d = mlx_get_data_addr(data -> img_p, &data -> bpp,
			&data -> size_line, &data -> endian);
	y = 0;
	while (y < data -> y_max)
	{
		x = 0;
		while (x < data -> x_max)
		{
			line = (float []){x, y, x + 1, y};
			if (x < data -> x_max - 1)
				fdf_render_line(line, data);
			line = (float []){x, y, x, y + 1};
			if (y < data -> y_max - 1)
				fdf_render_line(line, data);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data -> mlx, data -> win, data -> img_p, 0, 0);
	mlx_destroy_image(data -> mlx, data -> img_p);
}
