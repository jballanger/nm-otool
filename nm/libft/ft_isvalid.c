/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isvalid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jballang <jballang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 12:12:30 by jballang          #+#    #+#             */
/*   Updated: 2017/06/06 11:57:01 by jballang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_isvalid(char c)
{
	if (ft_isalnum(c) || (c > 32 && c < 59) || (c > 90 && c < 96))
		return (1);
	return (0);
}