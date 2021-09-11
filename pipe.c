/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhorefto <lhorefto@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 16:48:30 by lhorefto          #+#    #+#             */
/*   Updated: 2021/08/19 17:34:48 by lhorefto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	contains_pipe(char *line)
{
	int	i;
	int	quote;
	int	q;

	i = 0;
	quote = 0;
	while (line[i])
	{
		if (line[i] == '|' && !quote)
			return (1);
		if ((line[i] == '"' || line[i] == '\'') && !quote)
		{
			quote = 1;
			q = line[i];
		}
		else if (line[i] == q)
			quote = 0;
		i++;
	}
	return (0);
}

char	**strpipefeed(char **strs, char *s, int i)
{
	int	j;
	int	len;

	j = 0;
	strs[0] = malloc(sizeof(char) * (i + 1));
	while (j < i)
	{
		strs[0][j] = s[j];
		j++;
	}
	strs[0][j] = '\0';
	j = 0;
	len = ft_strlen(s);
	strs[1] = malloc(sizeof(char) * (len - i));
	while (j < (len - i - 1))
	{
		strs[1][j] = s[i + j + 1];
		j++;
	}
	strs[1][j] = '\0';
	return (strs);
}

char	**split_pipe(char *line, char quote, char q)
{
	char	**strs;
	int		i;

	i = ft_strlen(line) - 1;
	strs = malloc(2 * sizeof(char *));
	while (i >= 0)
	{
		if (line[i] == '|' && !quote)
		{
			if (i == 0 || line[i - 1] == '|')
				return (NULL);
			else
				break ;
		}
		if ((line[i] == '"' || line[i] == '\'') && !quote)
		{
			quote = 1;
			q = line[i];
		}
		else if (line[i] == q)
			quote = 0;
		i--;
	}
	strs = strpipefeed(strs, line, i);
	return (strs);
}

void	pipe_main2(int pid1, int pid2, int *fd, char **strs)
{
	pipe(fd);
	pid1 = fork();
	if (pid1 == 0)
	{
		dup2(fd[1], 1);
		close(fd[0]);
		close(fd[1]);
		ft_exec_command(strs[0]);
		exit(0);
	}
	pid2 = fork();
	if (pid2 == 0)
	{
		dup2(fd[0], 0);
		close(fd[0]);
		close(fd[1]);
		ft_exec_command(strs[1]);
		exit(0);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}

void	pipe_main(char *s)
{
	int		*fd;
	char	**strs;

	strs = split_pipe(s, 0, 0);
	fd = malloc(2 * sizeof(int));
	if (!strs || ft_isspace(strs[0]) || ft_isspace(strs[1]))
	{
		ft_putendl_fd("Incorrect command syntax", 1);
		return ;
	}
	pipe_main2(0, 0, fd, strs);
	free(fd);
	ft_free_2darray(strs);
}
