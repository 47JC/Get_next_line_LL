#include "get_next_line.h"

t_list *ft_limpar_lista(t_list **list)
{
    t_list *aux;
    int n;
    int nbr_nodes;

    nbr_nodes = 0;
    aux = *list;
    n = 0;
    while (aux)
    {   
        while(aux->content[n] != '\n' && aux->content[n] != '\0')
            n++;
        aux = aux->next;
        nbr_nodes++;
    }
    aux = *list;
    while(nbr_nodes > 1) 
        {
            aux = aux->next;
            free(*list);
            *list = aux;
            nbr_nodes--;
        }
     n = 0;
    while (aux->content[n] != '\n' && aux->content[n] != '\0')
        n++;
    (*list)->content = (aux->content + n + 1);
    return (*list);
}

int count_newline(t_list *list)
{
    int i;
    int j;
    t_list *temp;

    temp = list;
    i = 0;
    while(temp)
    {
        j = 0;
        while(temp->content[j] != '\n' && temp->content[j] != '\0')
        {
            i++;
            j++;
        }
        if(temp->content[j] == '\n' || temp->content[j] == '\0')
            break;
        temp = temp->next;
    }
    if (temp->content[i] == '\n')
        i++; 
    return(i);
}

char *ft_criar_string(t_list **list, char *str)
{
    int i;
    int j;
    t_list *aux;
    int len;
    i = 0;
    aux = *list;
    len = count_newline(*list);
    str = malloc(sizeof(char) * (len + 1));
    if (!str)
        return (NULL);
    while (aux)
    {
        j = 0;
        while (aux->content[j] != '\n' && aux->content[j] != '\0')
        {
            str[i++] = aux->content[j];
            j++;
        }
        str[i] = '\0';
        aux = aux->next;
    }
    str[i++] = '\n';
    str[i] = '\0';
    return (str);
}

void ft_lstadd_back(t_list **lst, char *buffer, int i)
{
    t_list *aux;
    t_list *new_node;
    int n;
    int y;

    new_node = malloc(sizeof(t_list));
    if (!new_node)
        return ;
    new_node->next = NULL;
    new_node->content = malloc(sizeof(char) * (i + 1));
    if (!new_node->content)
        return ;
    n = 0;
    y = i;
    while (buffer[n] && n != y)
    {
        new_node->content[n] = buffer[n];
        n++;
    }
    new_node->content[n] = '\0';
    aux = *lst;
    if (!aux)
        *lst = new_node;
    else
    {
        while (aux->next)
            aux = aux->next;
        aux->next = new_node;
    }
    free(buffer);
}

int ft_found_newline(t_list *list)
{
    int i;
    char *str;
    t_list *aux;

    aux = list;
    while (aux)
    {
        str = aux->content;
        i = 0;
        while (str[i])
        {
            if (str[i] == '\n')
                return (1);
            i++;
        }
        aux = aux->next;
    }
    return (0);
}

t_list *ft_criar_lista(int fd, t_list **list)
{
    int i;
    char *buffer;

    while (!ft_found_newline(*list))
    {   
        buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
        if(!buffer)
            return (NULL);
        i = read(fd, buffer, BUFFER_SIZE);
        buffer[i] = '\0';
        if (i > 0)
            ft_lstadd_back(list, buffer, i);
        else
        {   
            free(buffer);
            if ((*list)->content[0] == '\0')
                return (NULL);
            return (*list);
        }
    }
    return (*list);
}

char *get_next_line(int fd)
{
    char *newline;
    static t_list *list;
    t_list *aux;
    int t;

    t = 0;
    newline = malloc(sizeof(char) * (BUFFER_SIZE + 1));
    if (!newline)
        return (NULL);
    if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &newline, 0) < 0)
        return (NULL);
    //criar lista até encontrar \n
    list = ft_criar_lista(fd, &list);
    if(!list)
    {   
        free(list);
        return (NULL);
    }
    //criar string com o conteudo da lista
    aux = list;
    while (aux)
    {
        t++;
        aux = aux->next;
    }
    newline = ft_criar_string(&list, newline);

    //limpar lista e deixar o resto que foi lido
    ft_limpar_lista(&list);

    return (newline);
}

int main(void)
{
    int fd;

    fd = open("test.txt", O_RDONLY | O_CREAT);
    printf("|%s|", get_next_line(fd));
    printf("|%s|", get_next_line(fd));
    printf("|%s|", get_next_line(fd));
    printf("|%s|", get_next_line(fd));
    printf("|%s|", get_next_line(fd));
    printf("|%s|", get_next_line(fd));
}