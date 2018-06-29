/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 14:43:24 by julien            #+#    #+#             */
/*   Updated: 2018/06/29 15:05:49 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void	swap_value(t_symbol **s1, t_symbol **s2, char arch)
{
	t_symbol	*tmp1;
	t_symbol	*tmp2;
	uint32_t	value_32;
	uint64_t	value_64;

	tmp1 = *s1;
	tmp2 = *s2;
	if (arch == 32)
	{
		value_32 = tmp1->value_32;
		tmp1->value_32 = tmp2->value_32;
		tmp2->value_32 = value_32;
	}
	else if (arch == 64)
	{
		value_64 = tmp1->value_64;
		tmp1->value_64 = tmp2->value_64;
		tmp2->value_64 = value_64;
	}
}

void	swap_symbol(t_symbol **s1, t_symbol **s2, char arch)
{
	t_symbol	*tmp1;
	t_symbol	*tmp2;
	char		*name;
	char		type;

	tmp1 = *s1;
	tmp2 = *s2;
	name = ft_strdup(tmp1->name);
	type = tmp1->type;
	//value = tmp1->value;
	tmp1->name = tmp2->name;
	tmp1->type = tmp2->type;
	//tmp1->value = tmp2->value;
	tmp2->name = name;
	tmp2->type = type;
	//tmp2->value = value;
	swap_value(s1, s2, arch);
}

void	sort_symbols(t_symbol **symbol, char arch)
{
	int			bubble;
	t_symbol	*tmp;

	bubble = 0;
	while (bubble == 0)
	{
		bubble = 1;
		tmp = *symbol;
		while (tmp && tmp->next)
		{
			if (ft_strcmp(tmp->name, tmp->next->name) > 0)
			{
				bubble = 0;
				swap_symbol(&tmp, &tmp->next, arch);
			}
			tmp = tmp->next;
		}
	}
}
