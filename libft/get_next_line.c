/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhorefto <lhorefto@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 11:27:58 by lhorefto          #+#    #+#             */
/*   Updated: 2021/08/03 11:27:59 by lhorefto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_free_null(char **ptr)
{
	if (!ptr || !*ptr)
		return ;
	free(*ptr);
	*ptr = NULL;
}

static void	ft_cpy_rest(char **buff, long long j)
{
	long long	i;
	char		tmp[BUFF_MAX];

	i = 0;
	if (buff[0][j] == '\0')
		ft_free_null(&*buff);
	else
	{
		while (buff[0][j] != '\0')
			tmp[i++] = buff[0][j++];
		tmp[i] = '\0';
		ft_free_null(&*buff);
		*buff = ft_strdup(tmp);
	}
}

static int	ft_buffcpy(char **line, char **buff)
{
	long long	i;
	long long	j;
	char		tmp[BUFF_MAX];

	i = 0;
	j = 0;
	while (line[0][i] != '\0')
	{
		tmp[i] = line[0][i];
		i++;
	}
	ft_free_null(&*line);
	while (buff[0][j] != '\0' && buff[0][j] != '\n')
		tmp[i++] = buff[0][j++];
	tmp[i] = '\0';
	*line = ft_strdup(tmp);
	if (buff[0][j] == '\n')
	{
		ft_cpy_rest(&*buff, j + 1);
		return (1);
	}
	ft_free_null(&*buff);
	return (0);
}

static int	ft_free_return(char **ptr, int x, int fd)
{
	if (x == 1 && fd >= 0)
		return (1);
	ft_free_null(&*ptr);
	return (-1);
}

int	get_next_line(int fd, char **line)
{
	static char	*buff[O_MAX];
	char		tmp[BUFF_MAX];
	int			ret[2];

	ret[0] = 0;
	*line = ft_strdup("");
	while (ret[0] == 0 && ret[1] >= 0 && fd >= 0)
	{
		if (buff[fd] == NULL)
		{
			ret[1] = read(fd, tmp, 10);
			if (ret[1] >= 0)
			{
				tmp[ret[1]] = '\0';
				buff[fd] = ft_strdup(tmp);
			}
		}
		if (buff[fd] != NULL)
			ret[1] = ft_strlen(buff[fd]);
		if (ret[1] >= 0)
			ret[0] = ft_buffcpy(&*line, &buff[fd]);
		if (ret[1] == 0)
			return (0);
	}
	return (ft_free_return(&*line, ret[0], fd));
}
