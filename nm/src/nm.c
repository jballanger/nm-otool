/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 16:36:14 by julien            #+#    #+#             */
/*   Updated: 2018/06/15 19:28:48 by julien           ###   ########.fr       */
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
		ft_putstr_fd("ft_nm: ", 2);
		ft_putstr_fd(name, 2);
		ft_putendl_fd(": No such file or directory.", 2);
		return (NULL);
	}
	if (fstat(fd, &file) < 0)
	{
		ft_putstr_fd("ft_nm: ", 2);
		ft_putstr_fd(name, 2);
		ft_putendl_fd(": Couldn't obtain information.", 2);
		return (NULL);
	}
	if ((ptr = mmap(0, file.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
	{
		ft_putstr_fd("ft_nm: ", 2);
		ft_putstr_fd(name, 2);
		ft_putendl_fd(": Couldn't map.", 2);
		return (NULL);
	}
	return (ptr);
}

int		valid_type(unsigned int m, char *name)
{
	if (!IS_32(m) && !IS_64(m) &&\
		!IS_FAT_32(m) && !IS_FAT_64(m))
	{
		ft_putstr_fd("ft_nm: ", 2);
		ft_putstr_fd(name, 2);
		ft_putendl_fd(" The file was not recognized as a valid object file\n", 2);
		return (0);
	}
	return (1);
}

void	ft_nm(char *name, int n)
{
	void			*ptr;
	unsigned int	magic_number;

	if (!(ptr = get_ptr(name)))
		return ;
	magic_number = *(unsigned int*)ptr;
	if (!valid_type(magic_number, name))
		return ;
	if (n > 1)
	{
		ft_putchar('\n');
		ft_putstr(name);
		ft_putendl(":");
	}
	if (IS_32(magic_number))
		handle(ptr);
	else if (IS_64(magic_number))
		handle_64(ptr);
	else if (IS_FAT_32(magic_number))
		ft_putendl("handle fat 32");
	else if (IS_FAT_64(magic_number))
		ft_putendl("handle fat 64");
}

int main(int ac, char **av)
{
	int i;

	i = 1;
	if (ac < 2)
		ft_nm("a.out", 1);
	else
	{
		while (i < ac)
		{
			ft_nm(av[i], (ac - 1));
			i += 1;
		}
	}
	return (0);
}
