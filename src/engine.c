/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiliaie <mbiliaie@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 01:43:14 by mbiliaie          #+#    #+#             */
/*   Updated: 2018/10/23 01:43:17 by mbiliaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void				*get_frc(char *type)
{
	struct s_args	a;
	void			*f;

	f = NULL;
	a.j = "julia";
	a.m = "mandelbrot";
	a.t = "tricorn";
	if (!ft_strcmp(type, a.t))
	{
		f = tricorn;
		return (f);
	}
	else if (!ft_strcmp(type, a.j))
	{
		f = julia;
		return (f);
	}
	else if (!ft_strcmp(type, a.m))
	{
		f = mandelbrot;
		return (f);
	}
	else
		return (f);
}

void				set_buttons(struct s_keys *b)
{
	b->arr_r = 124;
	b->arr_d = 125;
	b->arr_u = 126;
	b->arr_l = 123;
	b->rpls = 69;
	b->lpls = 24;
	b->lmin = 27;
	b->rmin = 78;
	b->col_k = 40;
	b->col_l = 37;
	b->det_up_z = 6;
	b->det_dn_x = 7;
	b->djf1 = 18;
	b->dmf2 = 19;
	b->dtf3 = 20;
	b->escape = 53;
}

void				set_dimensions(struct s_disp *d)
{
	d->x_tab = 1300;
	d->y_tab = 595;
	d->x_fract = 995;
	d->y_fract = 595;
}

int					get_active(struct s_gen *base)
{
	struct s_disp	d;
	int				out;
	char			*j_case;

	out = 0;
	if (base)
	{
		j_case = "julia";
		set_dimensions(&d);
		set_default_vals(base, j_case);
		out = display(base, &d);
	}
	return (out);
}
