/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_io.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhorefto <lhorefto@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 22:30:30 by lhorefto          #+#    #+#             */
/*   Updated: 2021/08/23 12:08:57 by lhorefto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fredirect_single(char *line, int pid, char **strs)
{
	int	fd[2];

	strs = split_redirect(1, line);
	if (ft_isspace(strs[0]) || ft_isspace(strs[1]))
	{
		ft_putendl_fd("Incorrect command syntax", 1);
		return ;
	}
	join_redirect(strs);
	pid = fork();
	if (pid == 0)
	{
		fd[0] = open(remove_quotes((ft_split_quotes(strs[1]))[0]),
				O_WRONLY | O_CREAT | O_TRUNC, 0777);
		fd[1] = dup2(fd[0], STDOUT_FILENO);
		close(fd[0]);
		ft_exec_command(strs[0]);
		close(fd[1]);
		exit(0);
	}
	wait(NULL);
}

void	fredirect_double(char *line, int pid, char **strs)
{
	int	fd[2];

	strs = split_redirect(2, line);
	if (ft_isspace(strs[0]) || ft_isspace(strs[1]))
	{
		ft_putendl_fd("Incorrect command syntax", 1);
		return ;
	}
	join_redirect(strs);
	pid = fork();
	if (pid == 0)
	{
		fd[0] = open(remove_quotes((ft_split_quotes(strs[1]))[0]),
				O_WRONLY | O_CREAT | O_APPEND, 0777);
		fd[1] = dup2(fd[0], STDOUT_FILENO);
		close(fd[0]);
		ft_exec_command(strs[0]);
		close(fd[1]);
		exit(0);
	}
	wait(NULL);
}

void	bredirect_single(char *line, int pid, char **strs, int *fd)
{
	strs = split_redirect(3, line);
	if (ft_isspace(strs[0]) || ft_isspace(strs[1]))
	{
		ft_putendl_fd("Incorrect command syntax", 1);
		return ;
	}
	join_redirect(strs);
	pid = fork();
	if (pid == 0)
	{
		fd[0] = open(remove_quotes((ft_split_quotes(strs[1]))[0]),
				O_RDWR, 0777);
		if (fd[0] == -1)
		{
			printf("Invalid input location\n");
			exit(0);
		}
		fd[1] = dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		ft_exec_command(strs[0]);
		close(fd[1]);
		exit(0);
	}
	wait(NULL);
}

void	bredir_double_sub(char *line2, char **strs, int fd)
{
	ft_exec_command("cat /dev/null > bredir_double.txt");
	while (1)
	{
		line2 = readline("> ");
		if (!ft_strcmp(line2, remove_quotes((ft_split_quotes(strs[1]))[0])))
		{
			free(line2);
			break ;
		}
		fd = open("bredir_double.txt", O_WRONLY | O_CREAT | O_APPEND, 0777);
		ft_putendl_fd(line2, fd);
		free(line2);
		close(fd);
	}
}

void	bredirect_double(char *line, int pid, char **strs)
{
	int		*fd;

	strs = split_redirect(4, line);
	fd = malloc(2 * sizeof(int));
	if (ft_isspace(strs[0]) || ft_isspace(strs[1]))
	{
		ft_putendl_fd("Incorrect command syntax", 1);
		return ;
	}
	join_redirect(strs);
	pid = fork();
	if (pid == 0)
	{
		bredir_double_sub(NULL, strs, 0);
		exit(0);
	}
	wait(NULL);
	bredirect_single(ft_strjoin(strs[0], " < bredir_double.txt"), 0, NULL, fd);
	remove(ft_split_quotes(strs[1])[0]);
	return ;
}
