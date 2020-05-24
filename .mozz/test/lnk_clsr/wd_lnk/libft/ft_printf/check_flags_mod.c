/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_flags_mod.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmentat <gmentat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 15:05:20 by gmentat           #+#    #+#             */
/*   Updated: 2019/12/19 19:32:32 by gmentat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		check_flags_mod_s(char *flags, char type)
{
	if (type == 's')
	{
		while (*flags != '\0')
		{
			if (*flags == '0')
				return (-1);
			if (*flags == '+')
				return (-1);
			if (*flags == ' ')
				return (-1);
			if (*flags == '#')
				return (-1);
			flags++;
		}
	}
	return (0);
}

int		check_flags_mod_cp(char *flags, char type)
{
	if (type == 'c' || type == 'p')
	{
		while (*flags != '\0')
		{
			if (*flags == '0')
				return (-1);
			if (*flags == '+')
				return (-1);
			if (*flags == ' ')
				return (-1);
			if (*flags == '#')
				return (-1);
			if (*flags == '.')
				flags++;
			if (ft_isdigit(*flags) != 0)
				return (-1);
			flags++;
		}
	}
	return (0);
}

int		check_flags_mod_u(char *flags, char type)
{
	if (type == 'u')
	{
		while (*flags != '\0')
		{
			if (*flags == '+')
				return (-1);
			if (*flags == ' ')
				return (-1);
			if (*flags == '#')
				return (-1);
			flags++;
		}
	}
	return (0);
}

int		check_flags_mod_dioxx(char *flags, char type)
{
	if (type == 'd' || type == 'i')
	{
		while (*flags != '\0')
		{
			if (*flags == '#')
				return (-1);
			flags++;
		}
	}
	if (type == 'o' || type == 'x' || type == 'X')
	{
		while (*flags != '\0')
		{
			if (*flags == '+')
				return (-1);
			if (*flags == ' ')
				return (-1);
			flags++;
		}
	}
	return (0);
}

int		check_flags_mod(char *flags, char type)
{
	if (type == 'c' || type == 'p' || type == 's')
	{
		if ((check_flags_mod_cp(flags, type)) != 0)
			return (-1);
	}
	if (type == 's')
	{
		if ((check_flags_mod_s(flags, type)) != 0)
			return (-1);
	}
	if (type == 'd' || type == 'i' || type == 'o' ||
		type == 'x' || type == 'X')
	{
		if ((check_flags_mod_dioxx(flags, type)) != 0)
			return (-1);
	}
	if (type == 'u')
	{
		if ((check_flags_mod_u(flags, type)) != 0)
			return (-1);
	}
	return (0);
}
