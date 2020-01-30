/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzhansha <lzhansha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 21:59:14 by lzhansha          #+#    #+#             */
/*   Updated: 2019/08/28 16:42:34 by lzhansha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point		new_point(int x, int y, t_map *map)
{
	t_point p;
	int		i;

	i = y * map->width + x;
	p.x = x;
	p.y = y;
	p.z = map->coor[i];
	p.color = (map->col[i] == -1) ? color_default(p.z, map) : map->col[i];
	return (p);
}

static void	draw_pixel(t_fdf *fdf, int x, int y, int color)
{
	int i;

	if (x >= MENU_WID && x < WIN_WID && y >= 0 && y < WIN_HEI)
	{
		i = (x * fdf->bpp / 8) + (y * fdf->size_line);
		fdf->addr[i] = color;
		fdf->addr[++i] = color >> 8;
		fdf->addr[++i] = color >> 16;
	}
}

static void	draw_ln(t_point in, t_point last, t_fdf *fdf)
{
	t_point	delta;
	t_point	sign;
	t_point	curr;
	int		slope_err[2];

	delta.x = FT_ABS(last.x - in.x);
	delta.y = FT_ABS(last.y - in.y);
	sign.x = in.x < last.x ? 1 : -1;
	sign.y = in.y < last.y ? 1 : -1;
	slope_err[0] = delta.x - delta.y;
	curr = in;
	while (curr.x != last.x || curr.y != last.y)
	{
		draw_pixel(fdf, curr.x, curr.y, color_get(curr, in, last, delta));
		if ((slope_err[1] = slope_err[0] * 2) > -delta.y)
		{
			slope_err[0] -= delta.y;
			curr.x += sign.x;
		}
		if (slope_err[1] < delta.x)
		{
			slope_err[0] += delta.x;
			curr.y += sign.y;
		}
	}
}

static void	draw_bgd(t_fdf *fdf)
{
	int *img;
	int i;

	ft_bzero(fdf->addr, WIN_WID * WIN_HEI * (fdf->bpp / 8));
	img = (int *)(fdf->addr);
	i = 0;
	while (i < WIN_WID * WIN_HEI)
		img[i++] = COL_BGD;
}

void		draw_fdf(t_map *map, t_fdf *fdf)
{
	int x;
	int y;

	y = 0;
	draw_bgd(fdf);
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (x != fdf->map->width - 1)
				draw_ln(proj_fdf(new_point(x, y, map), fdf),
				proj_fdf(new_point(x + 1, y, map), fdf), fdf);
			if (y != fdf->map->height - 1)
				draw_ln(proj_fdf(new_point(x, y, map), fdf),
				proj_fdf(new_point(x, y + 1, map), fdf), fdf);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
	print_menu(fdf);
}
