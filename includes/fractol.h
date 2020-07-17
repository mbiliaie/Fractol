/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiliaie <mbiliaie@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 01:45:27 by mbiliaie          #+#    #+#             */
/*   Updated: 2018/10/23 01:45:31 by mbiliaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "../libft/libft.h"
# include <mlx.h>
# include <pthread.h>

# define STRING mlx_string_put
# define PIXELPUT pxput(a->base, z->x, a->start, z->i * a->rgb);
# define NEWIND mlx_new_window
# define GETADR mlx_get_data_addr

struct				s_disp
{
	short int		x_tab;
	short int		y_tab;
	short int		x_fract;
	short int		y_fract;
};

struct				s_args
{
	char			*j;
	char			*m;
	char			*t;
	char			*u;
	char			*title;
};

struct				s_btns
{
	int short		btn_push;
	int short		btn_letgo;
	int short		mov_warn;
	int short		btn_push_msk;
	int short		btn_letgo_msk;
	int short		arr_mov_msk;
};

struct				s_keys
{
	short int		arr_r;
	short int		arr_d;
	short int		arr_u;
	short int		arr_l;
	short int		rpls;
	short int		lpls;
	short int		lmin;
	short int		rmin;
	short int		col_k;
	short int		col_l;
	short int		det_up_z;
	short int		det_dn_x;
	short int		djf1;
	short int		dmf2;
	short int		dtf3;
	short int		escape;
};

struct				s_frc
{
	double			ntr;
	double			pti;
	double			pto;
	double			nti;
	double			rtp;
	double			i;
};

struct				s_adjust
{
	double			ctr;
	double			cti;
	double			scale;
	double			t_x;
	double			t_y;
	int				rgb;
	int				t_i;
	int				start;
	int				fin;
	struct s_gen	*base;
};

struct				s_add
{
	int				x;
	int				i;
	short int		tmp;
};

struct				s_gen
{
	short int		trd;
	void			*mlx;
	void			*win;
	void			*img;
	char			*str;
	int				smt;
	int				fnsh;
	int				size;
	char			*type;
	int				x;
	int				y;
	struct s_adjust	c;
	int				tmp;
};

void				set_buttons(struct s_keys *b);
int					get_active(struct s_gen *base);
void				*mandelbrot(struct	s_adjust *a);
void				*tricorn(struct	s_adjust *a);
void				handle_exit(int inp, struct s_gen *base);
void				*julia(struct	s_adjust *a);
int					mouse_inp(int m_click, int x, int y, struct s_gen *base);
int					mouse_move(int x, int y, struct s_gen *base);
void				set_dimensions(struct s_disp *d);
int					display(struct s_gen *base, struct s_disp *d);
short				set_default_vals(struct s_gen *base, char *j);
void				*get_frc(char *type);
int					upd_mlx(void *mlx, void *win, void *img);
short int			run_mlx(struct s_gen *base, char *title, struct s_disp *d);
short				pxput(struct s_gen *base, int c_x, int c_y, int rgb);
void				col_schemes(int inp, struct s_gen *base, struct s_keys *b);
int					catch_btn_push(int inp, struct s_gen *base);
short int			move(int inp, struct s_gen *base, struct s_keys *b);

#endif
