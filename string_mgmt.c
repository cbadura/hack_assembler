#include <stdbool.h>
#include "string_mgmt.h"

static char *reverse_string(char *word);

int my_strlen(char *str)
{
    int counter = 0;
    while(str[counter] != '\0')
        counter++;    
    return counter;
}

void my_strcpy(char *dst, char *src)
{
    // create a pointer pointing to the beginning of the destination string's address
    int i = 0;
    while(src[i] != '\0')
    {
        dst[i] = src[i];
        i++;
    }
    dst[i] = src[i];
}

char *my_strdup(char *str)
{
    int size;
    char *dupStr;
    size = my_strlen(str) + 1;

    dupStr = (char*)malloc(sizeof(char) * size);
    if(dupStr == NULL)
    {
        // printf("malloc of size %d failed!\n", size);
        return NULL;
    }
    for(int i = 0; i < size; i++)
        dupStr[i] = str[i];
    dupStr[size-1] = '\0';
    
    /*  while(*str) {       // the same thing
        *ptr++ = *str++;
    }
    *ptr = '\0'; */
    return dupStr;   
}

int my_strcmp(char *s1, char *s2) 
{
    while (*s1)
    {
        // if characters differ, or end of the second string is reached
        if (*s1 != *s2)
            break;

        // move to the next pair of characters
        s1++;
        s2++;
        // return the ASCII difference after converting `char*` to `unsigned char*`
    }
    return *(const unsigned char*)s1 - *(const unsigned char*)s2;
}                  

void my_strcat(char *dest, char *src)
{
    while(*dest) dest++;
    while((*dest++ = *src++));
    --dest;
}

void my_strcat_dot(char *dest, char *src)
{
    while(*dest != '.') dest++;
    while((*dest++ = *src++));
    --dest;
}

void my_memset(char *str, char c, int n)
{
    int i = 0;
    for (; i < n; i++)
        str[i] = c;
    
    str[i] = '\0';
}

int my_putchar(char c)
{
    return write(1, &c, 1);
}

void my_putstr(char *string)
{
    while(*string)
    { 
        my_putchar(*string);
        string++;
    }
}

char *my_strchr(char *str, char c)
{
    while (*str)
    {
        if (*str == c)
            return str;
        else
            str++;
    }
    return NULL;
}

char* my_itoa(int num)
{
    // find number of digits
    int len = 0;
    long numCopy = num;
    do {
        len++;
        numCopy /= 10;  // for decimal nbrs
    } while (numCopy != 0);

    char* str = malloc(sizeof(int) * len);
    int i = 0;
    bool isNegative = false;
    // handle 0 explicitly, otherwise empty string is printed for 0
    if (num == 0)
    {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }
    // in standard itoa(), negative numbers are handled only with
    // base 10. Otherwise numbers are considered unsigned.
    if (num < 0)
    {
        isNegative = true;
        num = -num;
    }
    // process individual digits
    while (num != 0)
    {
        int rem = num % 10;
        str[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0';
        num = num/10;
    }
    // if number is negative, append '-'
    if (isNegative)
        str[i++] = '-';
 
    str[i] = '\0'; // append string terminator
    // reverse the string
    reverse_string(str);
    return str;
}

static char *reverse_string(char *word)
{
    int length, c;
    char *begin, *end;
    
    length = my_strlen(word);
    begin  = word;  // gives begin the same address as word
    end    = word;  // gives end the same address as word
    
    for (c = 0; c < length - 1; c++)
        end++;          // -1 because the last cell contains the

    for (c = 0; c < length/2; c++) // if odd number, the middle letter stays the same  
    {      
        char temp;
        temp   = *end;     
        *end   = *begin;   
        *begin = temp;
    
        begin++;
        end--;
    }
    return word;
}