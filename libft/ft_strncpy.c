/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzhansha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 09:25:11 by lzhansha          #+#    #+#             */
/*   Updated: 2019/05/14 09:21:20 by lzhansha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	char *temp;

	temp = dest;
	while (*src && n && n--)
		*temp++ = *src++;
	while (n && n--)
		*temp++ = '\0';
	return (dest);
}
