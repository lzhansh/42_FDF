/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzhansha <lzhansha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 01:13:15 by lzhansha          #+#    #+#             */
/*   Updated: 2019/07/12 09:26:09 by lzhansha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	change_zoom(int key, t_fdf *fdf)
{
	if (key == NUM_PAD_PLUS ||
		key == MAIN_PAD_PLUS ||
		key == MOUSE_SCROLL_UP)
		fdf->cam->zoom++;
	else if (key == NUM_PAD_MINUS ||
		key == MAIN_PAD_MINUS ||
		key == MOUSE_SCROLL_DOWN)
		fdf->cam->zoom--;
	if (fdf->cam->zoom < 1)
		fdf->cam->zoom = 1;
	draw_fdf(fdf->map, fdf);
}

void	change_move(int key, t_fdf *fdf)
{
	if (key == ARROW_LEFT)
		fdf->cam->x_off -= 10;
	else if (key == ARROW_RIGHT)
		fdf->cam->x_off += 10;
	else if (key == ARROW_UP)
		fdf->cam->y_off -= 10;
	else
		fdf->cam->y_off += 10;
	draw_fdf(fdf->map, fdf);
}

void	change_rot(int key, t_fdf *fdf)
{
	if (key == NUM_PAD_2 || key == MAIN_PAD_2)
		fdf->cam->alpha += 0.05;
	else if (key == NUM_PAD_8 || key == MAIN_PAD_8)
		fdf->cam->alpha -= 0.05;
	else if (key == NUM_PAD_4 || key == MAIN_PAD_4)
		fdf->cam->beta -= 0.05;
	else if (key == NUM_PAD_6 || key == MAIN_PAD_6)
		fdf->cam->beta += 0.05;
	else if (key == NUM_PAD_1 || key == MAIN_PAD_1)
		fdf->cam->gamma += 0.05;
	else if (key == NUM_PAD_7 || key == MAIN_PAD_7)
		fdf->cam->gamma -= 0.05;
	draw_fdf(fdf->map, fdf);
}

void	change_flat(int key, t_fdf *fdf)
{
	if (key == MAIN_PAD_LESS)
		fdf->cam->z_div -= 0.1;
	else if (key == MAIN_PAD_MORE)
		fdf->cam->z_div += 0.1;
	if (fdf->cam->z_div < 0.1)
		fdf->cam->z_div = 0.1;
	else if (fdf->cam->z_div > 10)
		fdf->cam->z_div = 10;
	draw_fdf(fdf->map, fdf);
}

void	change_proj(int key, t_fdf *fdf)
{
	fdf->cam->alpha = 0;
	fdf->cam->beta = 0;
	fdf->cam->gamma = 0;
	if (key == MAIN_PAD_I)
		fdf->cam->proj = ISO;
	else if (key == MAIN_PAD_T)
		fdf->cam->proj = TOP;
	else if (key == MAIN_PAD_F)
		fdf->cam->proj = FRONT;
	else if (key == MAIN_PAD_S)
		fdf->cam->proj = SIDE;
	draw_fdf(fdf->map, fdf);
}
