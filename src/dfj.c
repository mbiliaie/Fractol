/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dfj.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiliaie <mbiliaie@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 01:41:40 by mbiliaie          #+#    #+#             */
/*   Updated: 2018/10/23 01:41:44 by mbiliaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int					mouse_inp(int m_click, int x, int y, struct s_gen *base)
{
	struct s_disp	d;
	int				out;
	short			prime_btn;
	short			sec_btn;

	prime_btn = 1;
	sec_btn = 2;
	set_dimensions(&d);
	while (prime_btn == m_click)
	{
		(void)x;
		base->c.scale = 1.09 * base->c.scale;
		break ;
	}
	while (sec_btn == m_click)
	{
		(void)y;
		base->c.scale = 0.9 * base->c.scale;
		break ;
	}
	out = display(base, &d);
	return (out);
}

int					mouse_move(int x_coord, int y_coord, struct s_gen *base)
{
	struct s_disp	d;
	double			index;
	int				out;

	index = 0.007;
	set_dimensions(&d);
	while (ft_strcmp(base->type, "julia") == 0)
	{
		if (x_coord > base->x)
			base->c.cti = base->c.cti + index / base->c.scale;
		if (x_coord < base->x)
			base->c.cti = base->c.cti - index / base->c.scale;
		if (y_coord > base->y)
			base->c.ctr = base->c.ctr + index / base->c.scale;
		if (y_coord > base->y)
			base->c.ctr = base->c.ctr - index / base->c.scale;
		base->x = x_coord;
		base->y = y_coord;
		break ;
	}
	out = display(base, &d);
	return (out);
}

static short		inner_loop(struct s_frc	*w, struct s_disp *d,
	struct s_add *z, struct s_adjust *a)
{
	short int		k;
	short int		out_j;

	k = 0;
	out_j = k;
	while (++a->start < a->fin && (z->x = z->tmp))
		while (++z->x < d->x_fract)
		{
			w->ntr = a->t_x + 1.499 * (z->x - d->x_fract * 0.5) /
			(a->scale * d->x_fract * 0.48);
			w->nti = a->t_y + (a->start - d->y_fract * 0.5) /
			(a->scale * d->y_fract * 0.48);
			z->i = 0;
			while (z->i < a->t_i && (w->ntr * w->ntr + w->nti * w->nti) <= 4)
			{
				w->pto = w->ntr;
				w->pti = w->nti;
				w->ntr = w->pto * w->pto - w->pti * w->pti + a->ctr;
				w->nti = 2 * w->pto * w->pti + a->cti;
				++z->i;
			}
			PIXELPUT;
		}
	return (out_j);
}

void				*julia(struct s_adjust *a)
{
	struct s_disp	d;
	struct s_add	w;
	struct s_frc	q;

	if (a)
	{
		set_dimensions(&d);
		w.tmp = -1;
		inner_loop(&q, &d, &w, a);
	}
	pthread_exit(NULL);
}

int					display(struct s_gen *base, struct s_disp *d)
{
	struct s_adjust	k[base->trd];
	pthread_t		t[base->trd];
	int				j;

	j = 0;
	ft_bzero(t, sizeof(pthread_t) * base->trd);
	if (d)
	{
		while (base->trd > j)
		{
			k[j] = base->c;
			k[j].start = ((d->y_fract / base->trd) * j) - 1;
			k[j].fin = 1 + (d->y_fract / base->trd) * (j + 1);
			pthread_create(t + j, NULL, get_frc(base->type), k + j);
			j++;
		}
		while (j > 0)
		{
			pthread_join(t[j], NULL);
			j--;
		}
		j = upd_mlx(base->mlx, base->win, base->img);
	}
	return (j);
}
