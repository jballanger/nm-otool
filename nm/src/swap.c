/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jballang <jballang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 10:22:57 by jballang          #+#    #+#             */
/*   Updated: 2018/06/21 11:58:29 by jballang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

uint32_t	swap_32(uint32_t value)
{
	uint32_t	result;

	result = 0;
	result |= (value & 0x000000FF) << 24;
    result |= (value & 0x0000FF00) << 8;
    result |= (value & 0x00FF0000) >> 8;
    result |= (value & 0xFF000000) >> 24;
    return (result);
}

uint32_t	swap_64(uint32_t value)
{
	ft_putendl("swap_64");
	exit(0);
	return value;
}

uint32_t	swap(uint32_t value, unsigned int magic)
{
	if (magic == MH_CIGAM || magic == FAT_CIGAM)
		return (swap_32(value));
	if (magic == MH_CIGAM_64 || magic == FAT_CIGAM_64)
		return (swap_64(value));
	return (value);
}
