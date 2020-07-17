/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_start.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiliaie <mbiliaie@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 01:43:55 by mbiliaie          #+#    #+#             */
/*   Updated: 2018/10/23 01:43:57 by mbiliaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

static short		text_legend(void *mlx, void *win, short x_c, short y_c)
{
	short int		out;

	STRING(mlx, win, x_c, y_c, 0x020B2AA, "1 : FRACTAL JULIA");
	y_c += 27;
	STRING(mlx, win, x_c, y_c, 0x0FFFF00, "2 : FRACTAL MANDELBROT");
	y_c += 27;
	STRING(mlx, win, x_c, y_c, 0x0EBFE9, "3 : FRACTAL TRICORN");
	y_c += 40;
	STRING(mlx, win, x_c, y_c, 0xC0C0C0, "Use - + to scale, push num ");
	y_c += 18;
	STRING(mlx, win, x_c, y_c, 0xC0C0C0, "of fractal to default scale");
	y_c += 41;
	STRING(mlx, win, x_c, y_c, 0x0F8F8FF, "Use arrows to move");
	y_c += 18;
	STRING(mlx, win, x_c, y_c, 0x0F8F8FF, "a scope");
	y_c += 41;
	STRING(mlx, win, x_c, y_c, 0xD3D3D3, "Z : More detailed fractal");
	y_c += 20;
	STRING(mlx, win, x_c, y_c, 0x0A9A9A9, "X : Less detailed fractal");
	y_c += 41;
	STRING(mlx, win, x_c, y_c, 0xFFFAFA, "Push K or L to toggle");
	y_c += 17;
	STRING(mlx, win, x_c, y_c, 0xFFFAFA, "colour schemes");
	out = y_c;
	return (out);
}

static short		name_checker(char *x, struct s_args a, struct s_gen *base)
{
	short int		z;
	int				(*cf)(const char*, const char*);

	base->type = x;
	z = 0;
	cf = ft_strcmp;
	if (cf(x, a.j) != z && cf(x, a.m) != z && cf(x, a.t) != z)
	{
		write(2, a.u, ft_strlen(a.u));
		write(2, "ERROR! Wrong arg name passed!\n", 30);
		return (1);
	}
	return (z);
}

int					upd_mlx(void *mlx, void *win, void *img)
{
	int				out;
	short int		coord_x;
	short int		coord_y;
	int				z;

	z = 0;
	coord_y = 16;
	coord_x = 1008;
	mlx_clear_window(mlx, win);
	text_legend(mlx, win, coord_x, coord_y);
	out = mlx_put_image_to_window(mlx, win, img, z, z);
	return (out);
}

static short int	activate_interaction_mlx(struct s_gen *base)
{
	short int		out;
	struct s_btns	k;
	void			*f;

	out = 0;
	if (base)
	{
		base->trd = 64;
		k.btn_letgo = 3;
		k.btn_letgo_msk = 1L << 1;
		f = handle_exit;
		mlx_hook(base->win, k.btn_letgo, k.btn_letgo_msk, f, base);
		k.btn_push = 2;
		k.btn_push_msk = 1L << 0;
		f = catch_btn_push;
		mlx_hook(base->win, k.btn_push, k.btn_push_msk, f, base);
		k.mov_warn = 6;
		k.arr_mov_msk = 1L << 6;
		f = mouse_move;
		mlx_hook(base->win, k.mov_warn, k.arr_mov_msk, f, base);
		mlx_mouse_hook(base->win, mouse_inp, base);
		mlx_expose_hook(base->win, get_active, base);
		mlx_loop(base->mlx);
	}
	return (out);
}

int					main(int argc, char **argv)
{
	struct s_gen	base;
	struct s_args	a;
	struct s_disp	d;

	a.title = "Awesome Fract'ol";
	a.u = "Usage: ./fractol 'julia' || 'mandelbrot' || 'tricorn'\n";
	if (argc == 2)
	{
		a.j = "julia";
		a.m = "mandelbrot";
		a.t = "tricorn";
		ft_bzero(&base, sizeof(struct s_gen));
		if (name_checker(argv[1], a, &base))
			return (1);
		if (run_mlx(&base, a.title, &d))
			return (1);
		activate_interaction_mlx(&base);
		return (0);
	}
	else
	{
		write(2, a.u, ft_strlen(a.u));
		write(2, "ERROR! Bad quantity of args!\n", 29);
		return (1);
	}
}
