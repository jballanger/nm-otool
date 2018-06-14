/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jballang <jballang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 17:20:29 by julien            #+#    #+#             */
/*   Updated: 2018/06/14 15:20:33 by jballang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

char	ft_print_sect(t_file *file, uint8_t sect)
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
	return ('?');
}

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
        else if ((symbol.n_type & N_TYPE) == N_SECT)
			c = ft_print_sect(file, symbol.n_sect);
        else if ((symbol.n_type & N_TYPE) == N_INDR)
            c = 'i';
        else
            c = '?';
    }
    if (symbol.n_type & N_EXT && c != '?')
        c = ft_toupper(c);
    ft_putchar(c);
}

void	ft_swap(char *a, char *b, size_t size)
{
	char	*_a;
	char	*_b;
	char	_tmp;
	size_t	_s;

	_a = (a);
	_b = (b);
	_s = (size);
	while (_s-- > 0)
	{
		_tmp = *_a;
		//*_a++ = *_b;
		//*_b++ = _tmp;
	}
}

void	ft_sort_symbol(struct nlist_64 *table, char* s, uint32_t n)
{
	uint32_t	i;
	int			bubble;

	bubble = 0;
	while (bubble == 0)
	{
		bubble = 1;
		i = 0;
		while (i < n + 1)
		{
			if (ft_strcmp((s + table[i].n_un.n_strx), (s + table[i + 1].n_un.n_strx)) > 0)
			{
				//bubble = 0;
				ft_putendl((s + table[i].n_un.n_strx));
				ft_putendl((s + table[i + 1].n_un.n_strx));
				ft_swap((char*)&table[i], (char*)&table[i + 1], sizeof(struct nlist_64));
			}
			i += 1;
		}
	}
}

void    nm_print(char *ptr, t_file *file)
{
    uint32_t		i;
    struct nlist_64	*symbol_table;
    char			*string_table;

    symbol_table = (void*)ptr + file->symtab->symoff;
    string_table = (void*)ptr + file->symtab->stroff;
    i = 0;
	ft_sort_symbol(symbol_table, string_table, file->symtab->nsyms);
    while (i < file->symtab->nsyms)
    {
        ft_print_type(file, symbol_table[i]);
        ft_putchar(' ');
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
	t_file					*file;

	file = (t_file*)malloc(sizeof(t_file));
    header = (struct mach_header_64*)ptr;
    ncmds = header->ncmds;
    lc = (void*)ptr + sizeof(*header);
    i = 0;
	file->seg64 = malloc(sizeof(struct segment_command_64) * 10);
	file->sect64 = malloc(sizeof(struct section_64) * 100);
    while (i < ncmds)
    {
        if (lc->cmd == LC_SEGMENT_64)
			file->seg64[i] = (struct segment_command_64*)lc;
        if (lc->cmd == LC_SYMTAB)
        {
			file->symtab = (struct symtab_command*)lc;
            nm_print(ptr, file);
            break ;
        }
        lc = (void*)lc + lc->cmdsize;
        i += 1;
    }
}
