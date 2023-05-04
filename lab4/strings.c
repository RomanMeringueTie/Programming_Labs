#include <stdio.h>

#include "strings.h"

size_t slen(char *str)
{
    size_t len = 0;
    for (int i = 0; str[i] != '\0'; i++)
        len++;
    return len;
}

char *schr(char *str, char c)
{
    while (*str != c && *str != '\0')
        str++;
    if (*str == c)
        return str;
    else
        return NULL;
}

size_t sspn(char *str1, char *str2)
{
    size_t len = 0;
    if ((str1 == NULL) || (str2 == NULL))
        return len;
    while (*str1 && schr(str2, *str1++))
    {
        len++;
    }
    return len;
}

int scmp(char *str1, char *str2)
{
    while (*str1)
    {
        if (*str1 != *str2)
            break;
        str1++;
        str2++;
    }
    return *str1 - *str2;
}

char *scpy(char *str1, char *str2)
{
    if (str1 == NULL)
    {
        return NULL;
    }
    char *ret = str1;
    while (*str2 != '\0')
    {
        *str1 = *str2;
        str1++;
        str2++;
    }
    *str1 = '\0';
    return ret;
}

int is_del(char c, char *delim)
{
    while (*delim != '\0')
    {
        if (c == *delim)
            return 1;
        delim++;
    }
    return 0;
}

char *stok(char *str, char *delim)
{
    static char *p;
    if (!str)
    {
        str = p;
    }
    if (!str)
    {
        return NULL;
    }
    while (1)
    {
        if (is_del(*str, delim))
        {
            str++;
            continue;
        }
        if (*str == '\0')
        {
            return NULL;
        }
        break;
    }
    char *ret = str;
    while (1)
    {
        if (*str == '\0')
        {
            p = str;
            return ret;
        }
        if (is_del(*str, delim))
        {
            *str = '\0';
            p = str + 1;
            return ret;
        }
        str++;
    }
}

char *scat(char *str1, char *str2)
{
    char *ptr = str1 + slen(str1);
    while (*str2 != '\0')
    {
        *ptr++ = *str2++;
    }
    *ptr = '\0';
    return str1;
}
