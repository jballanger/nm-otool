/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jballang <jballang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 17:20:29 by julien            #+#    #+#             */
/*   Updated: 2018/06/21 13:58:35 by jballang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"
#include <stdio.h>

void	nm_output(t_symbol *symbol, char arch)
{
	while (symbol)
	{
		if (symbol->type != '-' && symbol->type != 'N')
		{
			if (symbol->type != 'u' && symbol->type != 'U' &&\
				symbol->type != 'i' && symbol->type != 'I')
				(arch == 32) ? printf("%08llx", symbol->value) : printf("%016llx", symbol->value);
			else
				(arch == 32) ? printf("%s", "        ") : printf("%s", "                ");
			fflush(stdout);
			ft_putchar(' ');
			ft_putchar(symbol->type);
			ft_putchar(' ');
			ft_putendl(symbol->name);
		}
		symbol = symbol->next;
	}
}

void    handle(char *ptr)
{
    uint32_t				i;
    struct  mach_header		*header;
    struct  load_command	*lc;
	t_file					*file;

	i = 0;
    header = (struct mach_header*)ptr;
    lc = (void*)ptr + sizeof(*header);
	file = malloc(sizeof(t_file));
	file->sect = NULL;
	file->symbol = NULL;
	file->magic = header->magic;
	ft_putnbr(swap(header->ncmds, file->magic));
	ft_putchar('\n');
    while (i < swap(header->ncmds, file->magic))
    {
		ft_putnbr(swap(lc->cmd, file->magic));
		ft_putchar('\n');
        if (swap(lc->cmd, file->magic) == LC_SEGMENT) {
			ft_putendl("store segment");
			store_sect(&file, (struct segment_command*)lc);
		}
        if (swap(lc->cmd, file->magic) == LC_SYMTAB) {
			ft_putendl("process symbol");
			process_symbol(&file, (struct symtab_command*)lc, ptr);
		}
        if (swap(lc->cmd, file->magic) == LC_UUID) {
			ft_putendl("> LC_UUID");
		}
		if (swap(lc->cmd, file->magic) == LC_DYSYMTAB) {
			ft_putendl("> LC_DYSYMTAB");
		}
		if (swap(lc->cmd, file->magic) == LC_LOAD_DYLIB) {
			ft_putendl("> LC_LOAD_DYLIB");
		}
		if (swap(lc->cmd, file->magic) == LC_ID_DYLIB) {
			ft_putendl("> LC_ID_DYLIB");
		}
		if (swap(lc->cmd, file->magic) == LC_PREBOUND_DYLIB) {
			ft_putendl("> LC_PREBOUND_DYLIB");
		}
		if (swap(lc->cmd, file->magic) == LC_LOAD_DYLINKER) {
			ft_putendl("> LC_LOAD_DYLINKER");
		}
		if (swap(lc->cmd, file->magic) == LC_ID_DYLINKER) {
			ft_putendl("> LC_ID_DYLINKER");
		}
		if (swap(lc->cmd, file->magic) == LC_ROUTINES) {
			ft_putendl("> LC_ROUTINES");
		}
		if (swap(lc->cmd, file->magic) == LC_TWOLEVEL_HINTS) {
			ft_putendl("> LC_TWOLEVEL_HINTS");
		}
		if (swap(lc->cmd, file->magic) == LC_SUB_FRAMEWORK) {
			ft_putendl("> LC_SUB_FRAMEWORK");
		}
		if (swap(lc->cmd, file->magic) == LC_SUB_UMBRELLA) {
			ft_putendl("> LC_SUB_UMBRELLA");
		}
		if (swap(lc->cmd, file->magic) == LC_SUB_LIBRARY) {
			ft_putendl("> LC_SUB_LIBRARY");
		}
		if (swap(lc->cmd, file->magic) == LC_SUB_CLIENT) {
			ft_putendl("> LC_SUB_CLIENT");
		}
        lc = (void*)lc + swap(lc->cmdsize, file->magic);
        i += 1;
    }
	sort_symbol(&file->symbol);
	nm_output(file->symbol, 32);
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
			store_sect_64(&file, (struct segment_command_64*)lc);
        if (lc->cmd == LC_SYMTAB)
			process_symbol_64(&file, (struct symtab_command*)lc, ptr);
        lc = (void*)lc + lc->cmdsize;
        i += 1;
    }
	sort_symbol(&file->symbol);
	nm_output(file->symbol, 64);
}

void	handle_fat(char *ptr, unsigned int magic_number)
{
    uint32_t				i;
    struct  fat_header		*header;
	struct	fat_arch		*arch;
	char					*tmp_ptr;

	i = 0;
    header = (struct fat_header*)ptr;
	arch = (struct fat_arch*)(header + 1);
	while (i < swap(header->nfat_arch, magic_number))
	{
		/*ft_putnbr(swap(arch[i].offset, magic_number));
		ft_putstr(" | ");
		ft_putnbr(swap(arch[i].size, magic_number));
		ft_putchar('\n');*/
		tmp_ptr = (ptr + swap(arch[i].offset, magic_number));
		handle(tmp_ptr);
		i++;
	}
}
