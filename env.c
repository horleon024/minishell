/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhorefto <lhorefto@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 16:47:40 by lhorefto          #+#    #+#             */
/*   Updated: 2021/08/04 13:44:07 by lhorefto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Returns the value of the environment variable whose name is
	specified in str */

char	*ft_getenv(char *str)
{
	char	*name;
	char	*content;
	int		i;
	int		j;

	i = -1;
	while (g_global.env[++i])
	{
		j = 0;
		while (g_global.env[i][j] != '=')
			j++;
		name = ft_calloc(sizeof(char), j + 1);
		content = ft_calloc(1, ft_strlen(g_global.env[i]) - j + 1);
		ft_strlcpy(name, g_global.env[i], j + 1);
		ft_strlcpy(content, g_global.env[i] + j + 1,
			ft_strlen(g_global.env[i]) - j);
		if (!ft_strcmp(str, name))
		{
			free(name);
			return (content);
		}
		free(name);
		free(content);
	}
	return (0);
}

static bool	ft_env_isset(char *var)
{
	int	i;

	i = 0;
	while (g_global.env[i])
	{
		if (!ft_strncmp(g_global.env[i], var, ft_strlen(var)))
			return (true);
		i++;
	}
	return (false);
}

void	ft_update_env(char *var, char *new)
{
	int		i;
	char	*tmp;

	i = 0;
	if (ft_env_isset(var))
	{
		tmp = ft_strdup(var);
		ft_joininplace(&tmp, "=");
		ft_joininplace(&tmp, new);
		while (g_global.env[i]
			&& ft_strncmp(g_global.env[i], var, ft_strlen(var)))
			i++;
		free(g_global.env[i]);
		g_global.env[i] = ft_strdup(tmp);
		free(tmp);
	}
	free(new);
}

/* Prints all environment variables */

int	ft_env(void)
{
	int	i;

	i = 0;
	while (g_global.env[i])
	{
		if (ft_contains_char(g_global.env[i], '='))
			printf("%s\n", g_global.env[i]);
		i++;
	}
	g_global.return_code = 0;
	return (0);
}
