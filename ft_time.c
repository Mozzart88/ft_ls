/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozzart <mozzart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/17 09:58:13 by mozzart           #+#    #+#             */
/*   Updated: 2020/05/19 18:23:47 by mozzart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ft_get_month_str(char *arr[12])
{
	arr[0] = "Jan";
	arr[1] = "Feb";
	arr[2] = "Mar";
	arr[3] = "Apr";
	arr[4] = "May";
	arr[5] = "Jun";
	arr[6] = "Jul";
	arr[7] = "Aug";
	arr[8] = "Sep";
	arr[9] = "Oct";
	arr[10] = "Nov";
	arr[11] = "Des";
}

/* 
** @todo: See ft_localtime todo
*/
void		ft_set_loc(t_datetime *dt)
{
	char	*mon[12];
	int		i;
	char	*m;

	mon[0] = "Jan янв";
	mon[1] = "Feb фев";
	mon[2] = "Mar мар";
	mon[3] = "Apr апр";
	mon[4] = "May май";
	mon[5] = "Jun июн";
	mon[6] = "Jul июл";
	mon[7] = "Aug авг";
	mon[8] = "Sep сен";
	mon[9] = "Oct окт";
	mon[10] = "Nov ноя";
	mon[11] = "Dec дек";
	i = -1;
	m = dt->monstr;
	while (++i < 12)
		if ((ft_strstr(mon[i], dt->monstr)))
			dt->monstr = ft_strsub(mon[i], 4, 6);
	ft_strdel(&m);
}

/* 
** @todo: Check perfomance without strdup and mem allocations
*/
t_datetime	*ft_localtime(t_time *t)
{
	t_datetime	*dt;
	char		*ct;
	char		*s;

	ct = ctime(&t->tv_sec);
	if (!(dt = (t_datetime*)malloc(sizeof(t_datetime))))
		return (NULL);
	// (dt)->daystr = ft_strsub(ct, 0, 3);
	(dt)->monstr = ft_strsub(ct, 4, 3);
	s = ft_strsub(ct, 8, 2);
	(dt)->mday = ft_atoi(s);
	ft_strdel(&s);
	s = ft_strsub(ct, 11, 2);
	(dt)->hour = ft_atoi(s);
	ft_strdel(&s);
	s = ft_strsub(ct, 14, 2);
	(dt)->min = ft_atoi(s);
	ft_strdel(&s);
	s = ft_strsub(ct, 17, 2);
	(dt)->sec = ft_atoi(s);
	ft_strdel(&s);
	s = ft_strsub(ct, 20, 4);
	(dt)->year = ft_atoi(s);
	ft_strdel(&s);
	if (ft_strequ(getenv("LANG"), "ru_RU.UTF-8"))
		ft_set_loc(dt);
	return (dt);
}

time_t		ft_difftime(time_t *t1, time_t *t2)
{
	return (*t1 - *t2);
}

void		ft_print_time(t_time t)
{
	time_t		tl;
	t_datetime	*dt;
	long long	dif_time;
	char		*f;

	tl = time(NULL);
	dt = ft_localtime(&t);
	dif_time = ft_difftime(&tl, &t.tv_sec);
	if (ft_strequ(getenv("LANG"), "ru_RU.UTF-8"))
	{
		f = "%2d %6s %02d:%02d ";
		if (dif_time < (31536000L / 2) && dif_time >= 0)
			ft_printf(f, (dt)->mday, (dt)->monstr, (dt)->hour, (dt)->min);
		else
			ft_printf("%2d %6s %-5 d ", (dt)->mday, (dt)->monstr, (dt)->year);
	}
	else
	{
		f = "%3s %2d %02d:%02d ";
		if (dif_time < (31536000L / 2) && dif_time > (31536000L / 2 * -1))
			ft_printf(f, (dt)->monstr, (dt)->mday, (dt)->hour, (dt)->min);
		else
			ft_printf("%3s %2d %-5 d ", (dt)->monstr, (dt)->mday, (dt)->year);
	}
	ft_strdel(&(dt->monstr));
	free(dt);
	dt = NULL;
}
