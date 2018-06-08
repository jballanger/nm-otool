/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 17:20:29 by julien            #+#    #+#             */
/*   Updated: 2018/06/08 18:12:18 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void    nm_print(char *ptr, int nsyms, int symoff, int stroff)
{
    int             i;
    struct nlist_64 *symbol_table;
    char            *string_table;

    symbol_table = (void*)ptr + symoff;
    string_table = (void*)ptr + stroff;
    i = 0;
    while (i < nsyms)
    {
    	ft_putendl(string_table + symbol_table[i].n_un.n_strx);
        i += 1;
    }
}

void    handle_64(char *ptr)
{
    int                     i;
    int                     ncmds;
    struct  mach_header_64  *header;
    struct  load_command    *lc;
    struct  symtab_command  *sym;

    header = (struct mach_header_64*)ptr;
    ncmds = header->ncmds;
    lc = (void*)ptr + sizeof(*header);
    i = 0;
    while (i < ncmds)
    {
        if (lc->cmd == LC_SYMTAB)
        {
            sym = (struct symtab_command*)lc;
            nm_print(ptr, sym->nsyms, sym->symoff, sym->stroff);
            break ;
        }
        lc = (void*)lc + lc->cmdsize;
        i += 1;
    }
}
