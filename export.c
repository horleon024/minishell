/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhorefto <lhorefto@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 16:47:13 by lhorefto          #+#    #+#             */
/*   Updated: 2021/08/05 20:13:25 by lhorefto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_print_variables(void)
{
	int		i;
	int		j;
	char	*name;
	char	*content;

	i = 0;
	while (g_global.env[i])
	{
		j = 0;
		while (g_global.env[i][j] && g_global.env[i][j] != '=')
			j++;
		name = ft_calloc(1, j + 2);
		content = ft_calloc(1, ft_strlen(g_global.env[i]) - j + 1);
		ft_strlcpy(name, g_global.env[i], j + 2);
		ft_strlcpy(content, g_global.env[i] + j + 1,
			ft_strlen(g_global.env[i]) - j);
		if (ft_contains_char(g_global.env[i], '='))
			printf("declare -x %s\"%s\"\n", name, content);
		else
			printf("declare -x %s\n", name);
		free(name);
		free(content);
		i++;
	}
}

static void	ft_add_variable(char *arg)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = ft_calloc(sizeof(char *), get_arraylength(g_global.env) + 2);
	while (g_global.env[i])
	{
		tmp[i] = ft_strdup(g_global.env[i]);
		free(g_global.env[i]);
		i++;
	}
	tmp[i] = ft_strdup(arg);
	free(g_global.env);
	g_global.env = tmp;
}

static void	ft_update_or_add_variable(char *name, char *arg)
{
	int	k;

	k = 0;
	while (g_global.env[k])
	{
		if (!ft_strncmp(name, g_global.env[k], ft_strlen(name)))
		{
			free(g_global.env[k]);
			g_global.env[k] = ft_strdup(arg);
			break ;
		}
		k++;
	}
	if (k == get_arraylength(g_global.env))
		ft_add_variable(arg);
}

static void	ft_get_name(char *arg)
{
	int		i;
	char	*name;

	i = 0;
	while (arg[i] != '=' && arg[i])
		i++;
	name = ft_calloc(1, i + 1);
	ft_strlcpy(name, arg, i + 1);
	ft_update_or_add_variable(name, arg);
	free(name);
}

int	ft_export(t_list *input)
{
	if (ft_lstsize(input) == 1 || ft_is_delimeter(input->next->content))
		ft_print_variables();
	else
	{
		input = input->next;
		while (input && !ft_is_delimeter(input->content))
		{
			if (!ft_variable_is_valid(input->content))
				printf("minishell: export: '%s': not a valid identifier\n",
					input->content);
			else
				ft_get_name(input->content);
			input = input->next;
		}
	}
	if (input)
	{
		g_global.return_code = 1;
		return (1);
	}
	g_global.return_code = 0;
	return (0);
}
