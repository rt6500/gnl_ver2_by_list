/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utilis.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseki <rseki@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 12:03:44 by rseki             #+#    #+#             */
/*   Updated: 2025/06/02 12:03:45 by rseki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int is_newline(t_list *list)
{
    int i;

    if (!list)
        return (0);
    while (list)
    {
        i = 0;
        while (list->str_buf[i] && i < BUFFER_SIZE)
        {
            if (list->str_buf[i] == '\n')
                return (1);
            i++;
        }
        list = list->next;
    }
    return (0);
}

t_list  *find_last_node(t_list *list)
{
    if (!list)
        return (NULL);
    while (list->next)
        list = list->next;
    return (list);
}

/*
count how many char are till '\n'
*/
int len_to_newline(t_list *list)
{
    int i;
    int len;

    if (list == NULL)
        return (0);
    len = 0;
    while (list)
    {
        i = 0;
        while (list->str_buf[i])
        {
            if (list->str_buf[i] =='\n')
            {
                ++len;
                return (len);
            }
            ++i;
            ++len;
        }
        list = list->next;
    }
    return (len);
}

/*
copy the string in the buf and return it
*/
void    copy_str(t_list *list, char *str)
{
    int i;
    int k;

    if (!list)
        return ;
    k = 0;
    while (list)
    {
        i = 0;
        while (list->str_buf[i])
        {
            if (list->str_buf[i] == '\n')
            {
                str[k++] = '\n';
                str[k] = '\0';
                return ;
            }
            str[k++] = list->str_buf[i++];
        }
        list = list->next;
    }
    str[k] = '\0';
}

void    dealloc(t_list **list, t_list *saved_remainder, char *buf)
{
    t_list  *tmp;

    if(!*list)
        return ;
    while (*list)
    {
        tmp = (*list)->next;
        free((*list)->str_buf);
        free(*list);
        *list = tmp;
    }
    *list = NULL;
    if (saved_remainder->str_buf[0])
        *list = saved_remainder;
    else
    {
        free(buf);
        free(saved_remainder);
    }
}