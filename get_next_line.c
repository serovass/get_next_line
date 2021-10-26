/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnaida <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 13:04:54 by gnaida            #+#    #+#             */
/*   Updated: 2021/05/13 22:21:38 by gnaida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list	*ft_list_clear(t_list *list, int fd, int st)
{
	t_list	*t;
	t_list	*t1;

	while (list != NULL && list->fd == fd && (list->status == 'd' || st == 1))
	{
		t1 = list;
		list = list->next;
		free(t1->str);
		free(t1);
	}
	t = list;
	while (t != NULL && t->next != NULL)
	{
		t1 = t->next;
		if (t1->fd == fd && (t1->status == 'd' || st == 1))
		{
			t->next = t1->next;
			free(t1->str);
			free(t1);
		}
		else
			t = t1;
	}
	return (list);
}

void	ft_str_copy(char *s, char *d)
{
	int	i;

	if (s == NULL || d == NULL)
		return ;
	i = 0;
	while (s[i] != '\0' && s[i] != '\n')
	{
		d[i] = s[i];
		i++;
	}
}

int	ft_get_line_len(t_list *list, int fd)
{
	int		len;
	t_list	*temp;

	len = 0;
	temp = list;
	while (temp != NULL)
	{
		if (temp && temp->fd == fd)
		{
			len = len + temp->len;
			if ((temp->status == '\n') || (temp->status == '\0'))
				return (len);
		}
		temp = temp->next;
	}
	return (-1);
}

char	*ft_get_line(t_list *list, int fd, int len, int *reply)
{
	char	*line;
	int		i;
	t_list	*temp;

	line = (char *)malloc(len + 1);
	if (line == NULL)
		return (NULL);
	i = 0;
	temp = list;
	while (temp != NULL && *reply < 0)
	{
		if (temp->fd == fd && (temp->status == '\n'))
			*reply = 1;
		if (temp->fd == fd && (temp->status == '\0'))
			*reply = 0;
		if (temp->fd == fd)
		{
			ft_str_copy(temp->str, &line[i]);
			i = i + temp->len;
			temp->status = 'd';
		}
		temp = temp->next;
	}
	line[len] = '\0';
	return (line);
}

int	get_next_line(int fd, char **line)
{
	int				reply;
	static t_list	*list;

	if ((BUFFER_SIZE == 0) || (line == NULL) || (fd < 0))
		return (-1);
	if (ft_get_line_len(list, fd) < 0)
	{
		if (ft_fd_read(&list, fd) < 0)
		{
			list = ft_list_clear(list, fd, 1);
			return (-1);
		}
	}
	reply = -1;
	*line = ft_get_line(list, fd, ft_get_line_len(list, fd), &reply);
	if (*line == NULL)
	{
		list = ft_list_clear(list, fd, 1);
		return (-1);
	}
	list = ft_list_clear(list, fd, 0);
	return (reply);
}
