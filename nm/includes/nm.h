/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 16:30:33 by julien            #+#    #+#             */
/*   Updated: 2018/06/15 17:41:41 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_H

# define NM_H

# include "../libft/libft.h"
# include <sys/mman.h>
# include <sys/stat.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <mach-o/fat.h>
# include <fcntl.h>

# define IS_32(m) ((m == MH_MAGIC || m == MH_CIGAM) ? 1 : 0)
# define IS_64(m) ((m == MH_MAGIC_64 || m == MH_CIGAM_64) ? 1 : 0)
# define IS_FAT_32(m) ((m == FAT_MAGIC || m == FAT_CIGAM) ? 1 : 0)
# define IS_FAT_64(m) ((m == FAT_MAGIC_64 || m == FAT_CIGAM_64) ? 1 : 0)

typedef struct		s_sect
{
	char			sectname[16];
	char			segname[16];
	int				n_sect;
	struct s_sect	*next;
}					t_sect;

typedef struct			s_symbol
{
	char				*name;
	char				type;
	unsigned long long	value;
	struct s_symbol		*next;
}						t_symbol;

typedef struct	s_file
{
	t_sect		*sect;
	t_symbol	*symbol;
}				t_file;

void    handle_64(char *ptr);
void	store_sect(t_file **file, struct segment_command_64 *seg);
void	process_symbol(t_file **file, struct symtab_command *symtab, char *ptr);
void	sort_symbol(t_symbol **symbol);

#endif