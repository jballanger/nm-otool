/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jballang <jballang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 16:36:14 by julien            #+#    #+#             */
/*   Updated: 2018/06/14 11:26:50 by jballang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void	*get_ptr(char *name)
{
	char		*ptr;
	int			fd;
	struct stat	file;

	if ((fd = open(name, O_RDONLY)) < 0)
	{
		ft_putstr("ft_nm: ");
		ft_putstr(name);
		ft_putendl(": Couldn't open.");
		return (NULL);
	}
	if (fstat(fd, &file) < 0)
	{
		ft_putstr("ft_nm: ");
		ft_putstr(name);
		ft_putendl(": Couldn't obtain information.");
		return (NULL);
	}
	if ((ptr = mmap(0, file.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
	{
		ft_putstr("ft_nm: ");
		ft_putstr(name);
		ft_putendl(": Couldn't map.");
		return (NULL);
	}
	return (ptr);
}

void	ft_nm(char *name)
{
	void	*ptr;
	int		magic_number;

	if (!(ptr = get_ptr(name)))
		return ;
	magic_number = *(int*)ptr;
	if (magic_number == (int)MH_MAGIC_64)
		handle_64(ptr);
}

int main(int ac, char **av)
{
	int i;

	i = 1;
	if (ac < 2)
		ft_nm("a.out");
	else
	{
		while (i < ac)
		{
			ft_nm(av[i]);
			i += 1;
		}
	}
	return (0);
}
