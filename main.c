/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhorefto <lhorefto@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 16:47:07 by lhorefto          #+#    #+#             */
/*   Updated: 2021/07/27 16:47:08 by lhorefto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	int		i;

	i = 0;
	if (argc > 1 || !argv[0])
		return (1);
	g_global = (t_global){0};
	g_global.env = ft_calloc(sizeof(char *), get_arraylength(envp) + 1);
	while (envp[i])
	{
		g_global.env[i] = ft_strdup(envp[i]);
		i++;
	}
	signal(SIGINT, handle_sigint);
	minishell();
	return (0);
}
