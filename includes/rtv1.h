/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercadi <vmercadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 18:44:32 by vmercadi          #+#    #+#             */
/*   Updated: 2018/04/25 14:16:58 by vmercadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __RTV1_H
# define __RTV1_H
# define MARGIN_FLOAT 0.001
# define MAX_DEEP 2
# define DEG2RAD(x) (x * M_PI / 180.0)
# include "libft.h"
# include "color.h"
# include "ui.h"
# include <time.h>
// # include <SDL.h>
# define SDL_MAIN_HANDLED
# include <SDL.h>
# include <SDL_ttf.h>
// # include <sdl2_image.h>
# include <math.h>
# include <limits.h>

/*
** Texture struct
*/

typedef struct				s_tex
{
	double					plasti;
	double					refra;
	double					trans;
	double					reflect;
	double					rug;
	int						hidden;
	t_col					col;
	t_col					ka;
	t_col					kd;
	t_col					ks;
	t_col					col_plasti;
}							t_tex;

/*
** Ray struct
*/

typedef struct				s_ray
{
	double					t;
	t_v						ori;
	t_v						dir;
}							t_ray;

/*
** Struct view plane | width/heigth/distance
*/

typedef	struct				s_vp
{
	double					w;
	double					h;
	double					xi;
	double					yi;
	double					dist;
	t_v						upleft;
}							t_vp;

/*
** Light struct
*/

typedef	struct				s_lux
{
	double					atn;
	double					amp_cst;
	double					amp_lin;
	double					amp_quad;
	t_v						ori;
	t_v						light;
	t_col					dif;
	t_col					spe;
	t_col					lum_amb;
	t_col					lum_dif;
	t_col					lum_spe;
	t_col					col;
	int						id;
	struct s_lux			*next;
}							t_lux;

/*
** Struct for the camera
*/

typedef struct				s_cam
{
	t_v						pos;
	t_v						dir;
	t_v						dirup;
	t_v						dirright;
	int						id;
	struct s_cam			*next;
}							t_cam;

/*
** Struct for triangles
*/

typedef struct				s_tri
{
	t_v						v[3];
	t_v						vt[3];
	t_v						vn[3];
}							t_tri;

/*
** Obj struct containing every kind of object
*/

typedef	struct				s_obj
{
	int						form;
	int						id;
	double					a;
	double					b;
	double					c;
	double					d;
	double					r;
	double					angle;
	t_tri					*tri;
	t_v						h;
	t_v						ori;
	t_tex					tex;
	struct s_obj			*next;
}							t_obj;

/*
** Intersection struct
*/

typedef struct				s_inter
{
	t_ray					to_cam;
	t_ray					to_lux;
	t_tex					tex;
	t_v						n;
	int						id;
	double					min;
}							t_inter;

/*
** Action struct
*/

typedef struct				s_act
{
	int						action;
	int						p;
	double					speed;
	double					dist;
	double					max;
	double					min;
	double					angle;
	double					*axis;
	double					start;
	t_obj					*obj1;
	t_obj					*obj2;
	struct s_act			*next;
}							t_act;

/*
** The base struct, containing all we need to create life
*/

typedef struct				s_b
{
	double					max;
	double					colmax;
	double					gamma;
	double					saturation;
	int						id;
	int						p;
	int						y;
	int						winx;
	int						winy;
	int						maxid;
	int						aliasing;
	int						rec;
	int						time;
	int						draw_lights;
	int						ac;
	char					*av;
	t_act					*act;
	t_px					**tab_px;
	t_vl					*vl;
	t_cam					cam;
	t_vp					vp;
	t_obj					*obj;
	t_lux					*lux;
	t_col					amb;
	t_inter					inter;
	t_ui					ui;
	SDL_Window				*win;
	SDL_Surface				*img;
}							t_b;

/*
** main functions						| maintest2.c
*/

void						render(void *arg);
void						start(t_b *b);
void						render_aliasing(t_b *b, t_px ref);

/*
** Draw fucntions						| draw.c
*/

void						draw(t_b *b);
void						draw_lux(t_b *b);

/*
** Structs inits						| init.c
*/

void						init_b(t_b *b);
void						init_win(t_b *b);
void						init_cam(t_b *b);
t_lux						init_lux(t_v pos, t_col dif, t_col spe);

/*
** Init for the obj structs				| init_obj.c
*/

t_obj						init_plane(t_v n, double d, t_col col);
t_obj						init_plane2(t_v ori, t_v h, t_v w);
t_obj						init_sph(t_v v, t_col color, double r);
t_obj						init_cone(t_v v, t_col col, t_v h, double r);
t_obj						init_cyl(t_v v, t_col col, t_v h, double r);

/*
** Init for vect, col, matrice, etc		| init_data.c
*/

t_col						init_col(double r, double g, double b);
t_ray						init_ray(t_v ori, t_v dir, double t);
t_v							init_vect(double x, double y, double z);
t_vl						init_vl(t_v v, int id);
t_matrice					init_matrice();

/*
** Inits that does not fit in a file with cool name | init_sheit.c
*/

void						init_vp(t_b *b);
t_tex						init_tex();
void						init_inter(t_inter *inter);
t_act						init_act(t_obj *obj1, int action, int axis);
t_b							copy_base(t_b *b, t_b *bl);

/*
**	Main & loop							| main.c
*/

int							main();
void						ray(t_b *b);

/*
**	Utilitaries							| Utils.c
*/

t_v							dir_vp_upleft(t_b *b);
t_v							dir_vp_pixel(t_b *b, t_px px);
t_v							ray2vect(t_ray ray);
double						solve_equation(double min, double a, double b,
																double c);
