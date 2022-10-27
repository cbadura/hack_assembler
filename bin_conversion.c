#include "main.h"

int my_atoi(char *str)
{
    int res = 0;
    int i = 0;
    int sign = 1;

    // get rid of whitespace
    while (str[i] == ' ' || str[i] == '\t')
        i++;

    // parse sign
    if (str[i] == '+')
        i++;
    if (str[i] == '-')
    {
        sign *= -1;
        i++;
    }
    // convert each char to int and multiply by 10 for each decimal position    
    while (str[i])
    {
        res = res * 10 + (str[i] - '0');
        i++;
    }

    return res * sign;
}

char *dec_to_bin(int nb)
{
    // set up string
    char *bin = NULL;
    bin = malloc(16); // bin itself has 15 bits + '\0'
    bin[15] = '\0';
    int i = 0;
    while (i < 15)
    {
        bin[i] = '0';
        i++;
    }
    
    i = 14; // str will be written from LSB (smallest bit)
    while (nb > 0)
    {
        bin[i] = (nb % 2) + '0';
        nb = nb / 2;
        i--;
    }
    return bin;
}

char *bin_conversion(char *dec)
{
    int nb = my_atoi(dec);
    // debug("nb: %d", nb);
    return dec_to_bin(nb);
}