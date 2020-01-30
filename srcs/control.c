/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzhansha <lzhansha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 01:09:29 by lzhansha          #+#    #+#             */
/*   Updated: 2019/07/12 09:19:28 by lzhansha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		control_keyb(int key, void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	if (key == MAIN_PAD_ESC)
		exit(0);
	if (key == NUM_PAD_PLUS || key == MAIN_PAD_PLUS
		|| key == NUM_PAD_MINUS || key == MAIN_PAD_MINUS)
		change_zoom(key, fdf);
	else if (key == ARROW_LEFT || key == ARROW_RIGHT
		|| key == ARROW_UP || key == ARROW_DOWN)
		change_move(key, fdf);
	else if (key == NUM_PAD_1 || key == MAIN_PAD_1
		|| key == NUM_PAD_2 || key == MAIN_PAD_2
		|| key == NUM_PAD_4 || key == MAIN_PAD_4
		|| key == NUM_PAD_6 || key == MAIN_PAD_6
		|| key == NUM_PAD_7 || key == MAIN_PAD_7
		|| key == NUM_PAD_8 || key == MAIN_PAD_8)
		change_rot(key, fdf);
	else if (key == MAIN_PAD_LESS || key == MAIN_PAD_MORE)
		change_flat(key, fdf);
	else if (key == MAIN_PAD_T || key == MAIN_PAD_I || key == MAIN_PAD_S ||
	key == MAIN_PAD_F)
		change_proj(key, fdf);
	return (0);
}

int		mouse_m(int x, int y, void *param)
{
	t_fdf *fdf;

	fdf = (t_fdf *)param;
	fdf->mouse->prev_x = fdf->mouse->x;
	fdf->mouse->prev_y = fdf->mouse->y;
	fdf->mouse->x = x;
	fdf->mouse->y = y;
	if (fdf->mouse->pressed)
	{
		fdf->cam->beta += (x - fdf->mouse->prev_x) * 0.002;
		fdf->cam->alpha += (y - fdf->mouse->prev_y) * 0.002;
		draw_fdf(fdf->map, fdf);
	}
	return (0);
}

int		mouse_r(int b, int x, int y, void *param)
{
	t_fdf *fdf;

	(void)x;
	(void)y;
	(void)b;
	fdf = (t_fdf *)param;
	fdf->mouse->pressed = 0;
	return (0);
}

int		mouse_p(int b, int x, int y, void *param)
{
	t_fdf *fdf;

	(void)x;
	(void)y;
	fdf = (t_fdf *)param;
	if (b == MOUSE_SCROLL_UP || b == MOUSE_SCROLL_DOWN)
		change_zoom(b, fdf);
	else if (b == MOUSE_LEFT_BUTTON)
		fdf->mouse->pressed = 1;
	return (0);
}

void	control(t_fdf *fdf)
{
	mlx_hook(fdf->win, 2, 0, control_keyb, fdf);
	mlx_hook(fdf->win, 17, 0, close, fdf);
	mlx_hook(fdf->win, 4, 0, mouse_p, fdf);
	mlx_hook(fdf->win, 5, 0, mouse_r, fdf);
	mlx_hook(fdf->win, 6, 0, mouse_m, fdf);
}
