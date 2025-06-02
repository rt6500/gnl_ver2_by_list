/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseki <rseki@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 11:13:05 by rseki             #+#    #+#             */
/*   Updated: 2025/06/02 11:13:06 by rseki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <unistd.h> // write/read
# include <fcntl.h> // open
# include <stdlib.h> // malloc

/*
node of the linked list
* a string
* a pointer to the next tring
*/
typedef struct s_list
{
    char            *str_buf;
    struct s_list   *next;
}   t_list;

char    *get_next_line(int fd);
int     is_newline(t_list *list);
t_list  *find_last_node(t_list *list);
int     len_to_newline(t_list *list);
void    copy_str(t_list *list, char *str);
void    dealloc(t_list **list, t_list *clean_node, char *buf);

#endif
