/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jballang <jballang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 14:36:30 by jballang          #+#    #+#             */
/*   Updated: 2018/06/28 15:18:17 by jballang         ###   ########.fr       */
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
	lc = (*file)->ptr + sizeof(*header);
	while (i < swap_32(header->ncmds, header->magic))
	{
		if (swap_32(lc->cmd, (*file)->magic) == LC_SEGMENT)
			ft_putendl("segment");
		if (swap_32(lc->cmd, (*file)->magic) == LC_SYMTAB)
			ft_putendl("symtab");
		lc = (void*)lc + swap_32(lc->cmdsize, (*file)->magic);
		i += 1;
	}
}

void	handle_64(t_file **file)
{
	if (file) {}
}
