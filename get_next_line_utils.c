/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnaida <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 13:09:33 by gnaida            #+#    #+#             */
/*   Updated: 2021/05/14 19:21:46 by gnaida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*ft_str_add(char *buffi, int len)
{
	char	*str;

	str = (char *)malloc(len + 1);
	if (str == NULL || buffi == NULL)
		return (NULL);
	ft_str_copy(buffi, str);
	str[len] = '\0';
	return (str);
}

t_list	*ft_l_new(char *buffi, int fd, int len, char status)
{
	t_list	*newone;
	char	*str;

	str = ft_str_add(buffi, len);
	if (str == NULL)
		return (NULL);
	newone = (t_list *)malloc(sizeof(*newone));
	if (newone == NULL)
		return (NULL);
	newone->str = str;
	newone->len = len;
	newone->fd = fd;
	newone->status = status;
	newone->next = NULL;
	return (newone);
}

int	ft_l_add(t_list **list, t_list *newone)
{
	t_list	*back;

	if (newone == NULL)
		return (-10);
	if (*list == NULL)
	{
		*list = newone;
		return (0);
	}
	back = *list;
	while (back->next != NULL)
		back = back->next;
	back->next = newone;
	return (0);
}

int	ft_buff_split(int fdr, int fd, char *buff, t_list **list)
{
	int	i;
	int	len;
	int	sp;

	i = 0;
	len = 0;
	sp = 0;
	while (buff[i] != '\0')
	{
		if (buff[i] == '\n')
		{
			sp = ft_l_add(list, ft_l_new(&buff[i - len], fd, len, '\n')) + 1;
			len = -1;
		}
		i++;
		len++;
	}
	if (sp >= 0 && ((fdr < BUFFER_SIZE && fd != 0) || (fd == 0 && fdr == 0)))
		sp = ft_l_add(list, ft_l_new(&buff[i - len], fd, len, '\0')) + 1 + sp;
	if (sp >= 0 && ((fdr == BUFFER_SIZE && fd != 0) || (fd == 0 && fdr > 0)))
		sp = ft_l_add(list, ft_l_new(&buff[i - len], fd, len, ' ')) + sp;
	return (sp);
}

int	ft_fd_read(t_list **list, int fd)
{
	char	*buff;
	int		fdr;
	int		split;

	buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buff == NULL)
		return (-1);
	fdr = 1;
	split = 0;
	while ((fdr > 0) && (split == 0))
	{
		fdr = read(fd, buff, BUFFER_SIZE);
		if (fdr < 0)
			break ;
		buff[fdr] = '\0';
		split = ft_buff_split(fdr, fd, buff, list);
	}
	free(buff);
	if ((fdr < 0) || (split < 0))
		return (-1);
	return (1);
}
