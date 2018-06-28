/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jballang <jballang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 13:40:10 by jballang          #+#    #+#             */
/*   Updated: 2018/06/28 14:43:58 by jballang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void	ft_nm(t_file **file)
{
	t_file	*f;

	f = *file;
	if ((*file)->magic == MH_MAGIC || f->magic == MH_CIGAM)
		handle_32(file);
	else if (f->magic == MH_MAGIC_64 || f->magic == MH_CIGAM_64)
		handle_64(file);
	else if (f->magic == FAT_MAGIC || f->magic == FAT_CIGAM)
		ft_putendl("handle fat 32");
	else if (f->magic == FAT_MAGIC_64 || f->magic == FAT_CIGAM_64)
		ft_putendl("handle fat 64");
}
