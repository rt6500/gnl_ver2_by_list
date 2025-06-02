/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseki <rseki@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 11:18:14 by rseki             #+#    #+#             */
/*   Updated: 2025/06/02 11:18:14 by rseki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* polish linked list for next call
// while (last_node->str_buf[i] != '\0' && last_node->str_buf[++i]):
		'\0' acceptable, not '\n' + \'0'
*/
static void	polish_list(t_list **list)
{
	t_list	*last_node;
	t_list	*saved_remainder;
	int		i;
	int		k;
	char	*buf;

	buf = malloc(BUFFER_SIZE + 1);
	saved_remainder = malloc(sizeof(t_list));
	if (!buf || !saved_remainder)
		return ;
	last_node = find_last_node(*list);
	i = 0;
	k = 0;
	while (last_node->str_buf[i] != '\0' && last_node->str_buf[i] != '\n')
		i++;
	while (last_node->str_buf[i] != '\0' && last_node->str_buf[++i])
		buf[k++] = last_node->str_buf[i];
	buf[k] = '\0';
	saved_remainder->str_buf = buf;
	saved_remainder->next = NULL;
	dealloc(list, saved_remainder, buf);
}

// fetch the line from list
static char	*get_line(t_list *list)
{
	int		str_len;
	char	*next_str;

	if (list == NULL)
		return (NULL);
	str_len = len_to_newline(list);
	next_str = malloc(sizeof(char) * (str_len + 1));
	if (next_str == NULL)
		return (NULL);
	copy_str(list, next_str);
	return (next_str);
}

/*
append one node to the end of list
*/
static void	append(t_list **list, char *buf)
{
	t_list	*new_node;
	t_list	*last_node;

	last_node = find_last_node(*list);
	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return ;
	if (last_node == NULL)
		*list = new_node;
	else
		last_node->next = new_node;
	new_node->str_buf = buf;
	new_node->next = NULL;
}

/*
Create the list till it reach on '\n'
*/
void	create_list(t_list **list, int fd)
{
	int		char_read;
	char	*buf;

	while (!is_newline(*list))
	{
		buf = malloc(BUFFER_SIZE + 1);
		if (!buf)
			return ;
		char_read = read(fd, buf, BUFFER_SIZE);
		if (!char_read)
		{
			free(buf);
			return ;
		}
		buf[char_read] = '\0';
		append(list, buf);
	}
}

/*
read(fd, &next_line, 0) < 0 :
	check if the file can be opend(a varid fd or permission not dinied)
*/
char	*get_next_line(int fd)
{
	static t_list	*list;
	char			*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &next_line, 0) < 0)
	{
		dealloc(&list, NULL, NULL);
		return (NULL);
	}
	create_list(&list, fd);
	if (!list)
		return (NULL);
	next_line = get_line(list);
	polish_list(&list);
	return (next_line);
}
