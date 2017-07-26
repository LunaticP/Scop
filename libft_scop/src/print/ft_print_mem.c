/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_mem.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vthomas <vthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 17:51:47 by vthomas           #+#    #+#             */
/*   Updated: 2017/05/16 19:38:50 by vthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static char	sf_partial_hex(unsigned char c, int flag)
{
	char	ret;
	int		tmp;

	tmp = (int)(c & flag);
	if (flag == 0xF0)
		tmp = tmp >> 4;
	if (tmp < 10)
		ret = '0' + tmp;
	else
		ret = 'A' + (tmp - 10);
	return (ret);
}

static char	*sf_get_hex(unsigned char c)
{
	char *str;

	str = ft_strnew(2);
	str[0] = sf_partial_hex(c, 0xF0);
	str[1] = sf_partial_hex(c, 0x0F);
	return (str);
}

static void	sf_print_part(unsigned char *str, int len)
{
	int	i;

	i = 0;
	ft_putstr("\033[90m | \033[34m");
	while (i < len)
	{
		if (ft_isprint(str[i]) == 0)
			ft_putchar('.');
		else
			ft_putchar(str[i]);
		i++;
	}
	if (i < 8)
		ft_putstr("\033[90m");
	while (i++ < 8)
		ft_putchar('.');
	ft_putendl(" \033[90m|\033[0m");
}

static void	sf_respace(int l)
{
	int	i;

	i = 0;
	while (i++ <= l - (l % 2))
		ft_putstr("  ");
}

void		ft_print_mem(unsigned char *mem, size_t len)
{
	size_t	i;
	char	*str;

	i = 0;
	while (i < len)
	{
		str = sf_get_hex(mem[i]);
		ft_putstr(str);
		ft_strdel(&str);
		if (((i + 1) % 2) == 0)
			ft_putchar(' ');
		i++;
		if ((i % 8) == 0 && i != 0)
			sf_print_part(&(mem[i - 8]), 8);
	}
	if (i % 2)
		ft_putstr("00");
	if ((i % 8) != 0 && i != 0)
	{
		sf_respace(8 - (i % 8));
		sf_print_part(&(mem[i - (i % 8)]), (i % 8));
	}
}
