/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzhansha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 17:09:03 by lzhansha          #+#    #+#             */
/*   Updated: 2019/05/02 13:24:16 by lzhansha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *s1, const void *s2, size_t n)
{
	char		*temp1;
	const char	*temp2;

	temp1 = (char *)s1;
	temp2 = (const char *)s2;
	while (n)
	{
		*temp1++ = *temp2++;
		n--;
	}
	return (s1);
}
