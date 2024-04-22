/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharpen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 19:49:02 by tcharpen          #+#    #+#             */
/*   Updated: 2022/01/10 19:49:04 by tcharpen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strchr_gnl(const char *s, int c)
{
	int		i;
	char	*str;

	str = (char *) s;
	if (!str)
		return (0);
	i = -1;
	while (str[++i])
	{
		if (str[i] == (char) c)
			return (1);
	}
	if (str[i] == c)
		return (1);
	return (0);
}

char	*ft_strjoin_gnl(char *save, char *buf)
{
	int		i;
	int		j;
	char	*new_save;

	if (!save)
	{
		save = malloc(sizeof(char) * 1);
		if (!save)
			return (ft_free_gnl(buf, NULL));
		save[0] = '\0';
	}
	new_save = malloc(sizeof(char) * ((ft_strlen(save) + ft_strlen(buf)) + 1));
	if (!new_save)
		return (ft_free_gnl(buf, save));
	i = -1;
	j = 0;
	while (save[++i] != '\0')
		new_save[i] = save[i];
	while (buf[j] != '\0')
		new_save[i++] = buf[j++];
	new_save[ft_strlen(save) + ft_strlen(buf)] = '\0';
	free(save);
	return (new_save);
}

char	*ft_free_gnl(char *str, char *str2)
{
	if (str)
		free(str);
	if (str2)
		free(str2);
	return (NULL);
}
