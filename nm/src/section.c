/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   section.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 12:02:12 by julien            #+#    #+#             */
/*   Updated: 2018/06/29 15:47:19 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void	push_sect(t_sect *head, t_sect *sect)
{
	t_sect		*tmp;
	uint32_t	i;

	tmp = head;
	i = 2;
	while (tmp->next)
	{
		tmp = tmp->next;
		i += 1;
	}
	sect->n_sect = i;
	tmp->next = sect;
}

void	get_sections_32(t_file **file, struct segment_command *segment)
{
	uint32_t		i;
	struct section	*section;
	t_sect			*sect;

	i = 0;
	section = (struct section*)((char*)segment + sizeof(struct segment_command));
	while (i < segment->nsects) // probably have to swap this
	{
		sect = malloc(sizeof(t_sect));
		ft_memcpy(sect->sectname, (section + i)->sectname, 16);
		ft_memcpy(sect->segname, (section + i)->segname, 16);
		sect->n_sect = 1;
		sect->next = NULL;
		if (!(*file)->sect)
			(*file)->sect = sect;
		else
			push_sect((*file)->sect, sect);
		i += 1;
	}
}

void	get_sections_64(t_file **file, struct segment_command_64 *segment)
{
	uint32_t			i;
	struct section_64	*section;
	t_sect				*sect;

	i = 0;
	section = (struct section_64*)((char*)segment + sizeof(struct segment_command_64));
	while (i < segment->nsects) // probably have to swap this
	{
		sect = malloc(sizeof(t_sect));
		ft_memcpy(sect->sectname, (section + i)->sectname, 16);
		ft_memcpy(sect->segname, (section + i)->segname, 16);
		sect->n_sect = 1;
		sect->next = NULL;
		if (!(*file)->sect)
			(*file)->sect = sect;
		else
			push_sect((*file)->sect, sect);
		i += 1;
	}
}
