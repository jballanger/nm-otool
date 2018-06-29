/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbol.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 12:24:54 by julien            #+#    #+#             */
/*   Updated: 2018/06/30 00:17:03 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void	push_symbol(t_symbol *head, t_symbol *symbol)
{
	t_symbol	*tmp;

	tmp = head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = symbol;
}

char	get_symbol_sect(t_sect **sect, uint8_t n_sect)
{
	t_sect	*tmp;
	char	symbol_type;

	tmp = *sect;
	symbol_type = 's';
	while (tmp)
	{
		if (tmp->n_sect == n_sect)
		{
			if (ft_strcmp(tmp->sectname, SECT_TEXT) == 0 &&\
				ft_strcmp(tmp->segname, SEG_TEXT) == 0)
				symbol_type = 't';
			else if (ft_strcmp(tmp->sectname, SECT_DATA) == 0 &&\
				ft_strcmp(tmp->segname, SEG_DATA) == 0)
				symbol_type = 'd';
			else if (ft_strcmp(tmp->sectname, SECT_BSS) == 0 &&\
				ft_strcmp(tmp->segname, SEG_DATA) == 0)
				symbol_type = 'b';
			break ;
		}
		tmp = tmp->next;
	}
	return (symbol_type);
}

char	get_symbol_type(t_file **file, uint8_t type, uint8_t sect, uint32_t value)
{
	char	symbol_type;

	if (type & N_STAB)
		symbol_type = '-';
	else
	{
		symbol_type = type & N_TYPE;
		if (symbol_type == N_UNDF)
			symbol_type = (value != 0) ? 'c' : 'u'; // to swap
		else if (symbol_type == N_PBUD)
			symbol_type = 'u';
		else if (symbol_type == N_ABS)
			symbol_type = 'a';
		else if (symbol_type == N_SECT)
			symbol_type = get_symbol_sect(&(*file)->sect, sect);
		else if (symbol_type == N_INDR)
			symbol_type = 'i';
		else
			symbol_type = '?';
	}
	if (type & N_EXT && symbol_type != '?')
		symbol_type = ft_toupper(symbol_type);
	return (symbol_type);
}

void	get_symbols_32(t_file **file, struct symtab_command *symtab)
{
	uint32_t		i;
	struct nlist	*symbol_table;
	char			*string_table;
	t_symbol		*symbol;

	i = 0;
	symbol_table = (struct nlist*)((*file)->ptr + symtab->symoff);
	check(file, symbol_table);
	string_table = (char*)((*file)->ptr + symtab->stroff);
	check(file, string_table);
	while (i < swap_32(symtab->nsyms, (*file)->magic))
	{
		symbol = malloc(sizeof(t_symbol));
		if (swap_32(symbol_table[i].n_un.n_strx, (*file)->magic) == 0)
			symbol->name = "";
		else if ((int)swap_32(symbol_table[i].n_un.n_strx, (*file)->magic) < 0 ||
			swap_32(symbol_table[i].n_un.n_strx, (*file)->magic) > symtab->strsize)
			symbol->name = ft_strdup("bad string index");
		else
			symbol->name = ft_strdup(string_table + swap_32(symbol_table[i].n_un.n_strx, (*file)->magic));
		symbol->type = get_symbol_type(file, symbol_table[i].n_type, symbol_table[i].n_sect, symbol_table[i].n_value);
		symbol->value_32 = symbol_table[i].n_value;
		symbol->next = NULL;
		if (!(*file)->symbol)
			(*file)->symbol = symbol;
		else
			push_symbol((*file)->symbol, symbol);
		i += 1;
	}
}

void	get_symbols_64(t_file **file, struct symtab_command *symtab)
{
	uint32_t		i;
	struct nlist_64	*symbol_table;
	char			*string_table;
	t_symbol		*symbol;

	i = 0;
	symbol_table = (struct nlist_64*)((*file)->ptr + symtab->symoff);
	check(file, symbol_table);
	string_table = (char*)((*file)->ptr + symtab->stroff);
	check(file, string_table);
	while (i < swap_32(symtab->nsyms, (*file)->magic))
	{
		symbol = malloc(sizeof(t_symbol));
		if (swap_32(symbol_table[i].n_un.n_strx, (*file)->magic) == 0)
			symbol->name = "";
		else if ((int)swap_32(symbol_table[i].n_un.n_strx, (*file)->magic) < 0 ||
			swap_32(symbol_table[i].n_un.n_strx, (*file)->magic) > symtab->strsize)
			symbol->name = ft_strdup("bad string index");
		else
			symbol->name = ft_strdup(string_table + swap_32(symbol_table[i].n_un.n_strx, (*file)->magic));
		symbol->type = get_symbol_type(file, symbol_table[i].n_type, symbol_table[i].n_sect, symbol_table[i].n_value);
		symbol->value_64 = symbol_table[i].n_value;
		symbol->next = NULL;
		if (!(*file)->symbol)
			(*file)->symbol = symbol;
		else
			push_symbol((*file)->symbol, symbol);
		i += 1;
	}
}
