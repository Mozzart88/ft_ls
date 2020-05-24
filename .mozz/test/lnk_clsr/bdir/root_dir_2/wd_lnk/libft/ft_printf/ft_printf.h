/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozzart <mozzart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 16:53:10 by tvanessa          #+#    #+#             */
/*   Updated: 2020/05/18 21:29:37 by mozzart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _FT_PRINTF_H
# define _FT_PRINTF_H
# define SIZE 1024
# include <stdarg.h>
# include "libft.h"

typedef unsigned short		t_us;
typedef unsigned int		t_uint;
typedef unsigned long long	t_ull;
typedef	union				u_ldbl_to_ull
{
	long double				ld;
	t_ull					llu[2];
}							t_ldbl_to_ull;
typedef struct				s_vector
{
	t_us					*nbr;
	t_us					*r_val;
	t_us					size;
	t_us					max_size;
	short					point;
	t_us					neg;
	int						(*append)(t_us, struct s_vector*);
	void					(*add_to)(struct s_vector*, t_us, t_us);
	void					(*add_to_r)(struct s_vector*, t_us, t_us);
	void					(*add)(struct s_vector*, struct s_vector*);
	char					*(*to_str)(struct s_vector*, t_us);
	t_us					(*resize)(struct s_vector*, size_t);
	t_us					(*resize_r)(struct s_vector*, size_t);
	void					*(*destroy)(struct s_vector*);
	struct s_vector			*(*nbr_set)(struct s_vector*, t_us *arr, t_us len);
	size_t					(*dcount)(struct s_vector*);
}							t_vector;
typedef	t_vector			t_v;
typedef	union				u_types
{
	unsigned int			val_ui;
	long long int			val;
	signed char				val_c;
	unsigned char			val_uc;
	short					val_h;
	unsigned short			val_uh;
	long int				val_l;
	unsigned long int		val_ul;
	long long int			val_ll;
	unsigned long long int	val_ull;
	float					val_f;
	long double				val_ld;
}							t_types;
typedef struct				s_arg
{
	t_types					u;
	va_list					ap;
	char					*str_result;
	char					*s_str;
	char					*flags;
	int						index_f;
	int						index_buff;
	int						value;
	int						len;
	int						fd;
	char					type;
	int						c_w;
	char					buff[SIZE];
	char					*dup;
}							t_arg;
typedef struct				s_f_arg
{
	char					*width;
	int						i_width;
	char					*length;
	char					*point;
	int						i_point;
	char					*spase;
	char					*zero;
	char					*minus;
	char					*less_zero;
	char					*plus;
	char					*grill;
	char					*fl;
	char					*fll;
	char					*fh;
	char					*fhh;
	char					*temp;
	char					*yes;
	char					*j;
	char					*z;
	char					*t;
	int						exeptions;
}							t_f_arg;

/*
** --------------------------- Main function -----------------------------------
*/
int							ft_printf(const char *restrict format, ...);
int							ft_dprintf(int fd,\
const char *restrict format, ...);

/*
** --------------------------- New struct --------------------------------------
*/
t_arg						*ft_newarg(char type);
t_f_arg						*ft_newarg_flags(void);

/*
** --------------------------- Parsing format ----------------------------------
*/
int							parsing_str_format(t_arg *args, va_list ap,\
const char *format);
int							parsing_str_format_fd(t_arg *args, va_list ap,\
const char *format, int fd);

/*
** --------------------------- Parsing flags -----------------------------------
*/
void						parse_flags_point(t_f_arg *p_fl,\
char *flags, char type, va_list ap);
void						parse_flags_length(t_f_arg *length_flags,\
char *flags);
void						parse_flags_width(t_f_arg *width_flags,\
char *flags, char type, va_list ap);
void						parse_flags_basic(t_f_arg *basic_flags,\
char *flags, int i);

/*
** --------------------------- Check flags -------------------------------------
*/
int							check_flags(t_arg *args);
int							check_flags_mod(char *flags, char type);

/*
** --------------------------- Make struct flags -------------------------------
*/

