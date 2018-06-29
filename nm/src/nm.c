/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 13:40:10 by jballang          #+#    #+#             */
/*   Updated: 2018/06/30 00:18:47 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void	print_value(t_symbol *symbol, char arch)
{
	size_t	size;
	size_t	padding;

	padding = (arch == 32) ? 8 : 16;
	size = ft_intlen_base((arch == 32) ? symbol->value_32 : symbol->value_64, 16);
	while (size < padding)
	{
		ft_putchar('0');
		size += 1;
	}
	ft_print_itoa_base((arch == 32) ? symbol->value_32 : symbol->value_64, 16);
}

void	output_nm(t_file **file)
{
	t_symbol	*symbol;

	symbol = (*file)->symbol;
	while (symbol)
	{
		if (symbol->type != '-' && symbol->type != 'N')
		{
			if (symbol->type != 'i' && symbol->type != 'I' &&
				symbol->type != 'u' && symbol->type != 'U' &&
				(((*file)->arch == 32) ? symbol->value_32 != 0 : symbol->value_64 != 0))
				print_value(symbol, (*file)->arch);
			else
				((*file)->arch == 32) ? ft_putstr("        ") : ft_putstr("                ");
			ft_putchar(' ');
			ft_putchar(symbol->type);
			ft_putchar(' ');
			ft_putendl(symbol->name);
		}
		symbol = symbol->next;
	}
}

void	ft_nm(t_file **file)
{
	if ((*file)->magic == MH_MAGIC || (*file)->magic == MH_CIGAM)
		handle_32(file);
	else if ((*file)->magic == MH_MAGIC_64 || (*file)->magic == MH_CIGAM_64)
		handle_64(file);
	else if ((*file)->magic == FAT_MAGIC || (*file)->magic == FAT_CIGAM)
		ft_putendl("handle fat 32");
	else if ((*file)->magic == FAT_MAGIC_64 || (*file)->magic == FAT_CIGAM_64)
		ft_putendl("handle fat 64");
	else
	{
		ft_putendl("not handled yet");
		return ;
	}
	sort_symbols(&(*file)->symbol, (*file)->arch);
	output_nm(file);
}
