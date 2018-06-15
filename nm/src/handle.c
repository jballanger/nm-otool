/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 17:20:29 by julien            #+#    #+#             */
/*   Updated: 2018/06/15 16:14:27 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"
#include <stdio.h>

void	nm_output(t_symbol *symbol)
{
	while (symbol)
	{
		if (symbol->type != '-' && symbol->type != 'N')
		{
			if (symbol->type != 'u' && symbol->type != 'U' &&\
				symbol->type != 'i' && symbol->type != 'I')
				printf("%016llx", symbol->value);
			else
				printf("%s", "                ");
			fflush(stdout);
			ft_putchar(' ');
			ft_putchar(symbol->type);
			ft_putchar(' ');
			ft_putendl(symbol->name);
		}
		symbol = symbol->next;
	}
}

void    handle_64(char *ptr)
{
    uint32_t				i;
    struct  mach_header_64	*header;
    struct  load_command	*lc;
	t_file					*file;

	i = 0;
    header = (struct mach_header_64*)ptr;
    lc = (void*)ptr + sizeof(*header);
	file = malloc(sizeof(t_file));
	file->sect = NULL;
	file->symbol = NULL;
    while (i < header->ncmds)
    {
        if (lc->cmd == LC_SEGMENT_64)
			store_sect(&file, (struct segment_command_64*)lc);
        if (lc->cmd == LC_SYMTAB)
			process_symbol(&file, (struct symtab_command*)lc, ptr);
        lc = (void*)lc + lc->cmdsize;
        i += 1;
    }
	sort_symbol(&file->symbol);
	nm_output(file->symbol);
}
