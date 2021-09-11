/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhorefto <lhorefto@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 16:47:51 by lhorefto          #+#    #+#             */
/*   Updated: 2021/08/18 13:45:32 by lhorefto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_get_prompt(void)
{
	char	*prompt;
	char	*end;
	char	*cwd;

	cwd = ft_getcwd();
	end = ft_strjoin(cwd, "$ ");
	prompt = ft_strjoin("MINISHELL:~", end);
	free(cwd);
	free(end);
	return (prompt);
}

void	ft_free_list(t_list *lst)
{
	t_list	*tmp;

	if (!lst)
		return ;
	while (lst)
	{
		if (lst->content)
			free(lst->content);
		tmp = lst->next;
		free(lst);
		lst = tmp;
	}
	lst = NULL;
}

static int	ft_nb_of_envv_outside_quotes(char *line)
{
	int	i;
	int	singleq;
	int	doubleq;
	int	res;

	i = 0;
	singleq = 0;
	doubleq = 0;
	res = 0;
	while (line[i])
	{
		if (line[i] == '"')
			doubleq++;
		else if (line[i] == '\'' && doubleq % 2 == 0)
			singleq++;
		else if (line[i] == '$' && singleq % 2 == 0)
			res++;
		i++;
	}
	return (res);
}

void	minishell(void)
{
	char	*line;
	char	*prompt;

	ft_load_history();
	while (1)
	{
		g_global.pid = 0;
		prompt = ft_get_prompt();
		line = readline(prompt);
		if (!line)
		{
			free(line);
			printf("\n");
			exit(EXIT_SUCCESS);
		}
		if (line[0])
			ft_add_history(line);
		while (ft_nb_of_envv_outside_quotes(line))
			line = ft_replace_envvariable(line);
		ft_update_env("_", ft_get_last_content(line));
		if (line[0])
			split_operator(line);
		free(line);
		free(prompt);
	}
}
