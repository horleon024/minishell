/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhorefto <lhorefto@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 22:31:57 by lhorefto          #+#    #+#             */
/*   Updated: 2021/08/23 11:48:30 by lhorefto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	contains_redirect_sub(char *line, int i, int quote)
{
	if (line[i] == '>' && !quote)
	{
		if (i == 0 || line[i - 1] != '>')
			return (1);
		if ((i == 0 || line[i - 1] == '>')
			&& (i == 1 || line[i - 2] != '>'))
			return (2);
		return (-1);
	}
	if (line[i] == '<' && !quote)
	{
		if (i == 0 || line[i - 1] != '<')
			return (3);
		if ((i == 0 || line[i - 1] == '<')
			&& (i == 1 || line[i - 2] != '<'))
			return (4);
		return (-1);
	}
	return (0);
}

int	contains_redirect(char *line)
{
	int		i;
	int		quote;
	char	q;

	i = ft_strlen(line) - 1;
	quote = 0;
	q = 0;
	while (i >= 0)
	{
		if (!contains_redirect_sub(line, i, quote))
		{
			if ((line[i] == '"' || line[i] == 39) && !quote)
			{
				quote = 1;
				q = line[i];
			}
			else if (line[i] == q)
				quote = 0;
			i--;
		}
		else
			return (contains_redirect_sub(line, i, quote));
	}
	return (0);
}

char	**split_redir_forward(char *line, int quote, char q, char **strs)
{
	int	i;

	i = ft_strlen(line) - 1;
	while (i >= 0)
	{
		if (line[i] == '>' && !quote)
			break ;
		if ((line[i] == '"' || line[i] == 39) && !quote)
		{
			quote = 1;
			q = line[i];
		}
		else if (line[i] == q)
			quote = 0;
		i--;
	}
	ft_strlcpy(strs[1], line + i + 1, ft_strlen(line) - i + 1);
	while (line[i] == '>' || line[i] == ' ')
		i--;
	ft_strlcpy(strs[0], line, i + 2);
	return (strs);
}

char	**split_redir_back(char *line, int quote, char q, char **strs)
{
	int	i;

	i = ft_strlen(line) - 1;
	while (i >= 0)
	{
		if (line[i] == '<' && !quote)
			break ;
		if ((line[i] == '"' || line[i] == 39) && !quote)
		{
			quote = 1;
			q = line[i];
		}
		else if (line[i] == q)
			quote = 0;
		i--;
	}
	ft_strlcpy(strs[1], line + i + 1, ft_strlen(line) - i + 1);
	while (line[i] == '<' || line[i] == ' ')
		i--;
	ft_strlcpy(strs[0], line, i + 2);
	return (strs);
}

char	**split_redirect(int n, char *line)
{
	char	**strs;

	strs = malloc(2 * sizeof(char *));
	strs[0] = malloc (sizeof(char) * ft_strlen(line));
	strs[1] = malloc (sizeof(char) * ft_strlen(line));
	if (n == 1 || n == 2)
		strs = split_redir_forward(line, 0, 0, strs);
	if (n == 3 || n == 4)
		strs = split_redir_back(line, 0, 0, strs);
	return (strs);
}
