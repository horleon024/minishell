/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhorefto <lhorefto@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 16:47:33 by lhorefto          #+#    #+#             */
/*   Updated: 2021/08/18 13:43:30 by lhorefto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_try_exec(char **args)
{
	int	pid;
	int	status;

	pid = fork();
	if (!pid)
	{
		execve(args[0], args, g_global.env);
		exit(100);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		g_global.pid = 2;
		return (WEXITSTATUS(status));
	}
	return (1);
}

static char	**ft_get_exec_paths(char *name)
{
	char	**paths;
	char	**tmp;
	int		i;

	if (!ft_strncmp(name, "./", 2))
	{
		paths = ft_calloc(2, sizeof(char *));
		paths[0] = ft_getcwd();
	}
	else
	{
		tmp = ft_get_paths();
		if (ft_contains_char(name, '/'))
		{
			paths = ft_calloc(sizeof(char *), get_arraylength(tmp) + 2);
			paths[0] = ft_strdup("");
			i = -1;
			while (tmp[++i])
				paths[i + 1] = ft_strdup(tmp[i]);
			ft_free_2darray(tmp);
		}
		else
			paths = tmp;
	}
	return (paths);
}

static void	ft_try_paths(char **paths, char **args)
{
	int		i;
	char	*name;
	char	*tmp;
	int		ret;

	i = 0;
	name = ft_strdup(args[0]);
	while (paths[i])
	{
		tmp = ft_strdup(paths[i]);
		ft_joininplace(&tmp, "/");
		ft_joininplace(&tmp, args[0]);
		free(args[0]);
		args[0] = tmp;
		ret = ft_try_exec(args);
		if (ret != 100)
			break ;
		free(args[0]);
		args[0] = ft_strdup(name);
		i++;
	}
	g_global.return_code = ret;
	if (ret == 100)
		ft_putendl_fd("Unknown command", 2);
	free(name);
}

static void	ft_exec_command2(char *line, t_list *input, int i)
{
	char	**args;
	char	**paths;

	if (!ft_strcmp(input->content, "unset"))
		ft_unset(input);
	else if (!ft_strcmp(input->content, "exit"))
		ft_exit(input, line);
	else
	{
		args = ft_calloc(sizeof(char *), ft_args_length(input) + 1);
		while (input && !ft_is_delimeter(input->content))
		{
			args[i++] = ft_strdup(input->content);
			input = input->next;
		}
		paths = ft_get_exec_paths(args[0]);
		if (!paths)
			ft_free_2darray(args);
		if (!paths)
			return (ft_putendl_fd("Unknown command", 2));
		ft_try_paths(paths, args);
		ft_free_2darray(paths);
		ft_free_2darray(args);
	}
}

void	ft_exec_command(char *line)
{
	t_list	*input;

	input = input_list(line);
	if (!input)
		return ;
	if (contains_pipe(line))
		pipe_main(line);
	else if (contains_redirect(line))
		redirect_main(line);
	else if (!ft_strcmp(input->content, "pwd"))
		ft_pwd();
	else if (!ft_strcmp(input->content, "echo") && input->next
		&& !ft_strcmp(input->next->content, "-n"))
		echo(input->next, 1);
	else if (!ft_strcmp(input->content, "echo"))
		echo(input, 0);
	else if (!ft_strcmp(input->content, "env"))
		ft_env();
	else if (!ft_strcmp(input->content, "export"))
		ft_export(input);
	else if (!ft_strcmp(input->content, "cd"))
		cd(input);
	else
		ft_exec_command2(line, input, 0);
	ft_free_list(input);
}
