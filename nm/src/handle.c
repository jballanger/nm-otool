/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 17:20:29 by julien            #+#    #+#             */
/*   Updated: 2018/06/22 10:58:11 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"
#include <stdio.h>

void	print_value(uint32_t value, size_t padding)
{
	size_t	size;

	size = ft_intlen_base(value, 16);
	ft_putnbr(size);
	ft_putchar('|');
	ft_putnbr(value);
	ft_putchar('|');
	while (size < padding)
	{
		ft_putchar('x');
		size += 1;
	}
	ft_print_itoa_base(value, 16);
}

void	nm_output(t_symbol *symbol, char arch)
{
	while (symbol)
	{
		if (symbol->type != '-' && symbol->type != 'N')
		{
			if (symbol->type != 'u' && symbol->type != 'U' &&\
				symbol->type != 'i' && symbol->type != 'I')
				print_value(symbol->value, (arch == 32) ? 8 : 16);
				//(arch == 32) ? printf("%08llx", symbol->value) : printf("%016llx", symbol->value);
			else
				(arch == 32) ? ft_putstr("        ") : ft_putstr("                ");
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

void	handle_fat_64(char *ptr, unsigned int magic_number)
{
    uint32_t				i;
    struct  fat_header		*header;
	struct	fat_arch_64		*arch;
	char					*tmp_ptr;

	i = 0;
    header = (struct fat_header*)ptr;
	arch = (struct fat_arch_64*)(header + 1);
	while (i < swap(header->nfat_arch, magic_number))
	{
		tmp_ptr = (ptr + swap(arch[i].offset, magic_number));
		handle_64(tmp_ptr);
		i++;
	}
}
