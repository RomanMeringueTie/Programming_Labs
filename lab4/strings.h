#pragma once

#include <stdio.h>

size_t slen(char *str);

char *schr(char *str, char c);

size_t sspn(char *str1, char *str2);

int scmp(char *str1, char *str2);

char *scpy(char *str1, char *str2);

char *stok(char *str1, char *delim);

char *scat(char *str1, char *str2);