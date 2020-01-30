/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proj.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzhansha <lzhansha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 00:01:01 by lzhansha          #+#    #+#             */
/*   Updated: 2019/07/12 09:21:25 by lzhansha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	proj_x(int *y, int *z, double alpha)
{
	int y_p;
	int z_p;

	y_p = *y;
	z_p = *z;
	*y = y_p * cos(alpha) + z_p * sin(alpha);
	*z = -y_p * sin(alpha) + z_p * cos(alpha);
}

static void	proj_y(int *x, int *z, double beta)
{
	int x_p;
	int z_p;

	x_p = *x;
	z_p = *z;
	*x = x_p * cos(beta) - z_p * sin(beta);
	*z = x_p * sin(beta) + z_p * cos(beta);
}

static void	proj_z(int *x, int *y, double gamma)
{
	int x_p;
	int y_p;

	x_p = *x;
	y_p = *y;
	*x = x_p * cos(gamma) - y_p * sin(gamma);
	*y = x_p * sin(gamma) + y_p * cos(gamma);
}

static void	proj_iso(int *x, int *y, int z)
{
	int x_p;
	int y_p;

	x_p = *x;
	y_p = *y;
	*x = (x_p - y_p) * cos(0.523599);
	*y = -z + (x_p + y_p) * sin(0.523599);
}

t_point		proj_fdf(t_point p, t_fdf *fdf)
{
	p.x *= fdf->cam->zoom;
	p.y *= fdf->cam->zoom;
	p.z *= fdf->cam->zoom / fdf->cam->z_div;
	p.x -= (fdf->map->width * fdf->cam->zoom) / 2;
	p.y -= (fdf->map->height * fdf->cam->zoom) / 2;
	proj_x(&p.y, &p.z, fdf->cam->alpha);
	proj_y(&p.x, &p.z, fdf->cam->beta);
	proj_z(&p.x, &p.y, fdf->cam->gamma);
	if (fdf->cam->proj == ISO)
		proj_iso(&p.x, &p.y, p.z);
	else if (fdf->cam->proj == FRONT)
		proj_x(&p.y, &p.z, 4.71239);
	else if (fdf->cam->proj == SIDE)
	{
		proj_x(&p.y, &p.z, 4.71239);
		proj_y(&p.x, &p.z, 1.571);
	}
	p.x += (WIN_WID - MENU_WID) / 2 + fdf->cam->x_off + MENU_WID;
	p.y += (WIN_HEI + fdf->map->height * fdf->cam->zoom) / 2 + fdf->cam->y_off;
	return (p);
}
