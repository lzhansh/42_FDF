/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzhansha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 12:09:19 by lzhansha          #+#    #+#             */
/*   Updated: 2019/05/02 12:30:08 by lzhansha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*copy;
	int		len;

	len = ft_strlen(str) + 1;
	if (!(copy = (char *)malloc(len)))
		return (NULL);
	ft_memcpy(copy, str, len);
	return (copy);
}
