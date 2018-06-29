/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 14:36:30 by jballang          #+#    #+#             */
/*   Updated: 2018/06/29 23:40:24 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void	handle_32(t_file **file)
{
	uint32_t			i;
	struct mach_header	*header;
	struct load_command	*lc;

	i = 0;
	header = (struct mach_header*)(*file)->ptr;
	check(file, header);
	lc = (*file)->ptr + sizeof(*header);
	while (i < swap_32(header->ncmds, header->magic))
	{
		check(file, lc);
		if (swap_32(lc->cmd, (*file)->magic) == LC_SEGMENT)
			get_sections_32(file, (struct segment_command*)lc);
		if (swap_32(lc->cmd, (*file)->magic) == LC_SYMTAB)
			get_symbols_32(file, (struct symtab_command*)lc);
		lc = (void*)lc + swap_32(lc->cmdsize, (*file)->magic);
		i += 1;
	}
	(*file)->arch = 32;
}

void	handle_64(t_file **file)
{
	uint32_t				i;
	struct mach_header_64	*header;
	struct load_command		*lc;

	i = 0;
	header = (struct mach_header_64*)(*file)->ptr;
	check(file, header);
	lc = (*file)->ptr + sizeof(*header);
	while (i < swap_32(header->ncmds, header->magic))
	{
		check(file, lc);
		if (swap_32(lc->cmd, (*file)->magic) == LC_SEGMENT_64)
			get_sections_64(file, (struct segment_command_64*)lc);
		if (swap_32(lc->cmd, (*file)->magic) == LC_SYMTAB)
			get_symbols_64(file, (struct symtab_command*)lc);
		lc = (void*)lc + swap_32(lc->cmdsize, (*file)->magic);
		i += 1;
	}
	(*file)->arch = 64;
}
