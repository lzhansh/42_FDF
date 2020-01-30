/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzhansha <lzhansha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 14:49:54 by lzhansha          #+#    #+#             */
/*   Updated: 2019/07/12 10:39:31 by lzhansha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../libft/libft.h"
# include "mlx.h"
# include "key_def.h"
# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <limits.h>

# define ERR_USAGE	"Usage : ./fdf <filename> [ case_size z_size ]"
# define ERR_NOFILE	"No file found"
# define ERR_NODATA	"No data found"
# define ERR_MAP	"Error in map reading"
# define ERR_INIT	"Error in initialization"
# define ERR_CONV	"Error in conversion"

# define WIN_WID	1400
# define WIN_HEI	1080
# define MENU_WID	250

# define COL_TEXT	0xEAEAEA
# define COL_BGD	0x222222
# define COL_BASE	0xFFFFFF
# define COL_MID1	0xEF8633
# define COL_MID2	0xEC4B27
# define COL_MID3	0xC2294E
# define COL_TOP	0xF70291

typedef enum		e_proj
{
	ISO,
	TOP,
	FRONT,
	SIDE,
}					t_proj;

typedef struct		s_point
{
	int				x;
	int				y;
	int				z;
	int				color;
}					t_point;

typedef struct		s_coord
{
	int				z;
	int				color;
	struct s_coord	*next;
}					t_coord;

typedef struct		s_cam
{
	t_proj			proj;
	int				zoom;
	double			alpha;
	double			beta;
	double			gamma;
	float			z_div;
	int				x_off;
	int				y_off;
}					t_cam;

typedef struct		s_mouse
{
	int				pressed;
	int				x;
	int				y;
	int				prev_x;
	int				prev_y;
}					t_mouse;

typedef	struct		s_map
{
	int				width;
	int				height;
	int				*coor;
	int				*col;
	int				z_min;
	int				z_max;
	int				z_range;
}					t_map;

typedef struct		s_fdf
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*addr;
	int				bpp;
	int				size_line;
	int				endian;
	t_cam			*cam;
	t_map			*map;
	t_mouse			*mouse;
}					t_fdf;

void				fdf_free(char **c);
t_map				*init_map(void);
t_fdf				*init_fdf(t_map *map);
t_cam				*init_cam(t_fdf *fdf);
void				start_fdf(t_coord **c_list, t_map *map);
t_point				proj_fdf(t_point p, t_fdf *fdf);
int					close_win(void	*p);
t_point				new_point(int x, int y, t_map *map);
void				print_menu(t_fdf *fdf);
void				error_msg(char *s);
void				draw_fdf(t_map *map, t_fdf *fdf);
void				control(t_fdf *fdf);
int					control_keyb(int key, void *param);
void				change_proj(int key, t_fdf *fdf);
void				change_flat(int key, t_fdf *fdf);
void				change_rot(int key, t_fdf *fdf);
void				change_move(int key, t_fdf *fdf);
void				change_zoom(int key, t_fdf *fdf);
int					color_default(int z, t_map *map);
int					color_get(t_point c, t_point s, t_point e, t_point d);

#endif
