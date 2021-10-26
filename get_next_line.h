/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnaida <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 13:13:01 by gnaida            #+#    #+#             */
/*   Updated: 2021/05/13 22:39:10 by gnaida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>

typedef struct s_list
{
	char			*str;
	char			status;
	int				len;
	int				fd;
	struct s_list	*next;
}					t_list;

int		get_next_line(int fd, char **line);
char	*ft_get_line(t_list *list, int fd, int len, int *reply);
int		ft_get_line_len(t_list *list, int fd);
void	ft_str_copy(char *s, char *d);
t_list	*ft_list_clear(t_list *list, int fd, int st);
char	*ft_str_add(char *buffi, int len);
t_list	*ft_l_new(char *buffi, int fd, int len, char status);
int		ft_l_add(t_list **list, t_list *newone);
int		ft_buff_split(int fdr, int fd, char *buff, t_list **list);
int		ft_fd_read(t_list **list, int fd);

#endif
