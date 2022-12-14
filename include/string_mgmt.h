#ifndef STRING_MGMT_H
#define STRING_MGMT_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int my_strlen(char *string);
void my_strcpy(char *dst, char *src);
char* my_strdup(char *str);
int my_strcmp(char *s1, char *s2);
void my_strcat(char *dest, char *src);
void my_strcat_dot(char *dest, char *src);
int my_putchar(char c);
void my_putstr(char *string);
void my_memset(char *str, char c, int n);
char *my_strchr(char *str, char c);
char *my_itoa(int nb);
int my_isalpha(char letter);
int my_isupper(char letter);
int my_islower(char letter);

#endif