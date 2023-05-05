#include <stdio.h>
#include <stdlib.h>

#include "lib.h"
#include "strings.h"

char *input(char *argument)
{
    scanf("%s", argument);
    return argument;
}

int symbols_check(char *argument)
{
    char *reject = "|\\:*?«<>|";
    for (char *a = argument; *a != '\0'; a++)
    {
        for (char *b = reject; *b != '\0'; b++)
        {
            if (*a == *b)
                return -1;
        }
    }
    return 0;
}

char *check(char *argument, char **error)
{
    if (slen(argument) > MAX_PATH)
        *error = "Слишком длинный путь";
    if (symbols_check(argument) != 0)
        *error = "В пути присутствуют запрещённые символы";
    if (argument[0] != '~' && argument[0] != '/')
        *error = "Аргумент не является ни абсолютным, ни относительным путём";
    return *error;
}

int output(char *str)
{
    if (printf("%s\n", str) != 0)
        return 0;
    else
        return -1;
}

char *process(char *tmp, char *delim, char *dir, char *result)
{
    if (tmp[0] == '~' && tmp[1] == '/')
    {
        scat(result, dir);
        scat(result, ++tmp);
    }
    else if (tmp[0] == '/' || (tmp[0] == '~' && tmp[1] != '/'))
    {
        scat(result, tmp);
    }
    return result;
}

int add_delim(char *result, char *tmp, char *delim, char **error)
{
    if (tmp != NULL)
    {
        *error = "";
        check(tmp, error);
        if (!slen(*error) && slen(result) != 0)
        {
            result[slen(result)] = *delim;
        }
        return 0;
    }
    return -1;
}
