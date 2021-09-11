/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhorefto <lhorefto@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 16:47:26 by lhorefto          #+#    #+#             */
/*   Updated: 2021/08/04 13:30:34 by lhorefto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Returns path location for ".minishell_history" file */

char	*get_history_file(void)
{
	char	*home;

	home = ft_getenv("HOME");
	ft_joininplace(&home, "/.minishell_history");
	return (home);
}

/* Adds to history the lines from previous instances of ./minishell */

void	ft_load_history(void)
{
	int				fd;
	char			*line;
	char			*history_file;

	history_file = get_history_file();
	fd = open(history_file, O_CREAT | O_RDWR | O_APPEND, 0777);
	while (get_next_line(fd, &line) > 0)
	{
		add_history(line);
		free(line);
	}
	free(line);
	free(history_file);
	close(fd);
}

/* Adds line to history and also to .minishell_history file */

void	ft_add_history(char *line)
{
	int		fd;
	char	*history_file;

	history_file = get_history_file();
	fd = open(history_file, O_CREAT | O_RDWR | O_APPEND, 0777);
	ft_putstr_fd(line, fd);
	ft_putstr_fd("\n", fd);
	add_history(line);
	free(history_file);
	close(fd);
}
