#include <stddef.h>
#include "includes/minishell.h"

char *extract_line(char **current_pos)
{
    char *start;
    char *end;
    char *line;
    int len;

    if (!current_pos || !*current_pos)
        return (NULL);
    start = *current_pos;
    end = ft_strchr(start, '\n');
    if (end)
    {
        len = end - start;
        line = ft_strndup(start, len);
        *current_pos = end + 1;
    }
    else
    {
        len = ft_strlen(start);
        line = ft_strndup(start, len);
        *current_pos = NULL;
    }
    return (line);
} 