t_f_arg						*st_flags(t_arg *args,\
t_f_arg *flags_struct, va_list ap);

/*
** --------------------------- Use mod -----------------------------------------
*/
void						use_mod(t_f_arg *struct_flugs, t_arg *args,\
va_list ap);
void						use_mod_point(t_f_arg *struct_flugs, t_arg *args);
t_arg						*use_mod_width(t_f_arg *struct_flugs, t_arg *args,\
int j);

/*
** --------------------------- Use flags ---------------------------------------
*/
void						use_flags_d_i(t_f_arg *struct_flugs, t_arg *args,\
va_list ap);
t_arg						*use_flags_x_x(t_f_arg *struct_flugs, t_arg *args,\
va_list ap);
t_arg						*use_flags_o(t_f_arg *struct_flugs, t_arg *args,\
va_list ap);
t_arg						*use_flags_u(t_f_arg *struct_flugs, t_arg *args,\
va_list ap);
t_arg						*use_flags_c(t_f_arg *struct_flugs, t_arg *args,\
va_list ap);
t_arg						*use_flags_s(t_f_arg *struct_flugs, t_arg *args,\
va_list ap);
t_arg						*use_flags_p(t_f_arg *struct_flugs, t_arg *args,\
va_list ap, int j);
t_arg						*use_flags_f(t_f_arg *s_f, t_arg *args, va_list ap);
t_arg						*use_flags_proc(t_f_arg *struct_flugs, t_arg *args);
void						finish_mod(t_arg *args);
void						finish_mod_fd(t_arg *args);

/*
** --------------------------- Chek_flugs_length -------------------------------
*/
char						*struct_flugs_length_d_i(t_f_arg *struct_flugs,\
t_arg *args, va_list ap);
char						*struct_flugs_length_o(t_f_arg *struct_flugs,
t_arg *args, va_list ap);
char						*struct_flugs_length_u(t_f_arg *struct_flugs,\
t_arg *args, va_list ap);
char						*struct_flugs_length_x_x(t_f_arg *struct_flugs,\
t_arg *args, va_list ap);

/*
** --------------------------- Free --------------------------------------------
*/
char						*ft_fundel(char *app, char *str, int z, int t);
void						free_struct_args(t_arg *args);
void						free_struct_flugs(t_f_arg *struct_flugs);

/*
** --------------------------- Help func ---------------------------------------
*/
char						*revers_str(char *str);
char						*ft_itoa_long(long long n);
char						*ft_itoa_long_un(unsigned long long n);
t_arg						*exeption_null(t_arg *args, t_f_arg *s_f, int i,\
int j);

/*
** --------------------------- float func --------------------------------------
*/
t_v							*ft_pow_vec(t_ull x, int p);
char						*get_float(long double val, t_us p);
char						*ft_exception_handler(t_ull arr[2]);
t_v							*ft_make_long_vector(t_ull int_val);
t_v							*ft_create_vector(size_t len);
void						ft_clear_arr(t_us *arr, size_t len);
void						*ft_vector_destroy(t_v *v);
int							ft_vector_append(t_us d, t_v *v);
void						ft_vector_addition_by_index(t_v *v, t_us n, t_us i);
void						ft_vector_addition_by_index_r(t_v *v, t_us n,\
t_us i);
void						ft_vector_addition(t_v *v, t_v *a);
t_us						ft_vector_resize(t_v *v, size_t len);
char						*ft_vector_to_str(t_v *v, t_us pr);
t_v							*ft_vector_nbr_set(t_v *v, t_us *arr, t_us l);
size_t						ft_vector_count_digits(t_v *v);
t_v							*ft_vector_round(t_v *v, t_us pr);
t_ull						ft_pow(t_ull x, int p);
t_v							*ft_mult_vects(t_v *a, t_v *b, t_us swaped);
t_us						*ft_arrcpy(t_us *dst, t_us *src, t_us len);
t_us						ft_count_digits(t_ull n);
t_us						*ft_arr_add_to(t_us *arr, t_ull v, t_us i);
t_us						ft_vector_resize_r(t_v *v, size_t len);

#endif
