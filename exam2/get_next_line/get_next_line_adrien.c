#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#define BUFFER_SIZE 1

int        ft_strlen(char *str)
{
    int i;

    i = 0;
    while (str[i])
        i++;
    return (i);
}
void    ft_strcpy(char *dest, char *src)
{
    while (*src)
    {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = *src;
}
char    *ft_strjoin(char *s1, char *s2)
{
    char *str;
    int l1;
    int l2;

    if (!s1 && !s2)
        return (NULL);
    l1 = ft_strlen(s1);
    l2 = ft_strlen(s2);
    str = malloc(sizeof(*str) * (l1 + l2 + 1));
    if (str == NULL)
        return (NULL);
    ft_strcpy(str, s1);
    ft_strcpy(str + l1, s2);
    str[l1 + l2] = '\0';
    return (str);
}

char    *ft_strdup(char *str)
{
    int i;
    char *new;

    new = malloc(sizeof(*new) * (ft_strlen(str) + 1));
    if (new == NULL)
        return (NULL);
    i = 0;
    while (str[i] != '\0')
    {
        new[i] = str[i];
        i++;
    }
    new[i] = str[i];
    return (new);
}

int        ft_isnewline(char *str)
{
    int i;

    i = 0;
    //printf("is newline\n");
    while (str[i] != '\0')
    {
      //  printf("str[%d] = |%c|\n", i, str[i]);
        if (str[i] == '\n')
            return (1);
        i++;
    }
    return (0);
}

int        get_next_line(char **line)
{
    char    *tmp;
    char    buf[BUFFER_SIZE + 1];
    int        red;
    if (line == NULL)
        return (-1);
    if (*line == NULL)
        *line = ft_strdup("");
    while ((red = read(0, buf, BUFFER_SIZE)) > 0)
    {
        buf[BUFFER_SIZE] = '\0';
       // printf("buf = |%s|\n", buf);
        tmp = NULL;
        if (ft_isnewline(buf))
            return (1);
        //printf("test\n");
        tmp = *line;
        if (*line == NULL)
        {
          //  printf("*line == NULL\n");
            *line = ft_strjoin(ft_strdup(""), buf);
        }
        else
        {
            //printf("joining..\n");
            *line = ft_strjoin(*line, buf);
        }
        free(tmp);
        if (*line == NULL)
            return (-1);
        //printf("line = %s| new_loop\n", *line);
    }
    return (red);
}
