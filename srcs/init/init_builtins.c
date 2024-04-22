/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharpen <tcharpen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 19:27:28 by tcharpen          #+#    #+#             */
/*   Updated: 2022/06/12 19:27:28 by tcharpen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	malloc_builtins(char **builtins)
{
	builtins[0] = malloc(sizeof(char) * (4 + 1));
	if (!builtins[0])
		free_all(1, "malloc");
	builtins[1] = malloc(sizeof(char) * (2 + 1));
	if (!builtins[1])
		free_all(1, "malloc");
	builtins[2] = malloc(sizeof(char) * (3 + 1));
	if (!builtins[2])
		free_all(1, "malloc");
	builtins[3] = malloc(sizeof(char) * (6 + 1));
	if (!builtins[3])
		free_all(1, "malloc");
	builtins[4] = malloc(sizeof(char) * (5 + 1));
	if (!builtins[4])
		free_all(1, "malloc");
	builtins[5] = malloc(sizeof(char) * (3 + 1));
	if (!builtins[5])
		free_all(1, "malloc");
	builtins[6] = malloc(sizeof(char) * (4 + 1));
	if (!builtins[6])
		free_all(1, "malloc");
	builtins[7] = NULL;
}

char	**init_builtins(void)
{
	char	**builtins;

	builtins = malloc(sizeof(char *) * (7 + 1));
	if (!builtins)
		free_all(1, "malloc");
	malloc_builtins(builtins);
	ft_strlcpy(builtins[0], "echo", 5);
	ft_strlcpy(builtins[1], "cd", 3);
	ft_strlcpy(builtins[2], "pwd", 4);
	ft_strlcpy(builtins[3], "export", 7);
	ft_strlcpy(builtins[4], "unset", 6);
	ft_strlcpy(builtins[5], "env", 4);
	ft_strlcpy(builtins[6], "exit", 5);
	return (builtins);
}
