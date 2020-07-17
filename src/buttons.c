/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiliaie <mbiliaie@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 01:41:30 by mbiliaie          #+#    #+#             */
/*   Updated: 2018/10/23 01:41:33 by mbiliaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

short int			move(int inp, struct s_gen *base, struct s_keys *b)
{
	short int		res;

	res = 0;
	if (inp == b->arr_l)
		base->c.t_x = base->c.t_x + 0.03 / base->c.scale;
	else if (inp == b->arr_u)
		base->c.t_y = base->c.t_y + 0.03 / base->c.scale;
	else if (inp == b->arr_d)
		base->c.t_y = base->c.t_y - 0.03 / base->c.scale;
	else
		base->c.t_x = base->c.t_x - 0.03 / base->c.scale;
	return (res);
}

void				col_schemes(int inp, struct s_gen *base, struct s_keys *b)
{
	int				scheme_first;
	int				scheme_last;
	short int		col_step;

	col_step = 1400;
	scheme_first = 200;
	scheme_last = 22400200;
	if (inp == b->col_l)
	{
		if (base->c.rgb < scheme_last)
			base->c.rgb = base->c.rgb + col_step;
		else
			base->c.rgb = scheme_first;
	}
	else
	{
		if (base->c.rgb > scheme_first)
		{
			base->c.rgb = base->c.rgb - col_step;
		}
		else
			base->c.rgb = scheme_last;
	}
}

static void			scale(struct s_gen *base, int inp, struct s_keys *b)
{
	if (inp == b->rpls || inp == b->rmin)
	{
		if (inp != b->rmin)
			base->c.scale = base->c.scale + 0.095 * base->c.scale;
		else
			base->c.scale = base->c.scale + -0.095 * base->c.scale;
	}
	else
	{
		if (inp != b->lmin)
			base->c.scale = base->c.scale + 0.095 * base->c.scale;
		else
			base->c.scale = base->c.scale + -0.095 * base->c.scale;
	}
}

static short		do_frc_det(int inp, struct s_gen *base, struct s_keys *b)
{
	short int		det_step;
	short int		out;
	int				new_level;

	det_step = 3;
	out = 0;
	if (inp == b->det_dn_x)
	{
		if (base->c.t_i > det_step)
		{
			new_level = base->c.t_i - det_step;
			base->c.t_i = new_level;
		}
	}
	else
	{
		new_level = base->c.t_i + det_step;
		base->c.t_i = new_level;
	}
	return (out);
}

int					catch_btn_push(int inp, struct s_gen *base)
{
	struct s_args	a;
	struct s_keys	b;
	struct s_disp	d;

	a.j = "julia";
	a.m = "mandelbrot";
	a.t = "tricorn";
	set_buttons(&b);
	set_dimensions(&d);
	if (inp == b.rpls || inp == b.lpls || inp == b.lmin || inp == b.rmin)
		scale(base, inp, &b);
	else if (inp == b.col_k || inp == b.col_l)
		col_schemes(inp, base, &b);
	else if (inp == b.det_up_z || inp == b.det_dn_x)
		do_frc_det(inp, base, &b);
	else if (inp == b.djf1 && (base->c.scale = 0.48))
		base->type = a.j;
	else if (inp == b.dmf2 && (base->c.scale = 0.48))
		base->type = a.m;
	else if (inp == b.dtf3 && (base->c.scale = 0.48))
		base->type = a.t;
	if (inp == b.arr_u || inp == b.arr_l || inp == b.arr_r || inp == b.arr_d)
		move(inp, base, &b);
	base->tmp = display(base, &d);
	return (base->tmp);
}
