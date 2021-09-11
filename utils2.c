/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhorefto <lhorefto@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 16:47:19 by lhorefto          #+#    #+#             */
/*   Updated: 2021/08/06 11:45:27 by lhorefto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_get_paths(void)
{
	char	*path;
	char	**path_array;

	path = ft_getenv("PATH");
	if (!path)
		return (NULL);
	path_array = ft_split(path, ':');
	free(path);
	return (path_array);
}

char	*ft_getcwd(void)
{
	char	cwd[PATH_MAX];

	if (!getcwd(cwd, PATH_MAX))
		exit(EXIT_FAILURE);
	return (ft_strdup(cwd));
}

void	ft_free_2darray(char **strs)
{
	int	i;

	i = 0;
	if (!strs)
		return ;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

int	ft_args_length(t_list *input)
{
	int	i;

	i = 0;
	while (input && !ft_is_delimeter(input->content))
	{
		i++;
		input = input->next;
	}
	return (i);
}

bool	ft_contains_char(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (true);
		i++;
	}
	return (false);
}
