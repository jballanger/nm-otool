/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 14:07:47 by julien            #+#    #+#             */
/*   Updated: 2018/06/22 10:36:37 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void	swap_symbol(t_symbol **s1, t_symbol **s2)
{
	t_symbol	*tmp1;
	t_symbol	*tmp2;
	char		*name;
	char		type;
	uint32_t	value;

	tmp1 = *s1;
	tmp2 = *s2;
	name = ft_strdup(tmp1->name);
	type = tmp1->type;
	value = tmp1->value;
	tmp1->name = tmp2->name;
	tmp1->type = tmp2->type;
	tmp1->value = tmp2->value;
	tmp2->name = name;
	tmp2->type = type;
	tmp2->value = value;
}

void	sort_symbol(t_symbol **symbol)
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
				swap_symbol(&tmp, &tmp->next);
			}
			tmp = tmp->next;
		}
	}
}
