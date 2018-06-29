/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 13:39:42 by jballang          #+#    #+#             */
/*   Updated: 2018/06/29 14:50:31 by julien           ###   ########.fr       */
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

int		is_valid(t_file *file)
{
	if (!IS_32(file->magic) && !IS_64(file->magic) &&\
		!IS_FAT_32(file->magic) && !IS_FAT_64(file->magic))
	{
		ft_putstr_fd("ft_nm: ", 2);
		ft_putstr_fd(file->name, 2);
		ft_putendl_fd(" The file was not recognized as a valid object file\n", 2);
		return (0);
	}
	return (1);
}

void	print_filename(t_file *file, int ac, int i)
{
	if (ac > 1 && file->magic != FAT_MAGIC && file->magic != FAT_CIGAM)
	{
		if (i > 1)
			ft_putchar('\n');
		ft_putstr(file->name);
		ft_putendl(":");
	}
}

void	nm_init(char *filename, int ac, int i)
{
	t_file	*file;
	void	*ptr;

	if (!(ptr = get_ptr(filename)))
		return ;
	file = malloc(sizeof(t_file));
	file->name = ft_strdup(filename);
	file->magic = *(unsigned int*)ptr;
	file->ptr = ptr;
	file->sect = NULL;
	file->symbol = NULL;
	if (!(is_valid(file)))
		return ;
	ft_nm(&file);
	print_filename(file, ac, i);
}

int		main(int ac, char **av)
{
	int i;

	i = 1;
	if (ac < 2)
		nm_init("a.out", 1, 1);
	else
	{
		while (i < ac)
		{
			nm_init(av[i], (ac - 1), i);
			i += 1;
		}
	}
	return (0);
}
