/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sect.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jballang <jballang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 14:24:33 by julien            #+#    #+#             */
/*   Updated: 2018/06/21 11:42:04 by jballang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void	push_sect(t_sect *head, t_sect *sect)
{
	int		i;
	t_sect	*tmp;

	i = 2;
	tmp = head;
	while (tmp->next)
	{
		tmp = tmp->next;
		i += 1;
	}
	sect->n_sect = i;
	tmp->next = sect;
}

void	store_sect(t_file **file, struct segment_command *seg)
{
	uint32_t		i;
	t_file			*f;
	t_sect			*sect;
	struct section	*s;

	i = 0;
	f = *file;
	s = (struct section*)((char*)seg + sizeof(struct segment_command));
	while (i < swap(seg->nsects, f->magic))
	{
		sect = malloc(sizeof(t_sect));
		ft_strcpy(sect->sectname, (s + i)->sectname);
		ft_strcpy(sect->segname, (s + i)->segname);
		sect->n_sect = 1;
		sect->next = NULL;
		if (!f->sect)
			f->sect = sect;
		else
			push_sect(f->sect, sect);
		i += 1;
	}
}

void	store_sect_64(t_file **file, struct segment_command_64 *seg)
{
	uint32_t			i;
	t_file				*f;
	t_sect				*sect;
	struct section_64	*s64;

	i = 0;
	f = *file;
	s64 = (struct section_64*)((char*)seg + sizeof(struct segment_command_64));
	while (i < swap(seg->nsects, f->magic))
	{
		sect = malloc(sizeof(t_sect));
		ft_strcpy(sect->sectname, (s64 + i)->sectname);
		ft_strcpy(sect->segname, (s64 + i)->segname);
		sect->n_sect = 1;
		sect->next = NULL;
		if (!f->sect)
			f->sect = sect;
		else
			push_sect(f->sect, sect);
		i += 1;
	}
}
