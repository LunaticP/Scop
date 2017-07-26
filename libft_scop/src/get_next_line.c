/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vthomas <vthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/10 00:43:18 by vthomas           #+#    #+#             */
/*   Updated: 2017/05/16 18:04:57 by vthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include <libft.h>

static void	sf_repos(char **str)
{
	void	*tmp;
	size_t	l;

	tmp = ft_strchr(*str, '\n');
	if (tmp == NULL)
	{
		ft_strclr(*str);
		return ;
	}
	tmp++;
	l = ft_strlen(tmp);
	ft_memcpy((void *)*str, tmp, l + 1);
}

static int	sf_save(char **line, int state)
{
	static char *str_save = NULL;
	char		*tmp;

	if (state)
	{
		if (str_save == NULL)
			return (0);
		if ((tmp = ft_strchr(str_save, '\n')) != NULL)
		{
			*tmp = '\0';
			*line = ft_strdup(str_save);
			*tmp = '\n';
		}
		else
			*line = ft_strdup(str_save);
		sf_repos(&str_save);
		return ((tmp != NULL) ? 1 : 2);
	}
	if (str_save != NULL)
		ft_strclr(str_save);
	tmp = ft_strchr(*line, '\n');
	ft_strdel(&str_save);
	str_save = ft_strdup(tmp + 1);
	*tmp = '\0';
	return (0);
}

static int	sf_finaltest(int ret, char **line, char *tmp)
{
	if (ret == -1)
		return (ret);
	if (ft_strchr(*line, '\n') != NULL)
	{
		sf_save(line, 0);
		ft_strdel(&tmp);
		return (1);
	}
	*line = ft_freejoin(*line, tmp);
	ft_strdel(&tmp);
	if (ft_strchr(*line, '\n') != NULL)
	{
		sf_save(line, 0);
		return (1);
	}
	if (!ft_strlen(*line))
		return (0);
	return (1);
}

int			get_next_line(const int fd, char **line)
{
	int		ret;
	char	*tmp;

	if (fd < 0 || line == NULL)
		return (-1);
	if ((ret = sf_save(line, 1)) == 1)
		return (1);
	else if (ret == 0)
		*line = ft_strnew(0);
	ret = BUFF_SIZE;
	tmp = ft_strnew(BUFF_SIZE);
	while ((ret = read(fd, tmp, BUFF_SIZE)) != 0)
	{
		if (ret == -1)
			return (-1);
		tmp[ret] = '\0';
		*line = ft_freejoin(*line, tmp);
		if (ft_strchr(tmp, '\n'))
			break ;
		ft_strclr(tmp);
	}
	return (sf_finaltest(ret, line, tmp));
}
