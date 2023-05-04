#pragma once

#define MAX_PATH 260

char *input(char *argument);

int add_delim(char *result, char *tmp, char *delim, char **error);

int symbols_check(char *argument);

char *check(char *argument, char **error);

char *process(char *paths, char *delim, char *dir, char *result);

int output(char *str);
