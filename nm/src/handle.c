/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 17:20:29 by julien            #+#    #+#             */
/*   Updated: 2018/06/15 15:16:58 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"
#include <stdio.h>

/*char	ft_print_sect(t_file *file, uint8_t sect)
{
	uint8_t	i;
	uint8_t	j;
	uint8_t	total;
	struct section_64	*s64;

	i = 0;
	total = 0;
	while (file->seg64[i])
	{
		if (sect <= (total + file->seg64[i]->nsects))
		{
			j = 0;
			s64 = (struct section_64*)((char*)file->seg64[i] + sizeof(struct segment_command_64));
			if (ft_strcmp((s64 + (sect - total - 1))->sectname, SECT_TEXT) == 0 &&
				ft_strcmp((s64 + (sect - total - 1))->segname, SEG_TEXT) == 0)
				return ('t');
			if (ft_strcmp((s64 + (sect - total - 1))->sectname, SECT_DATA) == 0 &&
				ft_strcmp((s64 + (sect - total - 1))->segname, SEG_DATA) == 0)
				return ('d');
			if (ft_strcmp((s64 + (sect - total - 1))->sectname, SECT_BSS) == 0 &&
				ft_strcmp((s64 + (sect - total - 1))->segname, SEG_DATA) == 0)
				return ('b');
		}
		total += file->seg64[i]->nsects;
		i += 1;
	}
	return ('s');
}*/

void    ft_print_type(t_file *file, struct nlist_64 symbol)
{
    char    c;

	if (file) {}
    if (symbol.n_type & N_STAB)
        c = '-';
    else
    {
        if ((symbol.n_type & N_TYPE) == N_UNDF)
            c = (symbol.n_value != 0) ? 'c' : 'u';
        else if ((symbol.n_type & N_TYPE) == N_PBUD)
            c = 'u';
        else if ((symbol.n_type & N_TYPE) == N_ABS)
            c = 'a';
        //else if ((symbol.n_type & N_TYPE) == N_SECT)
			//c = ft_print_sect(file, symbol.n_sect);
        else if ((symbol.n_type & N_TYPE) == N_INDR)
            c = 'i';
        else
            c = '?';
    }
    if (symbol.n_type & N_EXT && c != '?')
        c = ft_toupper(c);
    ft_putchar(c);
}

/*void    nm_print(char *ptr, t_file *file)
{
    uint32_t		i;
    struct nlist_64	*symbol_table;
    char			*string_table;

    symbol_table = (void*)ptr + file->symtab->symoff;
    string_table = (void*)ptr + file->symtab->stroff;
    i = 0;
    while (i < file->symtab->nsyms)
    {
		if (symbol_table[i].n_value != 0)
			printf("%016llx", symbol_table[i].n_value);
		else
			printf("%*c", 16, ' ');
		fflush(stdout);
		ft_putchar(' ');
        ft_print_type(file, symbol_table[i]);
        ft_putchar(' ');
    	ft_putendl(string_table + symbol_table[i].n_un.n_strx);
        i += 1;
    }
}*/

void	nm_output(t_symbol *symbol)
{
	while (symbol)
	{
		ft_putnbr(symbol->value);
		ft_putchar(' ');
		ft_putchar(symbol->type);
		ft_putchar(' ');
		ft_putendl(symbol->name);
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
