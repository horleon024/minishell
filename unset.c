/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhorefto <lhorefto@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 16:48:40 by lhorefto          #+#    #+#             */
/*   Updated: 2021/08/05 22:30:58 by lhorefto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_remove_variable(int i)
{
	char	**tmp;
	int		j;
	int		k;

	j = 0;
	k = 0;
	tmp = ft_calloc(sizeof(char *), get_arraylength(g_global.env));
	while (g_global.env[j])
	{
		if (i != j)
		{
			tmp[k] = ft_strdup(g_global.env[j]);
			k++;
		}
		free(g_global.env[j]);
		j++;
	}
	free(g_global.env);
	g_global.env = tmp;
}

static void	ft_check_variable(char *arg)
{
	int		i;
	int		j;
	char	*name;

	i = 0;
	while (g_global.env[i])
	{
		j = 0;
		while (g_global.env[i][j] && g_global.env[i][j] != '=')
			j++;
		name = ft_calloc(1, j + 1);
		ft_strlcpy(name, g_global.env[i], j + 1);
		if (!ft_strcmp(arg, name))
			ft_remove_variable(i);
		i++;
	}
}

int	ft_unset(t_list *input)
{
	input = input->next;
	while (input && !ft_is_delimeter(input->content))
	{
		if (!ft_variable_is_valid(input->content))
			printf("minishell: unset: '%s': not a valid identifier\n",
				input->content);
		else
			ft_check_variable(input->content);
		input = input->next;
	}
	g_global.return_code = 0;
	return (0);
}
