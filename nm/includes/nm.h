/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 16:30:33 by julien            #+#    #+#             */
/*   Updated: 2018/06/29 23:31:05 by julien           ###   ########.fr       */
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
	uint32_t		n_sect;
	struct s_sect	*next;
}					t_sect;

typedef struct			s_symbol
{
	char				*name;
	char				type;
	uint32_t			value_32;
	uint64_t			value_64;
	struct s_symbol		*next;
}						t_symbol;

typedef struct		s_file
{
	char			*name;
	uint64_t		size;
	char			arch;
	unsigned int	magic;
	void			*ptr;
	t_sect			*sect;
	t_symbol		*symbol;
}					t_file;

void		ft_nm(t_file **file);
void		handle_32(t_file **file);
void		handle_64(t_file **file);
void		get_sections_32(t_file **file, struct segment_command *seg);
void		get_sections_64(t_file **file, struct segment_command_64 *segment);
void		get_symbols_32(t_file **file, struct symtab_command *symtab);
void		get_symbols_64(t_file **file, struct symtab_command *symtab);
void		sort_symbols(t_symbol **symbol, char arch);
uint32_t	swap_32(uint32_t value, unsigned int m);
uint64_t	swap_64(uint64_t value, unsigned int m);
void		check(t_file **file, void *addr);

#endif