t_px						pos2px(t_b *b, t_v v);
void						print_obj(t_obj *obj);

/*
** Catch the events						| event.c
*/

int							event(t_b *b);
void						ev_qualitat(t_b *b, int ev);
void						ev_color(t_b *b, int ev);
void						ev_reset(t_b *b);

/*
** Movement events						| event_move.c
*/

int							event_move(t_b *b, int ev);
void						ev_move_cam(t_b *b, int ev);
void						ev_rotate_xy(t_b *b, int ev);

/*
** Event on objects						| event_obj.c
*/

void						event_obj(t_b *b, int ev);
void						ev_move_obj(t_b *b, int ev);
void						ev_move_lum(t_b *b, int ev);
void						ev_mouse(t_b *b);

/*
** Recording, screenshot 				| event_screen.c
*/

void						ev_screen(t_b *b, SDL_Event event);
void						ev_screenshot(t_b *b);

/*
**	Basic math between vectors			| vect_valc1.c
*/

t_v							vect_prod(t_v a, t_v b);
t_v							vect_add(t_v a, t_v b);
t_v							vect_sub(t_v a, t_v b);
double						vect_dot(t_v a, t_v b);

/*
**	Basic math with vector & nb			| vect_calc2.c
*/

t_v							vect_addnb(t_v *v, double nb);
t_v							vect_subnb(t_v *v, double nb);
t_v							vect_multnb(t_v *v, double nb);

/*
** Utilitaries about vectors			| vect_utils.c
*/

double						vect_norme(t_v v);
double						vect_norme2(t_v v);
void						vect_print(t_v v);
void						vect_normalize(t_v *v);
t_v							reflect(t_v v, t_v n);
t_v							vect_rotate(t_v v, double angle, t_v axe);
t_v							vect_init(double x, double y, double z);

/*
** Vector list actions					| vector.c
*/

t_vl						*add_vl(t_b *b, t_vl vl);
t_vl						*search_vl(t_b *b, int id);

/*
** Some color functions					| color.c
*/

unsigned int				spectrum_color(int value, int min, int max);
t_col						cast_ray(t_b *b, t_ray ray);
void						color_sat(t_col *col, double sat);
void						color_max(t_col *col, double *colmax);
t_col						gamma_corr(t_col col, double coeff, double gamma);

/*
** Utilitaries for color				| color_utils.c
*/

unsigned int				col2int(t_col col);
t_col						int2col(unsigned int color);
void						print_col(t_col col);

/*
** Calculation on colors				| color_calc.c
*/

t_col						color_add(t_col col, t_col col2);
t_col						color_mult(t_col col, t_col col2);
t_col						color_multnb(t_col col, double nb);
t_col						color_pow(t_col col, double n);

/*
** Intercept for objs 					| intersection.c
*/

double						inter_obj(t_b *b, t_ray *ray);
int							inter_obj_lux(t_b *b, t_ray *ray);
int							inter_all(t_b *b, t_ray *ray, double min);

/*
** Calculation for the differents obj	| calc_obj.c
*/

double						calc_sphere(t_ray *ray, t_obj sph, double min);
double						calc_plane(t_ray *ray, t_obj plane, double min);
double						calc_cone(t_ray *ray, t_obj cone, double min);
double						calc_cyl(t_ray *ray, t_obj cyl, double min);

/*
** Interact with obj list				| obj.c
*/

t_obj						*add_obj(t_b *b, t_obj obj);
t_obj						*search_obj(t_b *b, int id);
void						delete_obj(t_b *b, int id);

/*
** Lux									| lux.c
*/

t_lux						*add_lux(t_b *b, t_lux lux);
t_lux						*search_lux(t_b *b, int id);

/*
** Calculations for lux					| lux_cal.c
*/

t_col						calc_amb(t_b *b);
t_col						calc_dif(t_lux *lux, t_inter inter);
t_col						calc_spe(t_lux *lux, t_inter inter, t_v to_eye);
void						calc_atn(t_lux *lux, double dist);

/*
** Some scenes							| scene.c
*/

void						scene(t_b *b);

/*
** Matrice calculations functions
*/

t_matrice					matrice_add(t_matrice a, t_matrice b);
t_matrice					matrice_sub(t_matrice a, t_matrice b);
t_matrice					matrice_mult(t_matrice a, t_matrice b);
t_matrice					matrice_multnb(t_matrice a, double nb);
t_v							matrice_multvect(t_matrice m, t_v v);

/*
** Cam refreshing
*/

void						refresh_dir(t_cam *cam, t_v v);
void						refresh_dirup(t_cam *cam, t_v v);
void						refresh_dirright(t_cam *cam, t_v v);

/*
** Actions to animate scene				| action.c
*/

void						action(t_act *act);
t_act						*add_action(t_b *b, t_act act);
void						set_act(t_act *act, double min, double max,
															int axis);
void						act_movaxis(t_act *act);
void						act_ellipse(t_act *act);
void						act_color(t_obj *obj);

/*
** To create a FDF map of the actual scene
*/

void						to_fdf(t_b *b, char *name);

/*
** Parsing							| parsing.c
*/

void						parse_main(t_b *b, char *av);
void						parse_zob(t_b *b, char *av);

/*
** Utils for parsing special format | parsing_utils.c
*/

char						**decoupe(char *s);
t_v							parse_vect(char *s);
t_col						parse_col(char *s);
double						parse_double(char *s);

/*
** Erorrs functions
*/

void						error_quit(int e);
void						parse_err(int e, char *s);

/*
** HELP								| help.c
*/

int							help_parsing(void);
int							man_help(void);

#endif
