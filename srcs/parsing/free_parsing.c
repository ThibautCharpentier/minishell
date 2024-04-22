/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igeorge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 14:36:03 by igeorge           #+#    #+#             */
/*   Updated: 2022/07/10 14:36:03 by igeorge          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_doubletab(char **tabstr)
{
	int	i;

	i = 0;
	while (i < g_var.parsing.nbr_command)
	{
		if (tabstr[i])
			free(tabstr[i]);
		i++;
	}
	free(tabstr);
}

char	*free_under_tab(char	*under_tab)
{
	free(under_tab);
	under_tab = NULL;
	return (under_tab);
}
