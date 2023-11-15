/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 09:27:57 by misargsy          #+#    #+#             */
/*   Updated: 2023/10/24 18:27:12 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft/includes/libft.h"
# include "minilibx/mlx.h"
# include <fcntl.h>
# include <stdbool.h>
# include <math.h>

typedef struct s_data
{
	int		x_max;
	int		y_max;
	int		x_trans;
	int		y_trans;
	int		scale;
	int		factor;
	int		**color;
	int		**map;
	void	*mlx;
	void	*win;
	void	*img_p;
	char	*img_d;
	int		bpp;
	int		size_line;
	int		endian;
}				t_data;

# define BASEU "0123456789ABCDEF"
# define BASEL "0123456789abcdef"

//File Reading: fdf_read.c
bool		fdf_get_xy(char *file, int *x, int *y);
bool		fdf_get_map(t_data *data, char *file);
void		fdf_freearr(t_data *data);

//Util: fdf_util.c
size_t		wordcount(const char *str, const char c);
int			fdf_close(t_data *data);

//Rendering: fdf_render.c
void		fdf_isoproj(float *x, float *y, int z, float angle);
void		fdf_convert(float **line, int *z, float angle, t_data *data);
void		fdf_render_line(float *line, t_data *data);
void		fdf_render(t_data *data);

//Hotkeys: fdf.c
bool		fdf_ishotkey(int key);
int			fdf_key(int key, t_data *data);
bool		fdf_readfile(t_data *data, char *file);
bool		fdf_data_init(t_data *data);

#endif