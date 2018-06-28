/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jballang <jballang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 10:22:57 by jballang          #+#    #+#             */
/*   Updated: 2018/06/28 14:52:46 by jballang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

uint32_t	swap_32(uint32_t value, unsigned int m)
{
	uint32_t	result;

	if (m != MH_CIGAM && m != FAT_CIGAM)
		return (value);
	result = 0;
	result |= (value & 0x000000FF) << 24;
    result |= (value & 0x0000FF00) << 8;
    result |= (value & 0x00FF0000) >> 8;
    result |= (value & 0xFF000000) >> 24;
    return (result);
}

uint64_t	swap_64(uint64_t value, unsigned int m)
{
	uint64_t	result;

	if (m != FAT_CIGAM && m != FAT_CIGAM_64)
		return (value);
	result = ((value & 0x00000000000000ff) << 56 |
	(value & 0x000000000000ff00) << 40 |
	(value & 0x0000000000ff0000) << 24 |
	(value & 0x00000000ff000000) << 8 |
	(value & 0x000000ff00000000) >> 8 |
	(value & 0x0000ff0000000000) >> 24 |
	(value & 0x00ff000000000000) >> 40 |
	(value & 0xff00000000000000) >> 56);

	return (result);
}
