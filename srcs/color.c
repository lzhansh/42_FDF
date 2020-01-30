/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzhansha <lzhansha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 14:53:20 by lzhansha          #+#    #+#             */
/*   Updated: 2019/07/12 10:45:13 by lzhansha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int		color_light(int a, int b, double per)
{
	int l;

	l = (int)((1 - per) * a + per * b);
	return (l);
}

static double	color_intensity(int a, int b, int c)
{
	double pos;
	double range;

	pos = c - a;
	range = b - a;
	return ((range == 0) ? 1.0 : (double)(pos / range));
}

int				color_get(t_point current, t_point start,
t_point end, t_point delta)
{
	int		red;
	int		green;
	int		blue;
	double	per;

	if (current.color == end.color)
		return (current.color);
	if (delta.x > delta.y)
		per = color_intensity(start.x, end.x, current.x);
	else
		per = color_intensity(start.y, end.y, current.y);
	red = color_light((start.color >> 16) & 0xFF,
	(end.color >> 16) & 0xFF, per);
	green = color_light((start.color >> 8) & 0xFF,
	(end.color >> 8) & 0xFF, per);
	blue = color_light(start.color & 0xFF, end.color & 0xFF, per);
	return ((red << 16) | (green << 8) | blue);
}

int				color_default(int z, t_map *map)
{
	double per;

	per = color_intensity(map->z_min, map->z_max, z);
	if (per < 0.1)
		return (COL_BASE);
	else if (per < 0.4)
		return (COL_MID1);
	else if (per < 0.6)
		return (COL_MID2);
	else if (per < 0.8)
		return (COL_MID3);
	else
		return (COL_TOP);
}

void			print_menu(t_fdf *fdf)
{
	int		y;
	void	*mlx;
	void	*win;

	y = 0;
	mlx = fdf->mlx;
	win = fdf->win;
	mlx_string_put(mlx, win, 15, y += 20, COL_TEXT, "CONTROL COMMANDS:");
	mlx_string_put(mlx, win, 15, y += 40, COL_TEXT, "- Zoom: +/- or scroll");
	mlx_string_put(mlx, win, 15, y += 30, COL_TEXT, "- Rotate: Press and move");
	mlx_string_put(mlx, win, 15, y += 30, COL_TEXT, "- Move: Arrows");
	mlx_string_put(mlx, win, 15, y += 30, COL_TEXT, "- Flatten: <>");
	mlx_string_put(mlx, win, 15, y += 30, COL_TEXT, "- Rotate:");
	mlx_string_put(mlx, win, 50, y += 30, COL_TEXT, "X: 2/8");
	mlx_string_put(mlx, win, 50, y += 30, COL_TEXT, "Y: 4/6");
	mlx_string_put(mlx, win, 50, y += 30, COL_TEXT, "Z: 1/7");
	mlx_string_put(mlx, win, 15, y += 30, COL_TEXT, "- Projections:");
	mlx_string_put(mlx, win, 50, y += 25, COL_TEXT, "ISO: 'I'");
	mlx_string_put(mlx, win, 50, y += 25, COL_TEXT, "Top view: 'T'");
	mlx_string_put(mlx, win, 50, y += 25, COL_TEXT, "Front view: 'F'");
	mlx_string_put(mlx, win, 50, y += 25, COL_TEXT, "Side view: 'S'");
}
