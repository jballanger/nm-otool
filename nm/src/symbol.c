/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbol.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 14:25:00 by julien            #+#    #+#             */
/*   Updated: 2018/06/22 10:34:28 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

char	get_symbol_sect(t_sect *sect, uint8_t n_sect)
{
	t_sect	*tmp;
	char	type;

	tmp = sect;
	type = 's';
	while (tmp)
	{
		if (tmp->n_sect == n_sect)
		{
			if (ft_strcmp(tmp->sectname, SECT_TEXT) == 0 &&\
				ft_strcmp(tmp->segname, SEG_TEXT) == 0)
				type = 't';
			else if (ft_strcmp(tmp->sectname, SECT_DATA) == 0 &&\
				ft_strcmp(tmp->segname, SEG_DATA) == 0)
				type = 'd';
			else if (ft_strcmp(tmp->sectname, SECT_BSS) == 0 &&\
				ft_strcmp(tmp->segname, SEG_DATA) == 0)
				type = 'b';
			break ;
		}
		tmp = tmp->next;
	}
	return (type);
}

char	get_symbol_type(struct nlist nlist, t_sect *sect)
{
	t_sect	*s;
	char	type;

	s = sect;
	if (nlist.n_type & N_STAB)
		type = '-';
	else
	{
		type = nlist.n_type & N_TYPE;
		if (type == N_UNDF)
			type = (nlist.n_value != 0) ? 'c' : 'u'; // to swap
		else if (type == N_PBUD)
			type = 'u';
		else if (type == N_ABS)
			type = 'a';
		else if (type == N_SECT)
			type = get_symbol_sect(sect, nlist.n_sect);
		else if (type == N_INDR)
			type = 'i';
		else
			type = '?';
	}
	if (nlist.n_type & N_EXT && type != '?')
		type = ft_toupper(type);
	return (type);
}

void	push_symbol(t_symbol *head, t_symbol *symbol)
{
	t_symbol	*tmp;

	tmp = head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = symbol;
}

void	store_symbol(t_file **file, struct nlist nlist, char *s_table)
{
	t_file		*f;
	t_symbol	*symbol;

	f = *file;
	symbol = malloc(sizeof(t_symbol));
	symbol->name = ft_strdup((s_table + swap(nlist.n_un.n_strx, f->magic)));
	symbol->type = get_symbol_type(nlist, f->sect);
	symbol->value = swap(nlist.n_value, f->magic);
	symbol->next = NULL;
	if (!f->symbol)
		f->symbol = symbol;
	else
		push_symbol(f->symbol, symbol);
}

void	process_symbol(t_file **file, struct symtab_command *symtab, char* ptr)
{
	uint32_t		i;
    struct nlist	*symbol_table;
    char			*string_table;

	i = 0;
    symbol_table = (void*)ptr + swap(symtab->symoff, (*file)->magic);
    string_table = (void*)ptr + swap(symtab->stroff, (*file)->magic);
	while (i < swap(symtab->nsyms, (*file)->magic) && file)
	{
		store_symbol(file, symbol_table[i], string_table);
		i += 1;
	}
}
