/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzhansha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 10:19:23 by lzhansha          #+#    #+#             */
/*   Updated: 2019/05/01 10:27:47 by lzhansha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *dest, const char *src)
{
	char *temp;

	temp = dest;
	while (*temp)
		temp++;
	while (*src)
		*temp++ = *src++;
	*temp = '\0';
	return (dest);
}
