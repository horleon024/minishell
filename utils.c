/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhorefto <lhorefto@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 16:48:44 by lhorefto          #+#    #+#             */
/*   Updated: 2021/08/18 13:45:20 by lhorefto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_arraylength(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return (0);
	while (arr[i])
		i++;
	return (i);
}

/* Appends "/.minishell_history" onto home path (as location
specifier for history file path) */

void	ft_joininplace(char **str, char *str2)
{
	char	*tmp;

	tmp = ft_strjoin(*str, str2);
	free(*str);
	*str = tmp;
}

char	*ft_get_last_content(char *line)
{
	char	*str;
	int		i;

	i = ft_strlen(line);
	while (i > 0 && line[i] != ' ')
		i--;
	str = ft_strdup(line + i);
	return (str);
}

bool	ft_is_delimeter(char *str)
{
	return (!ft_strcmp(str, "|") || !ft_strcmp(str, "<")
		|| !ft_strcmp(str, "<<") || !ft_strcmp(str, ">")
		|| !ft_strcmp(str, ">>") || !ft_strcmp(str, "&&"));
}

bool	ft_variable_is_valid(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '=')
		return (false);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (false);
		i++;
	}
	return (true);
}
