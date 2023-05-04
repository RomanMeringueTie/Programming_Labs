#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "lib.h"
#include "strings.h"

int main()
{
    char *user = malloc(20);
    char *del = malloc(1);
    char *paths = malloc(MAX_PATH * 10);
    char *dir = malloc(MAX_PATH);
    char *result = malloc(MAX_PATH * 11);
    char *error = malloc(100);
    char *tmp = malloc(MAX_PATH);
    input(del);
    input(user);
    input(dir);
    input(paths);
    tmp = stok(paths, del);
    while (tmp != NULL)
    {
        check(tmp, &error);
        if (!slen(error))
        {
            process(tmp, del, dir, result);
        }
        else
        {
            output(error);
            printf("%s\n", tmp);
        }
        tmp = stok(NULL, del);
        add_delim(result, tmp, del, &error);
    }
    printf("New paths: ");
    output(result);
    free(del);
    free(paths);
    free(user);
    free(dir);
    free(result);
    free(tmp);
    return 0;
}
