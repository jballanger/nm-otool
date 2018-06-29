/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 22:52:46 by julien            #+#    #+#             */
/*   Updated: 2018/06/29 23:30:29 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void	check(t_file **file, void *addr)
{
	if (!addr ||
		addr < (*file)->ptr ||
		addr > ((*file)->ptr + (*file)->size))
	{
		ft_putstr_fd("ft_nm: ", 2);
		ft_putstr_fd((*file)->name, 2);
		ft_putstr_fd(" truncated or malformed object\n", 2);
		exit(EXIT_FAILURE);
	}
}
