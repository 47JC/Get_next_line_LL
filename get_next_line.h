#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

typedef struct s_list
{
    char            *content;
    struct s_list	*next;
}					t_list;

char		*get_next_line(int fd);
int count_newline(t_list *list);
#ifndef BUFFER_SIZE
#define BUFFER_SIZE 1
#endif
#endif